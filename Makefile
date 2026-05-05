obj-m += rng_custom.o
rng_custom-y := src/rng_custom.o
ccflags-y += -I$(src)/inc

