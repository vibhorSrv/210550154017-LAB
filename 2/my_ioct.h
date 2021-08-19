#ifndef MY_IOCT_H
#define MY_IOCT_H
#define MAGICNUM 'O'

struct stats
{
    int size;
    char *buff;
    int r_w;
};
#define GETSTATS _IOR(MAGICNUM, 21, struct stats)
#endif