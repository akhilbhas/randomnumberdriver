# Random Number Character driver

## Table of content
- [Introduction](#introduction)
- [Build](#build)
- [Usage](#usage)


## Introduction
This is a simple character driver which uses the Linux random number generator to create a random number between the min(default=0) and max(default=100) value provided. 

## Build
Use the following instruction to build the driver and test application using the repo

- Clone the repo
  >git clone <repo>
- Identify the Linux kernel header path 
   > export KDIR=\<linux headre path\>

   Default path is already available in Makefile.
- Build the package
    > make all

    or
    > make all KDIR=\<Linux path\>

- The kernel module and test app will be built in bin folder in side the cloned folder.
- To clean the build do 
    >make clean KDIR=\<Linux path\>

## Usage
To use the driver and test application refer [Usage doc](./doc/Usage.md)