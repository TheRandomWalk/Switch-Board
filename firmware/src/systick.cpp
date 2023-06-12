#include "stm32h743xx.h"

#include "config.h"
#include "systick.h"


namespace
{
    uint64_t load;
    volatile uint64_t systick_counter_ = 0;
}


void systick_handler(void)
{
    systick_counter_++;
};


// FreeRTOS tick hook
extern "C" void vApplicationTickHook(void)
{
    systick_handler();
}


void systick_init(void)
{
    load = (SystemCoreClock / SYSTICK_FREQUENCY - 1);

    SysTick->LOAD = load;                                            // Reload value (24 bits)
    SysTick->VAL = 0;                                                // Current value initialization
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk  |                      // Enable the counter
                     SysTick_CTRL_TICKINT_Msk |                      // Generate SysTick exception when it reaches 0
                     SysTick_CTRL_CLKSOURCE_Msk;                     // Use processor clock
}


uint64_t systick_s(void)
{
    return systick_us() / 1'000'000;
}


uint64_t systick_ms(void)
{
    return systick_us() / 1'000;
}


uint64_t systick_us(void)
{
    uint64_t t0 = systick_counter_;
    uint64_t t1;
    uint64_t val;

    while (true)
    {
        val = SysTick->VAL;
        t1 = systick_counter_;

        if (t0 == t1)
            break;
        else
            t0 = t1;
    }
    load = (SystemCoreClock / SYSTICK_FREQUENCY - 1);
    return (systick_counter_ * (load + 1) + (load - val)) / (SystemCoreClock / 1'000'000);
}
