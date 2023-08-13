#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/kmod.h>		   //for the call_usermodehelper function

#define VENDOR_ID_USB 0x03f0       // vendor ID of the currently used usb
#define PRODUCT_ID_USB 0x2d40	   // product ID of the currently used usb

// calls the below function when usb is connected to the device
static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    static char *argv[] = { "root/usbtest/unlocking.sh", NULL }; // path to the script being executed
    static char *envp[] = { "HOME=/", "TERM=linux", "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL }; // the environment variables to be set for the program being executed.
    int ret;
    printk(KERN_INFO "Pen i/f probed\n");
    ret = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC); // calls the script which unlocks this zipfile
    if (ret < 0) {
        printk(KERN_ERR "Failed to execute script: %d\n", ret);
        return ret;
    }    
    printk(KERN_INFO "Script executed successfully\n");
    return 0;
}
// calls the below function when usb is disconnected from the device
static void pen_disconnect(struct usb_interface *interface)
{
    static char *argv[] = { "root/usbtest/locking.sh", NULL }; // path to the script being executed
    static char *envp[] = { "HOME=/", "TERM=linux", "PATH=/sbin:/bin:/usr/sbin:/usr/bin",NULL }; // the environment variables to be set for the program being executed.
    int ret = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC); // calls this script which locks this zipfile
    if (ret < 0) {
        printk(KERN_ERR "Failed to execute script: %d\n", ret);
        return;
    }
    printk(KERN_INFO "Script executed successfully\n"); 
    printk(KERN_INFO "Pen i/f disconnected\n");
}

static struct usb_device_id pen_table[] =
    {
        {USB_DEVICE(VENDOR_ID_USB, PRODUCT_ID_USB)},  // adds this usb with the specified vendor id and product id to the pen_table
        {} // to show that this entry is terminated
};
MODULE_DEVICE_TABLE(usb, pen_table); // creates a device id table called pen_table and associates it with the USB system

static struct usb_driver pen_driver =
    {
        .name = "OSUSB",
        .probe = pen_probe,
        .disconnect = pen_disconnect,
        .id_table = pen_table,
};// details of the object "pen_driver"

static int __init pen_init(void)
{
    return usb_register(&pen_driver);
    // when this function is called the "pen_driver" object is registered with usb subsystem
    // allowing it to handle communication with the USB device.
}

static void __exit pen_exit(void)
{
    usb_deregister(&pen_driver);
    // this function deregisters the "pen_driver" object from the usb subsystem
}

module_init(pen_init); // function called when insmod command is used
module_exit(pen_exit); // function called whne rmmmod command is used

MODULE_LICENSE("GPL"); // to avoid "tainting kernel" warning
MODULE_AUTHOR("OS Group 9");
MODULE_DESCRIPTION("USB Device Driver");
