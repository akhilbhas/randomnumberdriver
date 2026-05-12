ifneq ($(KERNELRELEASE),)

# ===== Kernel Build Context =====

obj-m += rng_custom.o

rng_custom-y := rng_custom.o

ccflags-y += -I$(src)/../inc

else

# ===== External Build Context =====

KDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

endif

.PHONY: all clean
