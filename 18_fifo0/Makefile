include ${PWD}/../common.mk

prog=fifo0

obj-m	:=   $(prog).o

all : 
	$(MAKE) -C $(BASEINCLUDE) SUBDIRS=$(PWD) modules;
	chmod +x *.ko

clean:
	$(MAKE) -C $(BASEINCLUDE) SUBDIRS=$(PWD) clean;
	rm -f *.ko;

test:
	$(CROSS_COMPILE)gcc -o test test.c -static

