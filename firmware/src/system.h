#ifndef SYSTEM_H
    #define SYSTEM_H


    #include <cstdint>


    // Enable MemManage, BusFault and UsageFault exception handling
    void exception_init();

    // Enable single and double precision FPUs
    void fpu_init();

    // Set power to VOS0, so that the MCU can run at 480 MHz 
    void power_init();

    // Set clocks and enable peripherals 
    void rcc_init();


#endif