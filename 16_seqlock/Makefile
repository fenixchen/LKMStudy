include ${PWD}/../common.mk

prog=seqlock

obj-m	:=   $(prog).o

all : 
	$(MAKE) -C $(BASEINCLUDE) SUBDIRS=$(PWD) modules;
	chmod +x *.ko

clean:
	$(MAKE) -C $(BASEINCLUDE) SUBDIRS=$(PWD) clean;
	rm -f *.ko;


