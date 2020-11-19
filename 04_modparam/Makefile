include ${PWD}/../common.mk

prog=modparam

rb_test-objs := $(prog).o 

obj-m	:=   $(prog).o
all : 
	$(MAKE) -C $(BASEINCLUDE) SUBDIRS=$(PWD) modules;
	chmod +x *.ko

clean:
	$(MAKE) -C $(BASEINCLUDE) SUBDIRS=$(PWD) clean;
	rm -f *.ko;


