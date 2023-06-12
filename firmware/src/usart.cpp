#include "stm32h743xx.h"

#include "usart.h"


void usart_init(void)
{
    uint32_t reg;
    
    USART3->CR1 &= USART_CR1_UE;                           // Disable USART before configuring it    

    reg = USART3->CR1;
    reg &= ~(USART_CR1_M1_Msk | 
             USART_CR1_M0_Msk |
             USART_CR1_OVER8_Msk |
             USART_CR1_FIFOEN_Msk);
    reg |= (0 << USART_CR1_M1_Pos) |                       // 1 start bit, 8 Data bits (M[1:0] = 0b00)
           (0 << USART_CR1_M0_Pos) |
           (0 << USART_CR1_OVER8_Pos) |                    // Oversampling by 16 (0)
           (1 << USART_CR1_FIFOEN_Pos);                    // Enable FIFO
    USART3->CR1 = reg;

    reg = USART3->BRR;
    reg &= ~(USART_BRR_DIV_MANTISSA_Msk |
             USART_BRR_DIV_FRACTION_Msk);
    reg |= 120 << USART_BRR_DIV_FRACTION_Pos;              // USARTDIV = 120'000'000 / 1'000'000 = 120
    USART3->BRR = reg;

    reg = USART3->CR2;
    reg &= ~(USART_CR2_STOP_Msk);
    reg |= (0 << USART_CR2_STOP_Pos);                      // 1 stop bit (0b00)
    USART3->CR2 = reg;

    USART3->CR1 |= USART_CR1_UE;                           // Enable USART

    USART3->CR1 |= USART_CR1_TE |                          // Enable transmitter and send IDLE frame
                   USART_CR1_RE;                           // Enable receiver
}


bool usart_tx_not_full(void)
{
    return USART3->ISR & USART_ISR_TXE_TXFNF;
}


void usart_tx(uint8_t c)
{
    while (!(USART3->ISR & USART_ISR_TXE_TXFNF));
    USART3->TDR = static_cast<uint32_t>(c);
}


bool usart_rx_not_empty(void)
{
    return USART3->ISR & USART_ISR_RXNE_RXFNE;
}


uint8_t usart_rx(void)
{
    while (!(USART3->ISR & USART_ISR_RXNE_RXFNE));
    return static_cast<uint8_t>(USART3->RDR);
}
