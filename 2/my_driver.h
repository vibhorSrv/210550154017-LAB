
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/ioctl.h>
#include <linux/slab.h>
#include "my_ioct.h"

#define PRINT(...){printk(KERN_INFO "my_driver: "__VA_ARGS__);}

#define DEV_NAME "my_device"
#define MAJ_NUM 255
#define MIN_NUM 6

#define KBUFFSIZE 80


int CHAR_DEV_open(struct inode *__inode, struct file *__file);
int CHAR_DEV_release(struct inode *__inode, struct file *__file);
ssize_t CHAR_DEV_read(struct file *__file, char *__ubuff, size_t __nbytes, loff_t *offset);
ssize_t CHAR_DEV_write(struct file *__file, const char *__ubuff, size_t __nbytes, loff_t *offset);
long CHAR_DEV_ioctl(struct file *__file, unsigned int cmd, unsigned long arg);