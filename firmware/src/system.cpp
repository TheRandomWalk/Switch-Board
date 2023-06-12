#include "stm32h743xx.h"

#include "system.h"


void exception_init()
{
    uint32_t reg = SCB->SHCSR;
    reg |= SCB_SHCSR_USGFAULTENA_Msk | SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_MEMFAULTENA_Msk;
    SCB->SHCSR = reg;
}


void fpu_init()
{
    SCB->CPACR |= (0b11 << 20) | (0b11 << 22);
}


void power_init()
{
    // Enable SYSCFG peripheral clock
    uint32_t apb4enr = RCC->APB4ENR;
    RCC->APB4ENR |= RCC_APB4ENR_SYSCFGEN;

    // Possible hardware bug: Even though the register has LDOEN = 1, it appears that it is not, and it needs to be set. Removing this, makes the VOSRDY loops loop forever.
    PWR->CR3 |= (PWR_CR3_SCUEN | PWR_CR3_LDOEN);

    // Enter VOS1 mode (required before entering VOS0 mode)
    PWR->D3CR |= PWR_D3CR_VOS_Msk;

    while (!(PWR->D3CR & PWR_D3CR_VOSRDY));

    // Enter VOS0 mode;
    SYSCFG->PWRCR |= SYSCFG_PWRCR_ODEN;

    while (!(PWR->D3CR & PWR_D3CR_VOSRDY));

    // Restore previous RCC APB4 clock register state
    RCC->APB4ENR = apb4enr;

    return;
}


void rcc_init()
{
    uint32_t reg;

    // Clock setup

    RCC->CR |= RCC_CR_HSEBYP | RCC_CR_HSEON;                         // Set HSE as external clock [8 Mhz]

    while (!(RCC->CR & RCC_CR_HSERDY));                              // Wait for HSE clock to be ready

    // PLL source

    reg = RCC->PLLCKSELR;
    reg &= ~(RCC_PLLCKSELR_PLLSRC_Msk |
             RCC_PLLCKSELR_DIVM1_Msk  |
             RCC_PLLCKSELR_DIVM2_Msk  |
             RCC_PLLCKSELR_DIVM3_Msk);
    reg |=       RCC_PLLCKSELR_PLLSRC_HSE |                          // HSE is the PLL source
           (1 << RCC_PLLCKSELR_DIVM1_Pos) |                          // Divider DIVM1 = 1
           (1 << RCC_PLLCKSELR_DIVM2_Pos) |                          // Divider DIVM2 = 1
           (1 << RCC_PLLCKSELR_DIVM3_Pos);                           // Divider DIVM3 = 1
    RCC->PLLCKSELR = reg;

    // PLL 1

    reg = RCC->PLLCFGR;
    reg &= ~(RCC_PLLCFGR_PLL1VCOSEL_Msk |
             RCC_PLLCFGR_PLL1RGE_Msk    |
             RCC_PLLCFGR_PLL1FRACEN_Msk |
             RCC_PLLCFGR_DIVP1EN_Msk    |
             RCC_PLLCFGR_DIVQ1EN_Msk    |
             RCC_PLLCFGR_DIVR1EN_Msk);
    reg |= (0    << RCC_PLLCFGR_PLL1VCOSEL_Pos) |                    // Wide VCO range: 192 - 960 Mhz (0)
           (0b10 << RCC_PLLCFGR_PLL1RGE_Pos)    |                    // PLL input frequency range: 4 - 8 Mhz (0b10)
           (0    << RCC_PLLCFGR_PLL1FRACEN_Pos) |                    // Disable fractional mode
           (1    << RCC_PLLCFGR_DIVP1EN_Pos)    |                    // DIVP1 divider output enabled
           (1    << RCC_PLLCFGR_DIVQ1EN_Pos)    |                    // DIVQ1 divider output enabled
           (1    << RCC_PLLCFGR_DIVR1EN_Pos);                        // DIVR1 divider output enabled
    RCC->PLLCFGR = reg;

    reg = RCC->PLL1DIVR;
    reg &= ~(RCC_PLL1DIVR_N1_Msk |
             RCC_PLL1DIVR_P1_Msk |
             RCC_PLL1DIVR_Q1_Msk |
             RCC_PLL1DIVR_R1_Msk);
    reg |= (59 << RCC_PLL1DIVR_N1_Pos) |                             // x60 PLL multiplication factor (59)
           ( 0 << RCC_PLL1DIVR_P1_Pos) |                             // DIVP1 = 1 (0)
           ( 0 << RCC_PLL1DIVR_Q1_Pos) |                             // DIVQ1 = 1 (0)
           ( 0 << RCC_PLL1DIVR_R1_Pos);                              // DIVR1 = 1 (0)
    RCC->PLL1DIVR = reg;

    RCC->CR |= RCC_CR_PLL1ON;                                        // Turn PLL1 on

    while (!(RCC->CR & RCC_CR_PLL1RDY));                             // Wait for PLL1 to be ready

    // PLL 2

    reg = RCC->PLLCFGR;
    reg &= ~(RCC_PLLCFGR_PLL2VCOSEL_Msk |
             RCC_PLLCFGR_PLL2RGE_Msk    |
             RCC_PLLCFGR_PLL2FRACEN_Msk |
             RCC_PLLCFGR_DIVP2EN_Msk    |
             RCC_PLLCFGR_DIVQ2EN_Msk    |
             RCC_PLLCFGR_DIVR2EN_Msk);
    reg |= (0    << RCC_PLLCFGR_PLL2VCOSEL_Pos) |                    // Wide VCO range: 192 - 960 Mhz (0)
           (0b10 << RCC_PLLCFGR_PLL2RGE_Pos)    |                    // PLL input frequency range: 4 - 8 Mhz (0b10)
           (0    << RCC_PLLCFGR_PLL2FRACEN_Pos) |                    // Disable fractional mode
           (1    << RCC_PLLCFGR_DIVP2EN_Pos)    |                    // DIVP2 divider output enabled
           (1    << RCC_PLLCFGR_DIVQ2EN_Pos)    |                    // DIVQ2 divider output enabled
           (1    << RCC_PLLCFGR_DIVR2EN_Pos);                        // DIVR2 divider output enabled
    RCC->PLLCFGR = reg;

    reg = RCC->PLL2DIVR;
    reg &= ~(RCC_PLL2DIVR_N2_Msk |
             RCC_PLL2DIVR_P2_Msk |
             RCC_PLL2DIVR_Q2_Msk |
             RCC_PLL2DIVR_R2_Msk);
    reg |= (39 << RCC_PLL2DIVR_N2_Pos) |                             // x40 PLL multiplication factor (39)
           ( 0 << RCC_PLL2DIVR_P2_Pos) |                             // DIVP2 = 1 (0)
           ( 0 << RCC_PLL2DIVR_Q2_Pos) |                             // DIVQ2 = 1 (0)
           ( 0 << RCC_PLL2DIVR_R2_Pos);                              // DIVR2 = 1 (0)
    RCC->PLL2DIVR = reg;

    RCC->CR |= RCC_CR_PLL2ON;                                        // Turn PLL2 on

    while (!(RCC->CR & RCC_CR_PLL2RDY));                             // Wait for PLL2 to be ready

    // PLL 3

    reg = RCC->PLLCFGR;
    reg &= ~(RCC_PLLCFGR_PLL3VCOSEL_Msk |
             RCC_PLLCFGR_PLL3RGE_Msk    |
             RCC_PLLCFGR_PLL3FRACEN_Msk |
             RCC_PLLCFGR_DIVP3EN_Msk    |
             RCC_PLLCFGR_DIVQ3EN_Msk    |
             RCC_PLLCFGR_DIVR3EN_Msk);
    reg |= (0    << RCC_PLLCFGR_PLL3VCOSEL_Pos) |                    // Wide VCO range: 192 - 960 Mhz (0)
           (0b10 << RCC_PLLCFGR_PLL3RGE_Pos)    |                    // PLL input frequency range: 4 - 8 Mhz (0b10)
           (0    << RCC_PLLCFGR_PLL3FRACEN_Pos) |                    // Disable fractional mode
           (1    << RCC_PLLCFGR_DIVP3EN_Pos)    |                    // DIVP3 divider output enabled
           (1    << RCC_PLLCFGR_DIVQ3EN_Pos)    |                    // DIVQ3 divider output enabled
           (1    << RCC_PLLCFGR_DIVR3EN_Pos);                        // DIVR3 divider output enabled
    RCC->PLLCFGR = reg;

    reg = RCC->PLL3DIVR;
    reg &= ~(RCC_PLL3DIVR_N3_Msk |
             RCC_PLL3DIVR_P3_Msk |
             RCC_PLL3DIVR_Q3_Msk |
             RCC_PLL3DIVR_R3_Msk);
    reg |= (19 << RCC_PLL3DIVR_N3_Pos) |                             // x20 PLL multiplication factor (19)
           ( 0 << RCC_PLL3DIVR_P3_Pos) |                             // DIVP1 = 1 (0)
           ( 0 << RCC_PLL3DIVR_Q3_Pos) |                             // DIVQ1 = 1 (0)
           ( 0 << RCC_PLL3DIVR_R3_Pos);                              // DIVR1 = 1 (0)
    RCC->PLL1DIVR = reg;

    RCC->CR |= RCC_CR_PLL3ON;                                        // Turn PLL3 on

    while (!(RCC->CR & RCC_CR_PLL3RDY));                             // Wait for PLL3 to be ready

    // System clock tree

    reg = RCC->D1CFGR;
    reg &= ~(RCC_D1CFGR_D1CPRE_Msk |
             RCC_D1CFGR_HPRE_Msk   |
             RCC_D1CFGR_D1PPRE_Msk); 
    reg |= RCC_D1CFGR_D1CPRE_DIV1 |                                  // D1CPRE  = 1
           RCC_D1CFGR_HPRE_DIV2   |                                  // HPRE    = 2
           RCC_D1CFGR_D1PPRE_DIV2;                                   // D1PPRE  = 2
    RCC->D1CFGR = reg;

    reg = RCC->D2CFGR;
    reg &= ~(RCC_D2CFGR_D2PPRE1_Msk |
             RCC_D2CFGR_D2PPRE2_Msk);
    reg |= RCC_D2CFGR_D2PPRE1_DIV2 |                                 // D2PPRE1 = 2
           RCC_D2CFGR_D2PPRE2_DIV2;                                  // D2PPRE2 = 2
    RCC->D2CFGR = reg;

    reg = RCC->D3CFGR;
    reg &= ~RCC_D3CFGR_D3PPRE_Msk;
    reg |= RCC_D3CFGR_D3PPRE_DIV2;                                   // D3PPRE = 2
    RCC->D3CFGR = reg;

    reg = RCC->CFGR;
    reg &= ~(RCC_CFGR_TIMPRE |                                       // Timers clocks prescaler selection
             RCC_CFGR_SW_Msk);
    reg |= RCC_CFGR_HRTIMSEL |                                       // High Resolution Timer clock prescaler selection
           RCC_CFGR_SW_PLL1;                                         // Set the system clock switch to PLL1 P clock
    RCC->CFGR = reg;

    while ((RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_PLL1);     // Wait until the switch to PLL1 finishes

    SystemCoreClock = 480'000'000;

    RCC->AHB4ENR |= 0b11'1111'1111;                                  // Enable GPIO A-K
    RCC->APB1LENR |= RCC_APB1LENR_USART3EN;                          // Enable USART3

    RCC->CR |= RCC_CR_HSI48ON;                                       // Enable HSI48
    while (!(RCC->CR & RCC_CR_HSI48RDY));                            // Wait until the HSI48 is ready

    RCC->D2CCIP2R |= (0b11 << RCC_D2CCIP2R_USBSEL_Pos);              // Enable hsi48_ck

    RCC->AHB1ENR |= RCC_AHB1ENR_USB1OTGHSEN |                        // Enable USB1 & USB2 
                    RCC_AHB1ENR_USB2OTGHSEN;

    PWR->CR3 |= PWR_CR3_USB33DEN;                                    // Enable USB voltage level detector
}
