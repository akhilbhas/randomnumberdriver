#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdint.h>

#include "rng_custom.h"

int main(){
	int fd = open("/dev/random_char", O_RDWR);
	rng_data_t data;

	data.min = 10;
	data.max = 20;

	if(ioctl(fd,RNG_GET_DATA,&data) == -1){
		perror("ioctl failed \n");
		return 1;
	}

	printf("Value %u\n",data.value);

	close(fd);
	return 0;
}

