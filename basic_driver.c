#include<linux/module.h>
#include<linux/kernel.h>
//Module initialization function
static int __init basic_driver_init(void)
{
	printk(KERN_INFO "Basic Driver Loaded\n");
	return 0;//return 0 indicates succeful loading
}
//Module cleanup function
static void __exit basic_driver_exit(void)
{
	printk(KERN_INFO "Basic Driver Unloaded\n");
}
//Register module initialization and cleanup functions
module_init(basic_driver_init);
module_exit(basic_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Techdhaba");
MODULE_DESCRIPTION("A Basic linx device driver");
