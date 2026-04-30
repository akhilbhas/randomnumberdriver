#ifndef _RNG_IOCTL_H_
#define _RNG_IOCTL_H_

#include <linux/types.h>

#define RNG_MAGIC 'r'

#define RNG_STR_LEN 32

typedef struct _rng_data{
	__u32 min;
	__u32 max;
	__u32 value;
} rng_data_t;

#define RNG_GET_DATA _IOWR(RNG_MAGIC,1,rng_data_t)

#endif //_RNG_IOCTL_