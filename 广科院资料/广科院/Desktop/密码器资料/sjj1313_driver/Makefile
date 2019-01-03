CC = gcc 
obj-m	:= tass_usb.o

KERNELDIR ?= /lib/modules/2.6.18-238.el5/build
INSTALLDIR :=  /lib/modules/2.6.18-238.el5/kernel/lib/
PWD       := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

install:
	cp -f ./tass_usb.ko $(INSTALLDIR)
	depmod
	modprobe tass_usb

uninstall:
	modprobe -r tass_usb
	rm -f  $(INSTALLDIR)tass_usb.ko

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.markers *.symvers *.unsigned *.order

