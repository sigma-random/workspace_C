#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/stddef.h>
#include <linux/init.h>


MODULE_LICENSE("GPL");


#define QUEUE_NAME  "random_queue"
#define WORK_NAME  "random"


typedef struct workqueue_struct WorkQueue;
typedef struct work_struct Work;

/* define new work_struct */
typedef struct mywork_struct {
    
    struct  work_struct work;
    char*   workname;
   
}MyWork;

MyWork  mywork;
WorkQueue *workqueue;

/* work func */
void work_func(Work *work) {
    
    MyWork *mywork = container_of(work,typeof(*mywork),work);
    printk(KERN_EMERG "Hello, current work is %s\n",mywork->workname);

}

static __init int startMyWork(void) {

    workqueue = create_workqueue(QUEUE_NAME);
    if(!workqueue) {
        printk(KERN_ERR "create_workqueue error!\n");
        return -1;
    }
    
    mywork.workname = WORK_NAME;
    INIT_WORK(&(mywork.work),work_func);

    queue_work(workqueue,&(mywork.work));
    printk(KERN_EMERG "create_workqueue!\n");
    return 0;
}


static __exit void exitMyWork(void) {
    
    if(workqueue) {
        destroy_workqueue(workqueue);   
    }
    printk(KERN_EMERG "destory_workqueue!\n");

}



module_init(startMyWork);
module_exit(exitMyWork);

