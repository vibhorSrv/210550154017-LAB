obj-m:= my_driver.o

KDIR = /lib/modules/$(shell uname -r)/build

PWD = $(shell pwd)

default:
		make -C $(KDIR) M=$(PWD) modules
		gcc UserApp1.c -o UserApp1
		gcc UserApp2.c -o UserApp2
clean:
		make -C $(KDIR) M=$(PWD) clean
		rm UserApp1 UserApp2
