obj-m +=rng_custom.o

KDIR ?= /lib/modules/$(shell uname -r)/build
PWD:= $(shell pwd)


ccflags-y += -I$(PWD)/inc

rng_custom-y := src/rng_custom.o

BIN_DIR ?= $(PWD)/bin

.PHONY: all driver test clean

all: driver test

driver:
	@mkdir -p $(BIN_DIR)
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	@mv -f *.ko *.o *.mod *.mod.c *.order *.symvers $(BIN_DIR) 2>/dev/null || true
	@mv -f .* $(BIN_DIR) 2> /dev/null || true

test:
	$(MAKE) -C test BIN_DIR=$(BIN_DIR) INC_DIR=$(PWD)/inc

clean:
	$(MAKE) -C $(KDIR) m=$(PWD) clean
	$(MAKE) -C test clean
	@rm -rf $(BIN_DIR)