obj-m +=rng_custom.o

ccflags-y += -I$(PWD)/inc

rng_custom-y := src/rng_custom.o

