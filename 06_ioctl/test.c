#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>              /* open */
#include <unistd.h>             /* exit */
#include <sys/ioctl.h>          /* ioctl */



#define DEV "/dev/chardev"

int main()
{
    unsigned int num = 123;
    int fd = open(DEV, 0);
    if (!fd){
        printf("open %s failed\n", DEV);
        return -1;
    }
    ioctl(fd, 100, &num);
    ioctl(fd, 200, &num);
    printf("num:%d\n", num);
    close(fd);
    return 0;
}
