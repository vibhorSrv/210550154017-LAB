
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/semaphore.h>

#define PRINT(...){printk(KERN_INFO "my_driver: "__VA_ARGS__);}

#define DEV_NAME "my_device2"
#define MAJ_NUM 255
#define MIN_NUM1 7
#define MIN_NUM2 8
#define KBUFFSIZE 80


int CHAR_DEV_open(struct inode *__inode, struct file *__file);
int CHAR_DEV_release(struct inode *__inode, struct file *__file);
ssize_t CHAR_DEV_read(struct file *__file, char *__ubuff, size_t __nbytes, loff_t *offset);
ssize_t CHAR_DEV_write(struct file *__file, const char *__ubuff, size_t __nbytes, loff_t *offset);