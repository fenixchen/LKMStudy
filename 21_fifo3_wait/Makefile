include ${PWD}/../common.mk

prog=fifo3

obj-m	:=   $(prog).o

all : 
	$(MAKE) -C $(BASEINCLUDE) SUBDIRS=$(PWD) modules;
	chmod +x *.ko

clean:
	$(MAKE) -C $(BASEINCLUDE) SUBDIRS=$(PWD) clean;
	rm -f *.ko test

test:
	$(CROSS_COMPILE)gcc -o test test.c -static

