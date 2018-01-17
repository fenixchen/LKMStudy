#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */


DECLARE_PER_CPU(int, var);

static int __init per_cpu_init(void)
{
    get_cpu_var(var)++;
    put_cpu_var(var);
    return 0;
}

static void __exit per_cpu_exit(void)
{
    
}


MODULE_LICENSE("GPL");


module_init(per_cpu_init);

module_exit(per_cpu_exit);


