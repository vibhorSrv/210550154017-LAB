obj-m:= my_driver.o

KDIR = /lib/modules/$(shell uname -r)/build

PWD = $(shell pwd)

default:
		make -C $(KDIR) M=$(PWD) modules
		gcc UserAppWrite.c -o UserAppWrite
		gcc UserAppRead.c -o UserAppRead
		gcc UserAppIoctl.c -o UserAppIoctl
clean:
		make -C $(KDIR) M=$(PWD) clean
		rm UserAppWrite UserAppIoctl UserAppRead
