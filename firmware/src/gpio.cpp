#include "stm32h743xx.h"

#include "gpio.h"


void gpio_init()
{
    // LED R
    GPIOB->MODER &= ~GPIO_MODER_MODE0_Msk;
    GPIOB->MODER |= 0b01 << GPIO_MODER_MODE0_Pos;          // Set PB0 to output mode (0b01)

    // LED G
    GPIOE->MODER &= ~GPIO_MODER_MODE1_Msk;
    GPIOE->MODER |= 0b01 << GPIO_MODER_MODE1_Pos;          // Set PE1 to output mode (0b01)

    // LED B
    GPIOB->MODER &= ~GPIO_MODER_MODE14_Msk;
    GPIOB->MODER |= 0b01 << GPIO_MODER_MODE14_Pos;         // Set PB14 to output mode (0b01)

    uint32_t reg;

    // USART TX/RX
    reg = GPIOD->MODER;
    reg &= ~(GPIO_MODER_MODE8_Msk |
             GPIO_MODER_MODE9_Msk);
    reg |= (0b10 << GPIO_MODER_MODE8_Pos) |                // Set PD8 to alternate mode (0b10)
           (0b10 << GPIO_MODER_MODE9_Pos);                 // Set PD9 to alternate mode (0b10)
    GPIOD->MODER = reg;

    // USART TX/RX
    reg = GPIOD->AFR[1];
    reg &= ~(GPIO_AFRH_AFSEL8_Msk |
             GPIO_AFRH_AFSEL9_Msk);
    reg |= (7 << GPIO_AFRH_AFSEL8_Pos) |                   // Set PD8 as USART3 TX
           (7 << GPIO_AFRH_AFSEL9_Pos);                    // Set PD9 as USART3 RX
    GPIOD->AFR[1] = reg;

    // USB DP/DM/ID/V-sense
    reg = GPIOA->MODER;
    reg &= ~(GPIO_MODER_MODE12_Msk |
             GPIO_MODER_MODE11_Msk |
             GPIO_MODER_MODE10_Msk |
             GPIO_MODER_MODE9_Msk);
    reg |= (0b10 << GPIO_MODER_MODE12_Pos) |               // Set PA12 to alternative mode (0b10)
           (0b10 << GPIO_MODER_MODE11_Pos) |               // Set PA11 to alternative mode (0b10)
           (0b10 << GPIO_MODER_MODE10_Pos) |               // Set PA10 to alternative mode (0b10)
           (0b00 << GPIO_MODER_MODE9_Pos);                 // Set PA9 to input mode (0b00)
    GPIOA->MODER = reg;

    // USB DP/DM/ID
    reg = GPIOA->AFR[1];
    reg &= ~(GPIO_AFRH_AFSEL12_Msk |
             GPIO_AFRH_AFSEL11_Msk |
             GPIO_AFRH_AFSEL10_Msk);
    reg |= (10 << GPIO_AFRH_AFSEL12_Pos) |                 // Set PA12 as OTG_FS_DP
           (10 << GPIO_AFRH_AFSEL11_Pos) |                 // Set PA11 as OTG_FS_DM
           (10 << GPIO_AFRH_AFSEL10_Pos);                  // Set PA10 as OTG_FS_ID
    GPIOA->AFR[1] = reg;

    // USB V-Sense
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT9_Msk;                 // Set PA9 as output-drain (0b1)

    // USB ID
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD10_Msk;
    GPIOA->PUPDR |= (0b01 << GPIO_PUPDR_PUPD10_Pos);       // Enable pull-up (0b01) on PA10

    // USB DP/DM/ID
    reg = GPIOA->OSPEEDR;
    reg &= ~(GPIO_OSPEEDR_OSPEED12_Msk |
             GPIO_OSPEEDR_OSPEED11_Msk |
             GPIO_OSPEEDR_OSPEED10_Msk);
    reg |= (0b10 << GPIO_OSPEEDR_OSPEED12_Pos) |           // Set PA12 to high speed (0b10)
           (0b10 << GPIO_OSPEEDR_OSPEED11_Pos) |           // Set PA11 to high speed (0b10)
           (0b10 << GPIO_OSPEEDR_OSPEED10_Pos);            // Set PA10 to high speed (0b10)

    USB_OTG_FS->GCCFG |= USB_OTG_GCCFG_VBDEN;              // Enable VBUS sense (B device) via pin PA9
}
