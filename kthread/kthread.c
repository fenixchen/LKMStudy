#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/wait.h>
#include <linux/delay.h>


MODULE_LICENSE("GPL");


int pid1 = 1;
int pid2 = 2;

#define LOOP 	 30
#define SLEEP_MS 1000



DECLARE_WAIT_QUEUE_HEAD(wq);

int condition;

struct task_struct *task1;
struct task_struct *task2;

static int thread_1(void *data)
{
    int i = 0;
    printk(KERN_INFO "thread_1 ENTER.\n");
    while (i < LOOP && !kthread_should_stop())
    {
        i++;
	    wait_event(wq, condition == 0xA);
	    printk(KERN_INFO "thread_1 RUN.\n");
	    msleep(SLEEP_MS);
	    condition = 0xB;
	    wake_up(&wq);
    }    
    printk(KERN_INFO "thread_1 EXIT.\n");
    do_exit(555);
    return 0;
}

static int thread_2(void *data)
{
    int i = 0;
	printk(KERN_INFO "thread_2 ENTER.\n");
    while (i < LOOP && !kthread_should_stop())
    {        
        i++;
        wait_event(wq, condition == 0xB);
        printk(KERN_INFO "thread_2 RUN.\n");
        msleep(SLEEP_MS);
        condition = 0xA;
        wake_up(&wq);
    }
    printk(KERN_INFO "thread_2 EXIT.\n");
    do_exit(666);
    return 0;
}

int init_module(void)
{
    condition = 0xA;
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
    return;
}
