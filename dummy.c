#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple character driver for learning purposes");

#define DEVICE_NAME "dummy"

static int major_num;

static int dummy_open(struct inode *inodep, struct file *filep){
    printk(KERN_INFO "Dummy driver: Device opened\n");
    return 0;
}

static int dummy_release(struct inode *inodep, struct file *filep){
    printk(KERN_INFO "Dummy driver: Device closed\n");
    return 0;
}

static ssize_t dummy_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
    printk(KERN_INFO "Dummy driver: Read function called\n");
    return 0;
}

static ssize_t dummy_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
    printk(KERN_INFO "Dummy driver: Write function called\n");
    return len;
}

static struct file_operations fops = {
    .open = dummy_open,
    .release = dummy_release,
    .read = dummy_read,
    .write = dummy_write,
};

static int __init dummy_init(void){
    printk(KERN_INFO "Dummy driver: Initialization started\n");

    major_num = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_num < 0){
        printk(KERN_ALERT "Dummy driver: Failed to register a major number\n");
        return major_num;
    }
    printk(KERN_INFO "Dummy driver: Registered successfully with major number %d\n", major_num);

    return 0;
}

static void __exit dummy_exit(void){
    unregister_chrdev(major_num, DEVICE_NAME);
    printk(KERN_INFO "Dummy driver: Unregistered successfully\n");
}

module_init(dummy_init);
module_exit(dummy_exit);

