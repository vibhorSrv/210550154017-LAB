#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define DEV_NAME "my_device"

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Error: Usage: ./UserAppWrite \"DATA TO WRITE\"\n");
        return -1;
    }
    int fd, res;
    fd = open("/dev/" DEV_NAME, O_WRONLY, 0777);
    if (fd < 0)
    {
        printf("Could not open device %s", DEV_NAME);
        return -1;
    }
    else
    {
        res = write(fd, argv[1], strlen(argv[1]));
        printf("Written %d bytes to the kernel buffer\n", res);
    }
    close(fd);
    return 0;
}
