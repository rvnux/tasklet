#include <linux/module.h>  /* Needed by all modules */
#include <linux/kernel.h>  /* Needed for KERN_ALERT */
#include <linux/types.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/delay.h>

char my_tasklet_data[]="my_tasklet_function was called";



/* Bottom Half Function */
void my_tasklet_function( unsigned long data )
{
				int pid;

				printk(KERN_EMERG "%s\n", (char *)data);
        //schedule();
				//msleep(1);
 					pid = current->pid; 
					printk(KERN_EMERG "pid of tasklet  =%d name =%s\n", pid, current->comm);
				return;
}


DECLARE_TASKLET(my_tasklet, my_tasklet_function, (unsigned long) &my_tasklet_data );
int init_module(void)
{

				int pid;

				pid = current->pid; 
				printk(KERN_EMERG "pid of module  =%d\n", pid);
				/* Schedule the Bottom Half */
				tasklet_schedule( &my_tasklet );
				return 0;
}


void cleanup_module(void)
{
				printk(KERN_EMERG "Goodbye :)\n");
				/* Stop the tasklet before we exit */
				tasklet_kill( &my_tasklet );
}  

MODULE_LICENSE("GPL");
