#ifndef USART_H
    #define USART_H


    #include <cstdint>

    // Initializes the peripheral
    void usart_init(void);

    // Check if TX FIFO is not full
    bool usart_tx_not_full(void); 

    // Block until character is transmitted
    void usart_tx(uint8_t c);

    // Check if RX FIFO is not empty
    bool usart_rx_not_empty(void);

    // Block until a character is received
    uint8_t usart_rx(void);


#endif