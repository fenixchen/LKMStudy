
rb_test-objs := rbtree_test.o 

obj-m	:=   rb_test.o
all : 
	$(MAKE) -C $(BASEINCLUDE) SUBDIRS=$(PWD) modules;
	chmod +x rb_test.ko

clean:
	$(MAKE) -C $(BASEINCLUDE) SUBDIRS=$(PWD) clean;
	rm -f *.ko;


