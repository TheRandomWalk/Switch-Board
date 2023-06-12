#include "Led.h"



// Invoked when device is mounted
extern "C" void tud_mount_cb(void)
{
    led_g(true);
}


// Invoked when device is unmounted (Does not work because of TinyUSB bug)
extern "C" void tud_umount_cb(void)
{
    led_g(false);
}


// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
extern "C" void tud_suspend_cb(bool remote_wakeup_en)
{
    led_g(false);
}


// Invoked when usb bus is resumed
extern "C" void tud_resume_cb(void)
{
}
