#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/stddef.h>
#include <linux/list.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/timer.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/jiffies.h>


MODULE_LICENSE("GPL");


/**
 *  scheduled by  kernel thread "keventd" in default workqueue
 *
 *  test on linux-3.5.4 / linux-3.12
 */


#define MAX_THREAD      100
#define MAX_LIST_SIZE   800
#define TIMEOUT         1


typedef struct work_struct      Work;
typedef struct mywork_struct    MyWork;
typedef struct timer_list       MyTimer;
typedef struct mylist_struct    MyList;



struct mywork_struct {
    pid_t       pid;             /* current thread pid */
    spinlock_t  spinlock;        /* list spinlock */
    atomic_t    counter;         /* list counter */
    atomic_t    list_size;       /* list size */
    struct work_struct work;     /* work_struct */
};


struct mylist_struct {
    int id;                     /* id */
    struct list_head list;      /* list_head */
};


static DEFINE_SEMAPHORE(sem);   /* semaphore */
static MyWork  mywork;          /* work queue*/
static LIST_HEAD(mine);         /* list head */
static MyTimer mytimer;         /* timmer */


//########################################################//

static void qt_task(unsigned long);
static void work_func(Work*);
static int  sharelist(void*);
static void start_work(void);
static void share_init(void);
static void share_exit(void);

//########################################################//


static __init 
int startModule(void) {
   
    printk(KERN_INFO "start sharelist module!\n"); 
    share_init();
    start_work();
    return 0;
}


static __exit 
void exitModule(void) {

    share_exit();
    printk(KERN_INFO "\nexit sharelist module!\n");

}


/* init func*/
static 
void share_init(void) {
    
    spin_lock_init(&(mywork.spinlock));
    atomic_set(&(mywork.counter),0);
    atomic_set(&(mywork.list_size),0);
    INIT_WORK(&(mywork.work), work_func);
    setup_timer(&mytimer, qt_task, (unsigned long)&(mywork.work));
    add_timer(&mytimer);
}

/* exit func*/
static 
void share_exit(void) {

    struct list_head *prev = NULL;
    struct list_head *next = NULL;
    MyList *p = NULL;

    printk(KERN_INFO "\n########## start to delete sharelist ##########\n\n");
    
    del_timer(&mytimer);
    spin_lock(&(mywork.spinlock));

    list_for_each_safe(prev, next, &mine) {
        p = list_entry(prev, typeof(*p), list);
        if(p) {
            list_del(prev);
            printk(KERN_INFO "########## [share_exit] List Del :%d\n", p->id);
            kfree(p);
        }

    }

    spin_unlock(&(mywork.spinlock));
    printk(KERN_INFO "\n\nsharelist is empty now!\n");

}


/* work func */
static 
void work_func(Work *work) {
    
    struct task_struct *task = NULL;

    MyWork *mywork = container_of(work,typeof(*mywork),work);

    /* create a thread to operate list by kerner_thread*/
    // kernel_thread(sharelist,NULL,CLONE_KERNEL | SIGCHLD);
    task = kthread_run(sharelist,(void*)work,"sharelist-thread");
    if( !task) {
        printk(KERN_ERR "kernel_thread error!\n");
        return;
    }

    mywork->pid = task->pid;
    
    //printk(KERN_INFO "********** create thread --> pid =  %d\n",task->pid);
    up(&sem);

}


/* schedule work by keventd*/
static 
void start_work(void) {

    int i;
    if(&(mywork.work)) {
        for(i = 0; i<MAX_THREAD; i++) { // launch 100 thread
            down(&sem);
            schedule_work(&(mywork.work));
        }
    }

}


/* sleep */
static 
void _sleep(int timeout) {
    set_current_state(TASK_INTERRUPTIBLE);
    schedule_timeout(timeout*HZ);
}


/* thread func*/
static 
int sharelist(void* data) {

    MyList *p;
    Work *work = (Work*)data;
    MyWork *mywork = container_of(work,typeof(*mywork),work);

    spin_lock(&(mywork->spinlock));
    
    if(atomic_read(&(mywork->list_size)) <= MAX_LIST_SIZE) {

        if(NULL == (p = kmalloc(sizeof(MyList), GFP_KERNEL))) {
            printk(KERN_ERR "kmalloc failed!\n");
            return -ENOMEM;
        }
        p->id = atomic_read(&(mywork->counter));
        list_add(&(p->list),&mine); /* add to mine list*/
        atomic_inc(&(mywork->counter));
        atomic_inc(&(mywork->list_size));
        printk(KERN_INFO "$$$$$$$$$$ [sharelist thread] pid = %d  List Add :%d\n",mywork->pid, p->id);

    }else {

        p = list_entry(mine.prev, typeof(*p), list);
        if(p) {
            list_del(mine.prev);
            atomic_dec(&(mywork->list_size));
            printk(KERN_INFO "[sharelist thread] pid = %d  List Del :%d\n",mywork->pid, p->id);
            kfree(p);
        }
    }

    spin_unlock(&(mywork->spinlock));

    return 0;
}

/* timmer func*/
static
void qt_task(unsigned long data) {
   
    
    MyWork *mywork = container_of((Work*)data,typeof(*mywork),work);
    MyList *p;
    spin_lock(&(mywork->spinlock));
    if(!list_empty(&mine)) {
        p = list_entry(mine.next, typeof(*p), list);
        if(p) {
            list_del(mine.next);
            atomic_dec(&(mywork->list_size));
            printk(KERN_INFO "@@@@@@@@@@ [qt_task]   List Del :%d \n", p->id);
            kfree(p);
        }
    }
    spin_unlock(&(mywork->spinlock));
    mod_timer(&mytimer,jiffies+1);
}

module_init(startModule);
module_exit(exitModule);

