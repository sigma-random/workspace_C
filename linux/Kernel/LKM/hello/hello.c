#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>



void func_test(void ) {

    printk(KERN_EMERG "Hello, World!\n");

}
EXPORT_SYMBOL(func_test);


static int __init hello_init(void) {

    printk(KERN_EMERG "Hello, World!\n");
    return 0;
}

static void __exit hello_exit(void) {

    printk(KERN_EMERG "Good Bye!\n");
}


module_init(hello_init);
module_exit(hello_exit);
