#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

    //--------------------------------------------------------------------+
    // Board Specific Configuration
    //--------------------------------------------------------------------+

    // RHPort number used for the device (default: 0)
    #ifndef BOARD_TUD_RHPORT
        #define BOARD_TUD_RHPORT 0
    #endif

    // RHPort max operational speed
    #ifndef BOARD_TUD_MAX_SPEED
        #define BOARD_TUD_MAX_SPEED OPT_MODE_DEFAULT_SPEED
    #endif

    //--------------------------------------------------------------------
    // COMMON CONFIGURATION
    //--------------------------------------------------------------------
    #define CFG_TUSB_MCU OPT_MCU_STM32H7
    #define CFG_TUSB_OS  OPT_OS_FREERTOS

    // can be defined by compiler in DEBUG build
    #ifndef CFG_TUSB_DEBUG
        #define CFG_TUSB_DEBUG 0
    #endif

    // Enable Device stack
    #define CFG_TUD_ENABLED 1

    // Default is max speed that hardware controller could support with on-chip PHY
    #define CFG_TUD_MAX_SPEED BOARD_TUD_MAX_SPEED

    /* USB DMA on some MCUs can only access a specific SRAM region with restriction on alignment.
    * Tinyusb use follows macros to declare transferring memory so that they can be put
    * into those specific section.
    * e.g
    * - CFG_TUSB_MEM SECTION : __attribute__ (( section(".usb_ram") ))
    * - CFG_TUSB_MEM_ALIGN   : __attribute__ ((aligned(4)))
    */
    #ifndef CFG_TUSB_MEM_SECTION
        #define CFG_TUSB_MEM_SECTION
    #endif

    #ifndef CFG_TUSB_MEM_ALIGN
        #define CFG_TUSB_MEM_ALIGN __attribute__ ((aligned(4)))
    #endif

    //--------------------------------------------------------------------
    // DEVICE CONFIGURATION
    //--------------------------------------------------------------------

    #ifndef CFG_TUD_ENDPOINT0_SIZE
        #define CFG_TUD_ENDPOINT0_SIZE 64
    #endif

    //------------- CLASS -------------//
    #define CFG_TUD_CDC                  1
    #define CFG_TUD_MSC                  1
    #define CFG_TUD_HID                  0
    #define CFG_TUD_MIDI                 0
    #define CFG_TUD_VENDOR               0
    // #define CFG_TUD_USBTMC               1
    // #define CFG_TUD_USBTMC_ENABLE_INT_EP 1
    // #define CFG_TUD_USBTMC_ENABLE_488    1

    // CDC FIFO size of TX and RX
    #define CFG_TUD_CDC_RX_BUFSIZE 64
    #define CFG_TUD_CDC_TX_BUFSIZE 64

    // CDC Endpoint transfer buffer size, more is faster
    #define CFG_TUD_CDC_EP_BUFSIZE 64

    // MSC Buffer size of Device Mass storage
    #define CFG_TUD_MSC_EP_BUFSIZE 512

#endif /* _TUSB_CONFIG_H_ */