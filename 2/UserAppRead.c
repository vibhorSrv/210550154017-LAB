#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define DEV_NAME "my_device"

static char ubuff[100] = {'\0'};

int main(int argc, char const *argv[])
{
    int fd, res;
    fd = open("/dev/" DEV_NAME, O_RDWR, 0777);
    if (fd < 0)
    {
        printf("Could not open device %s", DEV_NAME);
        return -1;
    }
    else
    {
        res = read(fd, ubuff, 100);
        if (res >= 0)
            printf("Read %d bytes from the kernel buffer = %s", res, ubuff);
        else
        {
            printf("Could not read");
        }
    }
    close(fd);
    return 0;
}
