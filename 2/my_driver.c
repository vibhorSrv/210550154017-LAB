
#include "my_driver.h"

MODULE_AUTHOR("Vibhor");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("IOCT based read write operation stats monitor");

struct file_operations fops =
    {
        .owner = THIS_MODULE,
        .open = CHAR_DEV_open,
        .write = CHAR_DEV_write,
        .read = CHAR_DEV_read,
        .unlocked_ioctl = CHAR_DEV_ioctl,
        .release = CHAR_DEV_release,
};

struct cdev *mycdev;

static struct stats *rwstats;

static char *kbuff[KBUFFSIZE];

static int MY_MODULE_init(void)
{
    int res;
    dev_t dev;
    PRINT("My Module init start");
    dev = MKDEV(MAJ_NUM, MIN_NUM);

    res = register_chrdev_region(dev, 1, DEV_NAME);

    if (res != 0)
    {
        PRINT("Couldnot register char device");
        return -1;
    }
    else
    {
        mycdev = cdev_alloc();
        mycdev->ops = &fops;
        res = cdev_add(mycdev, dev, 1);
        if (res != 0)
        {
            unregister_chrdev_region(dev, 1);
            PRINT("Could not add cdev")
            return -1;
        }
    }

    rwstats = (struct stats *)kmalloc(sizeof(struct stats), GFP_KERNEL);
    rwstats->buff = (char *)kmalloc(sizeof(char) * 100, GFP_KERNEL);

    PRINT("My Module init end");
    return 0;
}
static void MY_MODULE_exit(void)
{
    dev_t dev;
    dev = MKDEV(MAJ_NUM, MIN_NUM);

    unregister_chrdev_region(dev, 1);

    cdev_del(mycdev);
    kfree(rwstats->buff);
    kfree(rwstats);

    PRINT("Unregisterd device with MAJ=%d,MIN=%d", MAJOR(dev), MINOR(dev))
}

module_init(MY_MODULE_init);
module_exit(MY_MODULE_exit);

int CHAR_DEV_open(struct inode *__inode, struct file *__file)
{
    PRINT("CHARDEV_open");
    return 0;
}
int CHAR_DEV_release(struct inode *__inode, struct file *__file)
{
    PRINT("CHARDEV_release");
    return 0;
}

ssize_t CHAR_DEV_read(struct file *__file, char *__ubuff, size_t __nbytes, loff_t *offset)
{
    int numtoread, copyres;
    PRINT("Inside CHAR_DEV_read() start")

    numtoread = __nbytes > KBUFFSIZE ? KBUFFSIZE : __nbytes;

    copyres = copy_to_user(__ubuff, kbuff, numtoread);

    if (copyres == 0)
    {
        PRINT("Copied %d bytes to user space", numtoread);
        //updating the rw stats
        memcpy((char *)rwstats->buff, (char *)kbuff, numtoread);
        rwstats->size = numtoread;
        rwstats->r_w = 0;

        return numtoread;
    }
    PRINT("Inside CHAR_DEV_read() end")

    return 0;
}
ssize_t CHAR_DEV_write(struct file *__file, const char *__ubuff, size_t __nbytes, loff_t *offset)
{
    int numtowrite, copyres;
    PRINT("Inside CHAR_DEV_write() start")

    numtowrite = __nbytes > KBUFFSIZE ? KBUFFSIZE : __nbytes;

    copyres = copy_from_user(kbuff, __ubuff, numtowrite);

    if (copyres == 0)
    {
        PRINT("Copied %d bytes from user space to kernel space", numtowrite);
        //updating the rw stats
        memcpy((char *)rwstats->buff, (char *)kbuff, numtowrite);
        rwstats->size = numtowrite;
        rwstats->r_w = 1;
        PRINT("rwstatus->buff= %s", rwstats->buff);
        return numtowrite;
    }
    PRINT("Inside CHAR_DEV_write() end")

    return 0;
}

long CHAR_DEV_ioctl(struct file *__file, unsigned int cmd, unsigned long arg)
{
    struct stats *u_rwstat;

    PRINT("Inside CHAR_DEV_ioctl() start")

    switch (cmd)
    {
    case GETSTATS:
        u_rwstat = (struct stats *)arg;
        if (copy_to_user(&(u_rwstat->size), &(rwstats->size), sizeof(int)))
            return -EFAULT;
        if (copy_to_user(u_rwstat->buff, rwstats->buff, rwstats->size))
            return -EFAULT;
        if (copy_to_user(&(u_rwstat->r_w), &(rwstats->r_w), sizeof(int)))
            return -EFAULT;
        return 0;
    default:
        PRINT("IOCTL Operation Not Supported!");
    }
    PRINT("Inside CHAR_DEV_ioctl() end")
    return -1;
}