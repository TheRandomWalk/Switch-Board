#include "stm32h743xx.h"

#include "led.h"


void led_set(bool g, bool y, bool r)
{
    GPIOB->BSRR |= (g ? GPIO_BSRR_BS0  : GPIO_BSRR_BR0);
    GPIOE->BSRR |= (y ? GPIO_BSRR_BS1  : GPIO_BSRR_BR1);
    GPIOB->BSRR |= (r ? GPIO_BSRR_BS14 : GPIO_BSRR_BR14);
}


void led_g(bool state)
{
    GPIOB->BSRR |= (state ? GPIO_BSRR_BS0  : GPIO_BSRR_BR0);
}


void led_y(bool state)
{
    GPIOE->BSRR |= (state ? GPIO_BSRR_BS1  : GPIO_BSRR_BR1);    
}


void led_r(bool state)
{
    GPIOB->BSRR |= (state ? GPIO_BSRR_BS14 : GPIO_BSRR_BR14);
}

