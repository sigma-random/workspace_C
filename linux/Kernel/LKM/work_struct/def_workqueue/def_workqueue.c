#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/stddef.h>
#include <linux/init.h>


MODULE_LICENSE("GPL");


/**
 *
 *
 *  scheduled by default kernel thread "keventd"
 *
 *
 */


#define WORK_NAME  "random"


typedef struct work_struct Work;

/* define new work_struct */
typedef struct mywork_struct {
    
    struct  work_struct work;
    char*   workname;
   
}MyWork;

MyWork  mywork;

/* work func */
void work_func(Work *work) {
    
    MyWork *mywork = container_of(work,typeof(*mywork),work);
    printk(KERN_EMERG "Hello, current work is %s\n",mywork->workname);

}

static __init int startMyWork(void) {

    
    mywork.workname = WORK_NAME;
    INIT_WORK(&(mywork.work),work_func);

    schedule_work(&(mywork.work));
    
    printk(KERN_EMERG "create_workqueue!\n");
    return 0;
}


static __exit void exitMyWork(void) {
    
    printk(KERN_EMERG "remove workqueue mod!\n");

}



module_init(startMyWork);
module_exit(exitMyWork);

