#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros

MODULE_LICENSE("ELTEX");
MODULE_AUTHOR("Gubinskii Alexandr");
MODULE_DESCRIPTION("just a |hello world| module");

static int __init hello_init(void)
{
    printk(KERN_INFO "I just wanna work in eltex!\n");
    return 0;
}

static void __exit hello_cleanup(void)
{
    printk(KERN_INFO "Oh no..Module was killed 0_0\n");
}

module_init(hello_init);
module_exit(hello_cleanup);