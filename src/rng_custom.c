#include<linux/module.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/uaccess.h>
#include<linux/random.h>
#include<linux/types.h>
#include<linux/kernel.h>
#include "rng_custom.h"

#define DEVICE_NAME "random_char"
#define CLASS_NAME "rng"
//char device parameters
static int major;
static struct class* rng_class = NULL;
static struct device* rng_device = NULL;
static u32 rng_min = 0;
static u32 rng_max = 100;

static u32 rng_calulate_value(u32 min, u32 max);

static u32 rng_calulate_value(u32 min, u32 max){
	u32 value;
	get_random_bytes(&value,sizeof(value));
	value = min + (value%(max-min+1));
	return value;

}


/**
 * Read Funciton
 */
static ssize_t rng_read(struct file *file, char __user *buff, size_t len, loff_t *offset)
{
	
	u32 random_value;
	char kbuf[32];
	int str_len;

	if(*offset >0)
		return 0;

	if(len < sizeof(u32))
		return -EINVAL;

	random_value = rng_calulate_value(rng_min,rng_max);
	str_len = scnprintf(kbuf,sizeof(kbuf),"%u\n",random_value);

	if(*offset >=str_len)
		return 0;
	
	if (len > str_len - *offset)
		len = str_len - *offset;



	if(copy_to_user(buff,kbuf +*offset,len))
		return -EFAULT;
	*offset += len;
	return len;

}

/**
 * Write function
 */

static ssize_t rng_write(struct file *file, const char __user *buf, size_t len, loff_t *offset)
{
	char kbuf[32];
	int ret;
	if(len >= sizeof(kbuf))
		return -EINVAL;
	if(copy_from_user(kbuf,buf,len))
		return -EFAULT;
	
	kbuf[len] = '\0';

	ret =sscanf(kbuf,"%u %u",&rng_min, &rng_max);
	if(ret != 2)
		return -EINVAL;
	if(rng_max <= rng_min)
	{
		return -EINVAL;
	}
	printk(KERN_INFO "[rng] range set: %u -%u \n",rng_min,rng_max);
	return len;

}

static long rng_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	rng_data_t data;
	switch(cmd){
		case RNG_GET_DATA:
			if(copy_from_user(&data,(rng_data_t __user *)arg, sizeof(data)))
				return -EFAULT;
			if (data.max <= data.min)
				return -EINVAL;
			data.value = rng_calulate_value(data.min,data.max);
			if(copy_to_user((rng_data_t __user*)arg,&data,sizeof(data)))
				return -EFAULT;
			break;
		default:
			return -EINVAL;
	}
	return 0;

}

//Operations

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = rng_read,
	.write = rng_write,
	.unlocked_ioctl = rng_ioctl,
};

static int __init rng_init(void){
	major = register_chrdev(0,DEVICE_NAME,&fops);

	rng_class = class_create(CLASS_NAME);
	rng_device = device_create(rng_class, NULL, MKDEV(major,0),NULL, DEVICE_NAME);

	printk(KERN_INFO "RNG Char device loaded\n");
	return 0;
}

static void __exit rng_exit(void){
	device_destroy(rng_class,MKDEV(major,0));
	class_unregister(rng_class);
	class_destroy(rng_class);
	unregister_chrdev(major,DEVICE_NAME);
	printk(KERN_INFO "RNG device destroyed\n");
}

module_init(rng_init);
module_exit(rng_exit);

MODULE_LICENSE("GPL");
