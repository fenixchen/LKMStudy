#include <stdio.h>



void test1(void)
{
    int var = 10;
    asm("incl %0"
        :"=a"(var)
        :"0"(var));
    printf("var:%d\n", var);
}


void test2(void)
{
    int x = 10, y = 0;
    asm("movl %1, %%eax;"
        "movl %%eax, %0;"
        :"=r"(y)    /* y is output operand */
        :"r"(x)     /* x is input operand */
        :"%eax");   /* %eax is clobbered register */
    printf("y:%d\n", y);
}

/* input and output use different register */
void test3(void)
{
    int x = 10, y = 0;
    asm("movl %1, %%eax;"
        "movl %%eax, %0;"
        :"=&r"(y)    /* y is output operand */
        :"r"(x)     /* x is input operand */
        :"%eax");   /* %eax is clobbered register */
    printf("y:%d\n", y);
}


/* use special registers */
void test4(void)
{
    unsigned int _eax, _ebx, _ecx, _edx, op = 0;
    asm("cpuid"
        : "=a"(_eax),
        "=b"(_ebx),
        "=c"(_ecx),
        "=d"(_edx)
        : "a"(op));
    printf("%x,%x,%x,%x,%x\n", _eax, _ebx, _ecx, _edx, op);
}

void test5(void)
{
    unsigned int counter = 10000;
    __asm__ __volatile__(
        "lock; decl %0"
        :"=m"(counter)
        :"m"(counter));
    printf("counter:%d\n", counter);
}


int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}
