#include <linux/kernel.h> 
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kref.h>
#include <linux/usb.h>
#include <linux/mutex.h>
#include <asm/uaccess.h>
#include <linux/mutex.h>

/* Define these values to match your devices */
#define TASS_USB_VENDOR_ID	0x2509
#define TASS_USB_PRODUCT_ID	0xabce
#define TASS_USB_MINOR_BASE	192

#define END_POINT_SEND		0x1
#define END_POINT_RECV		0x82

DEFINE_MUTEX(drvMutex);
/* table of devices that work with this driver */
static struct usb_device_id tass_table[] = {
	{USB_DEVICE(TASS_USB_VENDOR_ID, TASS_USB_PRODUCT_ID) },
	{ }					/* Terminating entry */
};

MODULE_DEVICE_TABLE (usb, tass_table);


/* Get a minor range for your devices from the usb maintainer */

/* Structure to hold all of our device specific stuff */
struct usb_tass {
	struct usb_device	*udev;			/* the usb device for this device */
	struct usb_interface	*interface;		/* the interface for this device */
	struct kref		kref;
	unsigned char		recv_buff[2048];
	unsigned char		send_buff[2048];
};

#define to_tass_dev(d) container_of(d, struct usb_tass, kref)

static struct usb_driver tass_driver;

static void tass_delete(struct kref *kref)
{
	struct usb_tass *dev = to_tass_dev(kref);

	usb_put_dev(dev->udev);
	kfree (dev);
}

static int tass_usb_open(struct inode *inode, struct file *file)
{
	struct usb_tass *dev;
	struct usb_interface *interface;
	int subminor;
	int retval = 0;

	subminor = iminor(inode);

	interface = usb_find_interface(&tass_driver, subminor);
	if (!interface) {
		printk("%s - error, can't find device for minor %d",
		     __FUNCTION__, subminor);
		retval = -ENODEV;
		goto exit;
	}

	dev = usb_get_intfdata(interface);
	if (!dev) {
		retval = -ENODEV;
		goto exit;
	}

	printk("retval: %d\n", retval);

	/* increment our usage count for the device */
	kref_get(&dev->kref);

	/* save our object in the file's private structure */
	file->private_data = dev;

exit:
	return retval;
}

static int tass_release(struct inode *inode, struct file *file)
{
	struct usb_tass *dev;

	dev = (struct usb_tass *)file->private_data;
	if (dev == NULL) return -ENODEV;

	/* decrement the count on our device */
	kref_put(&dev->kref, tass_delete);
	
	return 0;
}

static ssize_t tass_usb_read(struct file *file, char __user *buffer, size_t count, loff_t *ppos)
{
	//临时变量
	struct usb_tass	*dev = (struct usb_tass *)file->private_data;
	unsigned char	*mesg = NULL;
	unsigned int	size;
	int		i, real_len, rc;

	//参数检查
	if (2048 != count) return -EINVAL;
	mesg = dev->recv_buff;

	//接收设备发来的USB数据报(起始)
	rc = usb_bulk_msg(dev->udev, usb_rcvbulkpipe(dev->udev, END_POINT_RECV), mesg + 0, 512, &real_len, HZ * 150);
	if (0 != rc) 
	{
		printk(KERN_INFO "TASS : usb read time out,rc = %d\n",rc);
		return rc;
	}//USB传输失败
	size = ((mesg[14] << 8) ^ mesg[15]) + 16;//计算数据报总长度
	//printk(KERN_INFO "count = %d size = %d\n", count, size);//DEBUG
	if (2048 < size) return -EIO;//这绝不应该发生
	
	//接收设备发来的USB数据报(后续)
	for(i = 512; i < size; i += 512) {
		rc = usb_bulk_msg(dev->udev, usb_rcvbulkpipe(dev->udev, END_POINT_RECV), mesg + i, 512, &real_len, HZ * 1);
		if (0 != rc) return rc;//USB传输失败
	}

	//复制数据到用户态
	if (0 != copy_to_user(buffer, mesg, size)) return -EFAULT;
	
	//返回有效数据长度
	return size;
}

static ssize_t tass_usb_write(struct file *file, const char __user *buffer, size_t count, loff_t *ppos)
{
	//临时变量
	struct usb_tass	*dev = (struct usb_tass *)file->private_data;
	unsigned char	*mesg = NULL;
	unsigned int	size;
	int		real_len, rc;

	mesg = dev->send_buff;

	//输入检查
	memset(mesg, 0x00, 2048);
	if ((16 > count) || (2048 < count)) return -EINVAL;
	if (0 != copy_from_user(mesg, buffer, count)) return -EFAULT;
	size = ((mesg[14] << 8) ^ mesg[15]) + 16;
	//printk(KERN_INFO "count = %d size = %d\n", count, size);//DEBUG
	if (count != size) return -EINVAL;
	
	//发送USB数据报给设备EP1
	size = (size + 511) & 0xFE00;
	rc = usb_bulk_msg(dev->udev, usb_sndbulkpipe(dev->udev, END_POINT_SEND), mesg, size, &real_len, HZ * 1);
	if (0 != rc) return rc;

	//成功返回
	return count;
}

#ifdef HAVE_UNLOCKED_IOCTL
long tass_usb_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
#else
int tass_usb_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
#endif
{
	struct usb_tass	*dev = (struct usb_tass *)file->private_data;
	void __user*	argp = (void __user*)arg;
	unsigned char	*mesg = NULL;
	unsigned int	i, size;
	int		real_len, rc;

	//输入报文检查
	mesg = dev->send_buff;
	if (0 != copy_from_user(mesg, argp, 16)) return -EFAULT;
	size = ((mesg[14] << 8) ^ mesg[15]) + 16;
	if ((16 > size) || (size > 2048)) return -EINVAL;
	if (0 != copy_from_user(mesg, argp, size)) return -EFAULT;
	
	//发送USB数据报给设备
	size = (size + 511) & 0xFF00;
	rc = usb_bulk_msg(dev->udev, usb_sndbulkpipe(dev->udev, END_POINT_SEND), mesg, size, &real_len, HZ * 1);
	if (0 != rc) return rc;//USB传输失败

	//接收设备发来的USB数据报(起始)
	mesg = dev->recv_buff;
	rc = usb_bulk_msg(dev->udev, usb_rcvbulkpipe(dev->udev, END_POINT_RECV), mesg + 0, 512, &real_len, HZ * 150);
	if (0 != rc) 
  {
		printk(KERN_INFO "TASS : usb read time out,rc = %d\n",rc);
		return rc;
	}//USB传输失败
	size = ((mesg[14] << 8) ^ mesg[15]) + 16;//计算数据报总长度
	if ((16 > size) || (size > 2048)) return -EIO;//这绝不应该发生

	//接收设备发来的USB数据报(后续)
	for(i = 512; i < size; i += 512) {
		rc = usb_bulk_msg(dev->udev, usb_rcvbulkpipe(dev->udev, END_POINT_RECV), mesg + i, 512, &real_len, HZ * 1);
		if (0 != rc) return rc;//USB传输失败
	}

	//复制数据到用户态
	if (0 != copy_to_user(argp, mesg, size)) return -EFAULT;

	return 0;
}

static struct file_operations tass_fops = {
	.owner =	THIS_MODULE,
#ifdef HAVE_UNLOCKED_IOCTL
	.unlocked_ioctl = tass_usb_ioctl,
#else
	.ioctl =	tass_usb_ioctl,
#endif
	.read =		tass_usb_read,
	.write =	tass_usb_write,
	.open =		tass_usb_open,
	.release =	tass_release,
};

/* 
 * usb class driver info in order to get a minor number from the usb core,
 * and to have the device registered with devfs and the driver core
 */
static struct usb_class_driver tass_class = {
	.name = "tass_usb_card%d",
	.fops = &tass_fops,
	.minor_base = TASS_USB_MINOR_BASE,
};

static int tass_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	struct usb_tass *dev = NULL;
	int retval = -ENOMEM;

	/* allocate memory for our device state and initialize it */
	dev = kmalloc(sizeof(struct usb_tass), GFP_KERNEL);
	if (dev == NULL) {
		printk("Out of memory");
		goto error;
	}
	memset(dev, 0x00, sizeof (*dev));
	kref_init(&dev->kref);

	dev->udev = usb_get_dev(interface_to_usbdev(interface));
	dev->interface = interface;

	/* save our data pointer in this interface device */
	usb_set_intfdata(interface, dev);

	/* we can register the device now, as it is ready */
	retval = usb_register_dev(interface, &tass_class);
	if (retval) {
		/* something prevented us from registering this driver */
		printk("Not able to get a minor for this device.");
		usb_set_intfdata(interface, NULL);
		goto error;
	}

	/* let the user know what node this device is now attached to */
	printk(KERN_INFO "USB TASS device now attached to USBSkel-%d", interface->minor);
	return 0;

error:
	if (dev) kref_put(&dev->kref, tass_delete);
	return retval;
}

static void tass_disconnect(struct usb_interface *interface)
{
	struct usb_tass *dev;
	int minor = interface->minor;

	/* prevent taxx_open() from racing tass_disconnect() */
	mutex_lock(&drvMutex);
	
	dev = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);

	/* give back our minor */
	usb_deregister_dev(interface, &tass_class);
	
	dev->interface=NULL;

	mutex_unlock(&drvMutex);

	/* decrement our usage count */
	kref_put(&dev->kref, tass_delete);

	printk(KERN_INFO "USB TASS #%d now disconnected", minor);
}

static struct usb_driver tass_driver = {
	.name = "tass_usb",
	.id_table = tass_table,
	.probe = tass_probe,
	.disconnect = tass_disconnect,
};

static int __init usb_tass_init(void)
{
	int result;

	/* register this driver with the USB subsystem */
	result = usb_register(&tass_driver);
	if (result)
		printk("usb_register failed. Error number %d", result);

	return result;
}

static void __exit usb_tass_exit(void)
{
	/* deregister this driver with the USB subsystem */
	usb_deregister(&tass_driver);
}

module_init (usb_tass_init);
module_exit (usb_tass_exit);

MODULE_LICENSE("GPL");
