#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/wait.h>
#include <linux/delay.h>


MODULE_LICENSE("GPL");


struct task_struct *task1;
struct task_struct *task2;


static DEFINE_MUTEX(mutex);


static int thread_1(void *data)
{
    printk(KERN_INFO "thread_1 ENTER.\n");
    while (!kthread_should_stop())
    {
	    printk(KERN_INFO "thread_1 lock ENTER.\n");
        msleep(1000);
        mutex_lock(&mutex);
	    printk(KERN_INFO "thread_1 lock OK, go to sleep.\n");
        msleep(1000);
	    printk(KERN_INFO "thread_1 lock EXIT.\n");
        mutex_unlock(&mutex);
    }    
    printk(KERN_INFO "thread_1 EXIT.\n");
    do_exit(555);
    return 0;
}

static int thread_2(void *data)
{
    printk(KERN_INFO "thread_2 ENTER.\n");
    while (!kthread_should_stop())
    {
	    printk(KERN_INFO "thread_2 lock ENTER.\n");
        msleep(1000);
        mutex_lock(&mutex);
	    printk(KERN_INFO "thread_2 lock OK, go to sleep.\n");
        msleep(1000);
	    printk(KERN_INFO "thread_2 lock EXIT.\n");
        mutex_unlock(&mutex);
    }    
    printk(KERN_INFO "thread_2 EXIT.\n");
    do_exit(666);
    return 0;
}

int init_module(void)
{
    mutex_init(&mutex);
    printk(KERN_INFO "Before create kernel thread\n");
    task1 = kthread_create(&thread_1, NULL, "thread_1");
    task2 = kthread_create(&thread_2, NULL, "thread_2");
    printk(KERN_INFO "After create kernel thread\n");
    wake_up_process(task1);
    wake_up_process(task2);
    return 0;
}

void cleanup_module(void)
{
	int ret;
	ret = kthread_stop(task1);
	printk(KERN_INFO "kthread stop task1 ret:%d\n", ret);
	ret = kthread_stop(task2);
	printk(KERN_INFO "kthread stop task2 ret:%d\n", ret);
    mutex_destroy(&mutex);
    return;
}
