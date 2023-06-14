#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "semphr.h"
#include "queue.h"
#include "task.h"
#include "timers.h"

#include "tusb.h"

#include "system.h"
#include "gpio.h"
#include "led.h"
#include "usart.h"
#include "systick.h"

#include "usb_tmc.h"

// Increase stack size when debug log is enabled
#define USBD_STACK_SIZE    (3*configMINIMAL_STACK_SIZE/2) * (CFG_TUSB_DEBUG ? 2 : 1)
#define CDC_STACK_SIZE      configMINIMAL_STACK_SIZE
#define TMC_STACK_SIZE      configMINIMAL_STACK_SIZE

StackType_t  usb_device_stack[USBD_STACK_SIZE];
StaticTask_t usb_device_taskdef;

StackType_t  cdc_stack[CDC_STACK_SIZE];
StaticTask_t cdc_taskdef;


void usb_device_task(void* param);
void cdc_task(void* params);
void tmc_task(void* params);

//--------------------------------------------------------------------+
// Main
//--------------------------------------------------------------------+

int main(void)
{
    exception_init();
    fpu_init();
    power_init();
    rcc_init();
    //systick_init();
    gpio_init();
    usart_init();

    const HeapRegion_t heap_region[] =
    {
        {reinterpret_cast<uint8_t*>(0x20000000UL), 0x20000},   // 128K DTCM
        {nullptr, 0}
    };

    vPortDefineHeapRegions(heap_region);
 
    xTaskCreate(usb_device_task, "USBD", USBD_STACK_SIZE, NULL, configMAX_PRIORITIES-1, NULL);
    xTaskCreate(cdc_task, "CDC", CDC_STACK_SIZE, NULL, configMAX_PRIORITIES-2, NULL);
    xTaskCreate(tmc_task, "TMC", TMC_STACK_SIZE, NULL, configMAX_PRIORITIES-2, NULL);

    vTaskStartScheduler();

    return 0;
}



// USB Device Driver task
// This top level thread process all usb events and invoke callbacks
void usb_device_task(void* param)
{
    (void) param;

    // init device stack on configured roothub port
    // This should be called after scheduler/kernel is started.
    // Otherwise it could cause kernel issue since USB IRQ handler does use RTOS queue API.
    tud_init(BOARD_TUD_RHPORT);

    // RTOS forever loop
    while (1)
    {
        // put this thread to waiting state until there is new events
        tud_task();

        // following code only run if tud_task() process at least 1 event
        tud_cdc_write_flush();
    }
}



//--------------------------------------------------------------------+
// USB CDC
//--------------------------------------------------------------------+
void cdc_task(void* params)
{
    (void) params;

    // RTOS forever loop
    while ( 1 )
    {
        // connected() check for DTR bit
        // Most but not all terminal client set this when making connection
        // if ( tud_cdc_connected() )
        {
            // There are data available
            while ( tud_cdc_available() )
            {
                uint8_t buf[64];

                // read and echo back
                uint32_t count = tud_cdc_read(buf, sizeof(buf));
                (void) count;

                // Echo back
                // Note: Skip echo by commenting out write() and write_flush()
                // for throughput test e.g
                //    $ dd if=/dev/zero of=/dev/ttyACM0 count=10000
                tud_cdc_write(buf, count);
            }

            tud_cdc_write_flush();
        }

        // For ESP32-Sx this delay is essential to allow idle how to run and reset watchdog
        vTaskDelay(1);
    }
}


void tmc_task(void* params)
{
    while (true)
    {
        usbtmc_app_task_iter();
        vTaskDelay(1);
    }
}