#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <asm/uaccess.h>        /* for put_user */


int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
long device_unlocked_ioctl(struct file *, unsigned int, unsigned long);

MODULE_LICENSE("GPL");


#define SUCCESS 0
#define DEVICE_NAME "mydev"
#define CLASS_NAME "myclass"
#define BUF_LEN 80

static int Major;
static int Device_Open = 0;

static char msg[BUF_LEN];
static char *msg_Ptr;

static struct class *myClass = NULL;
static struct device *myDevice = NULL;

static struct file_operations fops =
{
    .read = device_read,
    .write = device_write,
    .unlocked_ioctl = device_unlocked_ioctl,
    .open = device_open,
    .release = device_release
};


static struct kobject *myKObj;

static int test_num = 0;

static ssize_t test_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count){

    sscanf(buf, "%d", &test_num);
    return count;
}
static ssize_t test_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    test_num ++;
    return sprintf(buf, "test count:%d\n", test_num);
}

static struct kobj_attribute test_attr = __ATTR(test, 0644, test_show, test_store);

static struct attribute *myattrs[] = {
    &test_attr.attr,
    NULL,
};

static struct attribute_group attr_group = {
      .name  = "mygroup",
      .attrs = myattrs,
};


int init_module(void)
{
    Major = register_chrdev(0, DEVICE_NAME, &fops);

    if (Major < 0)
    {
        printk(KERN_ALERT "Registering char device failed with %d\n", Major);
        return Major;
    }     
    
    myClass = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(myClass))
    {
        panic("class register faled\n");
    }

    myDevice = device_create(myClass, NULL, MKDEV(Major, 0), NULL, DEVICE_NAME);
    if (IS_ERR(myDevice))
    {
        panic("device register faled\n");
    }

    myKObj = kobject_create_and_add("mykobj", kernel_kobj->parent); 
    if (!myKObj)
    {
        panic("create kobject failed\n");
    }   
    sysfs_create_group(myKObj, &attr_group);
    return SUCCESS;
}


void cleanup_module(void)
{
    kobject_put(myKObj);
    device_destroy(myClass, MKDEV(Major, 0));
    class_unregister(myClass);
    class_destroy(myClass);
    unregister_chrdev(Major, DEVICE_NAME);
}

static int device_open(struct inode *inode, struct file *file)
{
    static int counter = 0;

    if (Device_Open)
    {
        return -EBUSY;
    }

    Device_Open++;
    sprintf(msg, "I already told you %d times Hello world!\n", counter++);
    msg_Ptr = msg;
    try_module_get(THIS_MODULE);
    return SUCCESS;
}
static int device_release(struct inode *inode, struct file *file)
{
    Device_Open --;
    module_put(THIS_MODULE);
    return 0;
}
static ssize_t device_read(struct file *filp,
                           char *buffer,
                           size_t length,
                           loff_t *offset)
{
    int bytes_read = 0;

    if (*msg_Ptr == 0)
    {
        return 0;
    }

    while (length && *msg_Ptr)
    {
        put_user(*(msg_Ptr++), buffer++);
        length --;
        bytes_read++;
    }

    return bytes_read;
}

static ssize_t
device_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
    printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
    return -EINVAL;
}


unsigned int hello_num = 0;
long device_unlocked_ioctl(struct file *file, unsigned int ioctl_num, unsigned long param)
{
	printk(KERN_INFO"ioctl_num:%d\n", ioctl_num);
    switch (ioctl_num)
    {
    case 100:    	
    	copy_from_user(&hello_num, (unsigned int*)param, sizeof(unsigned int));    	
        break;	
    case 200:
    	hello_num ++;
    	copy_to_user((unsigned int*)param, &hello_num, sizeof(unsigned int));
        break;
    }
    return SUCCESS;
}



