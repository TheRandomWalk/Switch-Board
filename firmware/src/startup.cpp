#include "stm32h743xx.h"
#include "tusb.h"


#define STACK_POINTER (reinterpret_cast<void (*)(void)>(&_stack_pointer))


extern char _data_start;
extern char _data_end;
extern char _data_lma;
extern char _bss_start;
extern char _bss_end;
extern char _stack_pointer;


int main(void);

extern "C" void __libc_init_array();
extern "C" void __libc_fini_array();

extern "C" void __attribute__((weak)) default_handler();

extern "C" void __attribute__((weak)) NMI_Handler(void);
extern "C" void __attribute__((weak)) HardFault_Handler(void);
extern "C" void __attribute__((weak)) MemManage_Handler(void);
extern "C" void __attribute__((weak)) BusFault_Handler(void);
extern "C" void __attribute__((weak)) UsageFault_Handler(void);
extern "C" void __attribute__((weak)) SecureFault_Handler(void);
extern "C" void __attribute__((weak)) SVC_Handler(void);             // Overritten by FreeRTOS
extern "C" void __attribute__((weak)) DebugMon_Handler(void);
extern "C" void __attribute__((weak)) PendSV_Handler(void);          // Overritten by FreeRTOS
extern "C" void __attribute__((weak)) SysTick_Handler(void);         // Overritten by FreeRTOS

extern "C" void __attribute__((weak)) otg_fs_handler(void);          // TinyUSB


extern "C" void __attribute__((weak)) default_handler()
{
    while (true);
}


extern "C" void reset_handler(void) 
{
    for (char *p = &_bss_start; p < &_bss_end; p++) 
        *p = 0;

    for (char *out = &_data_start, *in = &_data_lma; out < &_data_end; out++, in++) 
        *out = *in;
    
    __libc_init_array();

    NVIC_SetPriority(OTG_FS_EP1_OUT_IRQn, 6);
    NVIC_SetPriority(OTG_FS_EP1_IN_IRQn, 6);
    NVIC_SetPriority(OTG_FS_WKUP_IRQn, 6);
    NVIC_SetPriority(OTG_FS_IRQn, 6);
    
    main();
    
    __libc_fini_array();
    while (true);
}


extern "C" void __attribute__((weak)) NMI_Handler(void) 
{
    while (true);
}


extern "C" void __attribute__((weak)) HardFault_Handler(void) 
{
    while (true);
}


extern "C" void __attribute__((weak)) MemManage_Handler(void)
{
    while (true);
}


extern "C" void __attribute__((weak)) BusFault_Handler(void)
{
    while (true);
}


extern "C" void __attribute__((weak)) UsageFault_Handler(void)
{
    while (true);
}


extern "C" void __attribute__((weak)) SecureFault_Handler(void)
{
    while (true);
}


extern "C" void __attribute__((weak)) SVC_Handler(void)
{
    while (true);
}


extern "C" void __attribute__((weak)) DebugMon_Handler(void)
{
    while (true);
}


extern "C" void __attribute__((weak)) PendSV_Handler(void)
{
    while (true);
}


extern "C" void __attribute__((weak)) SysTick_Handler(void)
{
    while (true);    
}


void otg_fs_handler(void)
{
    tud_int_handler(0);
}


__attribute__((section(".vector_table"))) void (*vector_table[256])(void) =
{
    STACK_POINTER,          // Stack pointer
    reset_handler,          // Reset
    NMI_Handler,            // NMI                     (non-maskable interrupts)
    HardFault_Handler,      // HardFault
    MemManage_Handler,      // MemManage               (memory managment)
    BusFault_Handler,       // BusFault                (prefetch fault / memory faccess fault)
    UsageFault_Handler,     // UsageFault              (undefined instruction or illegal state)
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    SVC_Handler,            // SVCall                  (service call)
    DebugMon_Handler,       // DebugMonitor
    0,                      // Reserved
    PendSV_Handler,         // PendSV                  (pendable request for system service)
    SysTick_Handler,        // SysTick                 (system tick timer)
    default_handler,        // WWDG1                   (window watchdog)
    default_handler,        // PVD_PVM                 (PVD through EXTI Line detection)
    default_handler,        // RTC_TAMP_STAMP_CSS_LSE  (tamper and timeStamps through the EXTI line)
    default_handler,        // RTC_WKUP                (wakeup through the EXTI line)
    default_handler,        // FLASH                   (flash memory)
    default_handler,        // RCC
    default_handler,        // EXTI0                   (EXTI Line0)
    default_handler,        // EXTI1                   (EXTI Line1)
    default_handler,        // EXTI2                   (EXTI Line2)
    default_handler,        // EXTI3                   (EXTI Line3)
    default_handler,        // EXTI4                   (EXTI Line4)
    default_handler,        // DMA1_STR0               (DMA1 Stream 0)
    default_handler,        // DMA1_STR1               (DMA1 Stream 1)
    default_handler,        // DMA1_STR2               (DMA1 Stream 2)
    default_handler,        // DMA1_STR3               (DMA1 Stream 3)
    default_handler,        // DMA1_STR4               (DMA1 Stream 4)
    default_handler,        // DMA1_STR5               (DMA1 Stream 5)
    default_handler,        // DMA1_STR6               (DMA1 Stream 6)
    default_handler,        // ADC1_2                  (ADC1 and ADC2)
    default_handler,        // FDCAN1_IT0              (FDCAN1 interrupt 0)
    default_handler,        // FDCAN2_IT0              (FDCAN2 interrupt 0)
    default_handler,        // FDCAN1_IT1              (FDCAN1 interrupt 1)
    default_handler,        // FDCAN2_IT1              (FDCAN2 interrupt 1)
    default_handler,        // EXTI9_5                 (EXTI Line[9:5])
    default_handler,        // TIM1_BRK                (TIM1 break)
    default_handler,        // TIM1_UP                 (TIM1 update)
    default_handler,        // TIM1_TRG_COM            (TIM1 trigger and commutation)
    default_handler,        // TIM1_CC                 (TIM1 capture / compare)
    default_handler,        // TIM2
    default_handler,        // TIM3
    default_handler,        // TIM4
    default_handler,        // I2C1_EV                 (I2C1 Event)
    default_handler,        // I2C1_ER                 (I2C1 Error)
    default_handler,        // I2C2_EV                 (I2C2 Event)
    default_handler,        // I2C2_ER                 (I2C2 Error)
    default_handler,        // SPI1
    default_handler,        // SPI2
    default_handler,        // USART1
    default_handler,        // USART2
    default_handler,        // USART3
    default_handler,        // EXTI15_10               (EXTI line[15:10])
    default_handler,        // RTC_ALARM               (RTC Alarm (A and B) through EXTI Line)
    0,                      // Reserved
    default_handler,        // TIM8_BRK_TIM12          (TIM8 break and TIM12)
    default_handler,        // TIM8_UP_TIM13           (TIM8 Update and TIM13)
    default_handler,        // TIM8_TRG_COM_TIM14      (TIM8 trigger / Commutation and TIM14)
    default_handler,        // TIM8_CC                 (TIM8 Capture / Compare)
    default_handler,        // DMA1_STR7               (DMA1 stream 7)
    default_handler,        // FMC
    default_handler,        // SDMMC1
    default_handler,        // TIM5
    default_handler,        // SPI3
    default_handler,        // UART4
    default_handler,        // UART5
    default_handler,        // TIM6_DAC                (TIM6 and DAC underrun)
    default_handler,        // TIM7
    default_handler,        // DMA2_STR0               (DMA2 stream 0)
    default_handler,        // DMA2_STR1               (DMA2 stream 1)
    default_handler,        // DMA2_STR2               (DMA2 stream 2)
    default_handler,        // DMA2_STR3               (DMA2 stream 3)
    default_handler,        // DMA2_STR4               (DMA2 stream 4)
    default_handler,        // ETH                     (Ethernet)
    default_handler,        // ETH_WKUP                (Ethernet wakeup through EXTI line)
    default_handler,        // FDCAN_CAL               (FDCAN calibration)
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    default_handler,        // DMA2_STR5               (DMA2 stream 5)
    default_handler,        // DMA2_STR6               (DMA2 stream 6)
    default_handler,        // DMA2_STR7               (DMA2 stream 7)
    default_handler,        // USART6
    default_handler,        // I2C3_EV                 (I2C3 event)
    default_handler,        // I2C3_ER                 (I2C3 error)
    default_handler,        // OTG_HS_EP1_OUT          (USB OTG HS end point 1 out)
    default_handler,        // OTG_HS_EP1_IN           (USB OTG HS end point 1 in)
    default_handler,        // OTG_HS_WKUP             (USB OTG HS wakeup through EXTI)
    default_handler,        // OTG_HS
    default_handler,        // DCMI
    default_handler,        // CRYPT
    default_handler,        // HASH_RNG                (HASH and RNG)
    default_handler,        // FPU
    default_handler,        // UART7
    default_handler,        // UART8
    default_handler,        // SPI4
    default_handler,        // SPI5
    default_handler,        // SPI6
    default_handler,        // SAI1
    default_handler,        // LTDC                    (LCD-TFT)
    default_handler,        // LTDC_Er                 (LCD-TFT error)
    default_handler,        // DMA2D
    default_handler,        // SAI2
    default_handler,        // QUADSPI
    default_handler,        // LPTIM1
    default_handler,        // CEC                     (HDMI_CEC)
    default_handler,        // I2C4_EV                 (I2C4 event)
    default_handler,        // I2C4_ER                 (I2C4 error)
    default_handler,        // SPDIF                   (SPDIFRX)
    default_handler,         // OTG_FS_EP1_OUT         (USB OTG FS end point 1 out)
    default_handler,         // OTG_FS_EP1_IN          (USB OTG FS end point 1 in)
    default_handler,         // OTG_FS_WKUP            (USB OTG FS wakeup through EXTI)
    otg_fs_handler,         // OTG_FS                  (USB OTG FS)
    default_handler,        // DMAMUX1_OV              (DMAMUX1 overrun)
    default_handler,        // HRTIM1_MST              (HRTIM master timer)
    default_handler,        // HRTIM1_TIMA             (HRTIM timer A)
    default_handler,        // HRTIM1_TIMB             (HRTIM timer B)
    default_handler,        // HRTIM1_TIMC             (HRTIM timer C)
    default_handler,        // HRTIM1_TIMD             (HRTIM timer D)
    default_handler,        // HRTIM1_TIME             (HRTIM timer E)
    default_handler,        // HRTIM1_FLT              (HRTIM fault)
    default_handler,        // DFSDM1_FLT0             (DFSDM filter0)
    default_handler,        // DFSDM1_FLT1             (DFSDM filter1)
    default_handler,        // DFSDM1_FLT2             (DFSDM filter2)
    default_handler,        // DFSDM1_FLT3             (DFSDM filter3)
    default_handler,        // SAI3
    default_handler,        // SWPMI1 
    default_handler,        // TIM15
    default_handler,        // TIM16
    default_handler,        // TIM17
    default_handler,        // MDIOS_WKUP              (MDIOS  wakeup)
    default_handler,        // MDIOS
    default_handler,        // JPEG
    default_handler,        // MDMA
    0,                      // Reserved
    default_handler,        // SDMMC2
    default_handler,        // HSEM0 
    0,                      // Reserved
    default_handler,        // ADC3
    default_handler,        // DMAMUX2_OVR             (DMAMUX2 overrun interrupt)
    default_handler,        // BDMA_CH0                (BDMA channel 0)
    default_handler,        // BDMA_CH1                (BDMA channel 1)
    default_handler,        // BDMA_CH2                (BDMA channel 2)
    default_handler,        // BDMA_CH3                (BDMA channel 3)
    default_handler,        // BDMA_CH4                (BDMA channel 4)
    default_handler,        // BDMA_CH5                (BDMA channel 5)
    default_handler,        // BDMA_CH6                (BDMA channel 6)
    default_handler,        // BDMA_CH7                (BDMA channel 7)
    default_handler,        // COMP                    (COMP1 and COMP2)
    default_handler,        // LPTIM2
    default_handler,        // LPTIM3
    default_handler,        // LPTIM4
    default_handler,        // LPTIM5
    default_handler,        // LPUART
    default_handler,        // WWDG1_RST               (window watchdog)
    default_handler,        // CRS                     (clock recovery system)
    default_handler,        // RAMECC                  (ECC diagnostic for D1-D3)
    default_handler,        // SAI4
    0,                      // Reserved
    0,                      // Reserved
    default_handler,        // WKUP                    (WKUP0 to WKUP5 pins)
};
