#ifndef SYSTICK_H
    #define SYSTICK_H


    #include <cstdint>


    // Initialization of the SysTick peripheral (Do not use it when using FreeRTOS)
    void systick_init(void);

    // Returns time in seconds since the initialization of the systick counter
    uint64_t systick_s(void);

    // Returns time in milliseconds since the initialization of the systick counter
    uint64_t systick_ms(void);

    // Returns time in microseconds since the initialization of the systick counter
    uint64_t systick_us(void);


#endif