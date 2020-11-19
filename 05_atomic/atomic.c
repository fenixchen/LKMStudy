#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */


atomic_t test;
static int __init atomic_init(void)
{
    atomic_set(&test, 1);
    return 0;
}

static void __exit atomic_exit(void)
{
    atomic_add(9, &test);
    atomic_sub(10, &test);
}


MODULE_LICENSE("GPL");


module_init(atomic_init);

module_exit(atomic_exit);


