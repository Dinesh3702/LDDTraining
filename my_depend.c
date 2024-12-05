#include<linux/module.h>
#include<linux/uaccess.h>
#include<linux/init.h>
#include<linux/kernel.h>

extern void  func(void);
//static int val=100;
static int driver_init(void)
{
	pr_info("driver is opened1\n");
	func();
	return 0;
}
static void driver_exit(void)
{
 	pr_info("driver is closed1\n");
}
module_init(driver_init);
module_exit(driver_exit);


MODULE_AUTHOR("DINESH");
MODULE_DESCRIPTION("Basic Program in kernel");
MODULE_LICENSE("GPL");
