#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
 
static int len,temp;
static char *msg;
 
ssize_t read_proc(struct file *filp, char *buf, size_t count, loff_t *offp ) {
    if(count > temp) {
        count = temp;
    }
    temp = temp - count;
    //copy_to_user(buf, msg, count);
    if (copy_to_user(buf, msg, count) != 0) { //т.к. фукнция возвращает 0, если все байты скопированы успешно, можно просто добавить проверку
        return -EFAULT;
    }
    if(count == 0)
        temp = len;
    return count;
}
 
ssize_t write_proc(struct file *filp, const char *buf, size_t count, loff_t *offp) {
    //copy_from_user(msg, buf, count);
    if (copy_from_user(msg, buf, count) != 0) { //т.к. фукнция возвращает 0, если все байты скопированы успешно, можно просто добавить проверку
        return -EFAULT;
    }
    len = count;
    temp = len;
    return count;
}
 
static const struct proc_ops proc_fops = {
    proc_read: read_proc,
    proc_write: write_proc,
};
 
void create_new_proc_entry(void) { //use of void for no arguments is compulsory now
    proc_create("proc", 0, NULL, &proc_fops);
    msg = kmalloc(10 * sizeof(char), GFP_KERNEL);
}
 
int proc_init (void) {
    create_new_proc_entry();
    return 0;
}
 
void proc_cleanup(void) {
    remove_proc_entry("hello", NULL);
    kfree(msg);
}
 
MODULE_LICENSE("Eltex");
MODULE_AUTHOR("Gubinskii Alexandr");
module_init(proc_init);
module_exit(proc_cleanup);