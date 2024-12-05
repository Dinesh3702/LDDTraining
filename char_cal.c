#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>//for adding file operations
#include <linux/uaccess.h> // For copy_to_user and copy_from_user

#define DEVICE_NAME "simple_device"
#define BUFFER_SIZE 1024
static int major_number;
static char device_buffer[BUFFER_SIZE];
static int open_count = 0;
int i1;
    int my_strcmp(char *s,char *s1)
    {
	    for(i1=0;s[i1];i1++)
	    {
		    if(s[i1]!=s1[i1]);
				    break;
	    }
	    if(s[i1]==s1[i1])
	         return 1;
		else
		return 0;
    }
    int add(int a,int b)
    {
    return a+b;
    }
    int sub(int a,int b)
    {
    return a-b;
    }
    int mul(int a,int b)
    {
    return a*b;
    }
    int div(int a,int b)
    {
    return a/b;
    }





// Function prototypes for device operations
static int device_open(struct inode *inode, struct file *file);//declaration of functions
static int device_close(struct inode *inode, struct file *file);
static ssize_t device_read(struct file *file, char __user *user_buffer, size_t size, loff_t *offset);
static ssize_t device_write(struct file *file, const char __user *user_buffer, size_t size, loff_t *offset);

// File operations structure
static struct file_operations fops = {//here fops is a variable to the structure
    .open = device_open,
    .release = device_close,
    .read = device_read,
    .write = device_write,//here we are assigning the function names to the function pointers
};

// Called when the device is opened
static int device_open(struct inode *inode, struct file *file) {
    open_count++;
    printk(KERN_INFO "simple_device: Device opened %d time(s)\n", open_count);
    return 0;
}

// Called when the device is closed
static int device_close(struct inode *inode, struct file *file) {
    printk(KERN_INFO "simple_device: Device closed\n");
    return 0;
}

// Called when data is read from the device
static ssize_t device_read(struct file *file, char __user *user_buffer, size_t size, loff_t *offset) {
    size_t len = strlen(device_buffer);

    if (*offset >= len) // Check if all data has been read
        return 0;

    if (size > len - *offset) // Adjust size to avoid reading beyond buffer
        size = len - *offset;

    if (copy_to_user(user_buffer, device_buffer + *offset, size)) {
        return -EFAULT;//here kernel will check the addresses,if the address is not available in kernel then kernel will produce an EFAULT.
    }

    *offset += size;
    printk(KERN_INFO "simple_device: Sent %zu bytes to the user\n", size);
    return size;
 }

// Called when data is written to the device
static ssize_t device_write(struct file *file, const char __user *user_buffer, size_t size, loff_t *offset) {
 int n=0,i,j,n1=0,k,l,res;
 char s[50],s1[50],s2[50];
    if (size > BUFFER_SIZE - 1) // Limit size to buffer capacity
        size = BUFFER_SIZE - 1;

    if (copy_from_user(device_buffer, user_buffer, size)) {
        return -EFAULT;
    }

   /* device_buffer[size] = '\0'; // Null-terminate the string
	for(i=0;device_buffer[i];i++)
		n=(n*10)+(device_buffer[i]-48);
		
	n1=n*n;
	for(i=0;n1;i++,n1/=10)
		device_buffer[i]=(n1%10)+48;
	device_buffer[i] = '\0';
	for(k=0,j=i-1;k<j;k++,j--)
	{
		char t=device_buffer[k];
		device_buffer[k]=device_buffer[j];
		device_buffer[j]=t;
		
	}*/
    
    for(i=0;device_buffer[i];i++)
    {
	    if(device_buffer[i]==',')
		    break;
	    else
		    s[j++]=device_buffer[i];
    }
    for(i=i+1;device_buffer[i];i++)
    {
	    if(device_buffer[i]==',')
		    break;
	    else
		    s1[k++]=device_buffer[i];
    }
    for(i=i+1;device_buffer[i];i++)
    {
	    if(device_buffer[i]==',')
		    break;
	    else
		    s2[l++]=device_buffer[i];
    }
    s[j]='\0';
    s1[k]='\0';
    s2[l]='\0';
    for(i=0;s[i];i++)
	    n=n*10+s[i]-48;
    for(i=0;s1[i];i++)
	    n1=n1*10+s1[i]-48;
    if(my_strcmp("add",s2))
	    res=add(n,n1);
    else if(my_strcmp("sub",s2))
	    res=sub(n,n1);
    else if(my_strcmp("mul",s2))
	    res=mul(n,n1);
    else if(my_strcmp("div",s2))
	    res=div(n,n1);

	for(i=0;res;i++,res/=10)
		device_buffer[i]=(res%10)+48;
	device_buffer[i] = '\0';
	for(k=0,j=i-1;k<j;k++,j--)
	{
		char t=device_buffer[k];
		device_buffer[k]=device_buffer[j];
		device_buffer[j]=t;
	}

    printk(KERN_INFO "simple_device: Received %zu bytes from the user\n", size);
    return size;
}

// Module initialization
static int __init simple_driver_init(void) {
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "simple_device: Failed to register device\n");
        return major_number;
    }
    printk(KERN_INFO "simple_device: Registered with major number %d\n", major_number);
    return 0;
}

// Module cleanup
static void __exit simple_driver_exit(void) {
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "simple_device: Unregistered device\n");
}

module_init(simple_driver_init);
module_exit(simple_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A Simple Linux Device Driver");
