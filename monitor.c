#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "container_monitor"
#define IOCTL_REGISTER _IOW('a','a',int*)

static int major;
static int monitored_pid;

// ioctl handler
static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    if (cmd == IOCTL_REGISTER) {
        copy_from_user(&monitored_pid, (int*)arg, sizeof(int));
        printk("Monitoring PID: %d\n", monitored_pid);
    }
    return 0;
}

// file operations
static struct file_operations fops = {
    .unlocked_ioctl = device_ioctl,
};

// init
static int __init monitor_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    printk("Monitor module loaded. Major: %d\n", major);
    return 0;
}

// exit
static void __exit monitor_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk("Monitor module removed\n");
}

module_init(monitor_init);
module_exit(monitor_exit);

MODULE_LICENSE("GPL");
