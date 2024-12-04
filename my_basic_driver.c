#include<linux/module.h>
#include<linux/uaccess.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/moduleparam.h>
static int val=200;
void func(void);

//EXPORT_SYMBOL(func);

//module_param(val,int,S_IRUGO);

static int driver_init(void)
{
	pr_info("driver is opened\n");
	func();
	return 0;
}
static void driver_exit(void)
{
 	pr_info("driver is closed\n");
}
module_init(driver_init);
module_exit(driver_exit);


void func(void)
{
	printk("func is called\n");
	printk("val=%d\n",val);
}


MODULE_AUTHOR("DINESH");
MODULE_DESCRIPTION("Basic Program in kernel");
MODULE_LICENSE("GPL");
