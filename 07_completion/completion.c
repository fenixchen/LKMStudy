#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/wait.h>
#include <linux/delay.h>
#include <linux/semaphore.h>

MODULE_LICENSE("GPL");

struct completion comp;

#define SLEEP_MS 10000
static int thread_func(void *data)
{
    printk(KERN_INFO "thread ENTER, sleep %d ms.\n", SLEEP_MS);
    msleep(SLEEP_MS);
    printk(KERN_INFO "thread EXIT, sleep DONE\n");
    complete(&comp);
    do_exit(0);
    return 0;
}


int init_module(void)
{
    struct task_struct *task1;
    init_completion(&comp);
    printk(KERN_INFO "Before create kernel thread\n");
    task1 = kthread_create(&thread_func, NULL, "thread_func");
    printk(KERN_INFO "After create kernel thread\n");
    wake_up_process(task1);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Waiting thread exit\n");
    wait_for_completion(&comp);
    printk(KERN_INFO "Thread done.\n");
    return;
}
