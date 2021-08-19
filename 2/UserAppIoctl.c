#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "my_ioct.h"

#define DEV_NAME "my_device"

char ubuff[100] = {'\0'};
struct stats *rwstat;

int main(int argc, char const *argv[])
{
    int fd, res;
    fd = open("/dev/" DEV_NAME, O_WRONLY, 0777);
    if (fd < 0)
    {
        printf("Could not open device %s", DEV_NAME);
        return -1;
    }
    else
    {
        rwstat = (struct stats *)malloc(sizeof(struct stats));
        res = ioctl(fd, GETSTATS, rwstat);
        if (res >= 0)
        {
            printf("RW stat->size =  %d \n", rwstat->size);
            printf("RW stat->buff =  %s \n", rwstat->buff);
            printf("RW stat->r_w =  %d \n", rwstat->r_w);
        }
        else
        {
            printf("IOCTL operation failed");
        }
    }
    close(fd);
    return 0;
}
