ifneq ($(KERNELRELEASE),)

# ===== Kernel Build Context =====

obj-m += rng_custom.o

ccflags-y += -I$(src)/../inc

else

# ===== External Build Context =====

KDIR ?= $(KERNEL_SRC)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

endif

.PHONY: all clean
