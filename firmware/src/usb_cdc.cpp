#include <stdint.h>

#include "Led.h"


// Invoked when cdc when line state changed e.g connected/disconnected
extern "C" void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts)
{
    // TODO set some indicator
    if (dtr)
    {
        // Terminal connected
        led_y(true);
    }
    else
    {
        // Terminal disconnected
        led_y(false);
    }
}


// Invoked when CDC interface received data from host
extern "C" void tud_cdc_rx_cb(uint8_t itf)
{
}