#ifndef __KERNEL__
#define __KERNEL__
#endif

#ifndef MODULE
#define MODULE
#endif

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
#include <asm/system.h> /* cli(), *_flags */
#include <asm/uaccess.h> /* copy_from/to_user */
#include <linux/interrupt.h>
#include <asm/hardware.h>
#include <asm/arch/gpio.h>
#include <linux/timer.h>



#define ACK 101
#define INT 28



//Function prototypes
static int mbta_open(struct inode *inode, struct file *filp);
static int mbta_release(struct inode *inode, struct file *filp);
static ssize_t mbta_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
static ssize_t mbta_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos);
static void mbta_cleanup(void);
static int mbta_init(void);
irqreturn_t gpio_irq0(int irq, void *dev_id, struct pt_regs *regs);
void interrupt_timer_callback(unsigned long);

//Sturctures used
struct file_operations mbta_fops = {
	read: mbta_read,
	write: mbta_write,
	open: mbta_open,
	release: mbta_release
};

//Global variables
static int mbta_major = 61;
static char *mbta_buffer;
static char display_message[128];
static int image_recieved = 0;
static unsigned capacity = 128;
static int mbta_len;
static unsigned bite = 128;

int count = 15;
static bool HIGH = true;
static bool LOW = false;
int period = 2;
int irq0 = gpio_to_irq(ACK);	


//Function definitions
static int mbta_init(void)
{	
	int result;

	printk("Welcome to MBTA Live Tracker\n");

	result = register_chrdev(mbta_major, "mbta", &mbta_fops);
	if (result < 0)
	{
		printk(KERN_ALERT
			"mbta: cannot obtain major number %d\n", mbta_major);
		return result;
	}

	/* Allocating mbta for the buffer */
	mbta_buffer = kmalloc(capacity, GFP_KERNEL); 
	if (!mbta_buffer)
	{ 
		printk(KERN_ALERT "Insufficient kernel memory\n"); 
		result = -ENOMEM;
		goto fail; 
	} 
	memset(mbta_buffer, 0, capacity);
	mbta_len = 0;	
	
	//gpio_direction_output(LED0, HIGH);
	gpio_direction_output(INT, LOW);
	gpio_direction_input(ACK);

	if(request_irq(irq0, &gpio_irq0, SA_INTERRUPT | SA_TRIGGER_RISING, "mbta", "return0") != 0 ) 
	{
                printk ( "irq0 not acquired \n" );
                return -1;
    }
	else
	{
                printk ( "irq0 acquired successfully \n");
	}

    
	return 0;

fail: 
	mbta_cleanup(); 
	return result;
}

static void mbta_cleanup(void)
{
	free_irq(irq0, "return0");
	printk(KERN_ALERT "IRQs removed\n");
	
	/* Freeing the major number */
	unregister_chrdev(mbta_major, "mbta");

	gpio_free(INT);
	gpio_free(ACK);

	printk(KERN_ALERT "Removing mbta module\n");

}


//IRQ --> called when Rasberry Pi sends an Acknowledgement
irqreturn_t gpio_irq0(int irq, void *dev_id, struct pt_regs *regs)
{
	
	//Habdling The acknowledgment Recieved
	image_recieved = 1;
	strcpy(display_message,"1");
	printk("Inside irq\nvalue = %d\n",image_recieved);
	return IRQ_HANDLED;
}


static int mbta_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static int mbta_release(struct inode *inode, struct file *filp)
{
	return 0;
}

//Read and Write functions --> Called when File operations are done from the lcd classes
static ssize_t mbta_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{

	if(image_recieved == 1)
	{
		image_recieved = 0;
		if(copy_to_user(buf, "display_message", 2))
		    return -EFAULT;
	}
		
	else
	{
		if (copy_to_user(buf, display_message, 2))
		return -EFAULT;
	}

	return count;
}


static ssize_t mbta_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	strcpy(display_message, "0");
	
	//sends an interrupt to rasberry pi for resding request from user 
	gpio_set_value(INT, HIGH);
	gpio_set_value(INT, LOW);
	return count;	
}


module_init(mbta_init);
module_exit(mbta_cleanup);

