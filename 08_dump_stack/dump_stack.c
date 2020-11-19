#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/moduleparam.h>  /* Needed by module param */

static int hello1_data __initdata = 3;


void func(void)
{
    dump_stack();
}

static int __init hello1_init(void)
{
    printk(KERN_INFO "Hello, world 1:%d\n", hello1_data);
    func();
    return 0;
}

static void __exit hello1_exit(void)
{
    printk(KERN_INFO "Goodbye, world 1\n");
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hello"); 
MODULE_DESCRIPTION("Test Driver");
MODULE_SUPPORTED_DEVICE("testdevice");


module_init(hello1_init);

module_exit(hello1_exit);


