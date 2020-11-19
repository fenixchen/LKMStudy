include ${PWD}/../common.mk

prog=misc

misc-objs := $(prog).o 

obj-m	:=   $(prog).o
all : 
	$(MAKE) -C $(BASEINCLUDE) SUBDIRS=$(PWD) modules;
	chmod +x *.ko

clean:
	$(MAKE) -C $(BASEINCLUDE) SUBDIRS=$(PWD) clean;
	rm -f *.ko;


