#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>              /* open */
#include <unistd.h>             /* exit */
#include <sys/ioctl.h>          /* ioctl */



#define DEV "./chardev"

int main()
{
    unsigned int num = 123;
    int fd = open(DEV, 0);
    ioctl(fd, 100, &num);
    ioctl(fd, 200, &num);
    printf("num:%d\n", num);
    close(fd);
    return 0;
}
