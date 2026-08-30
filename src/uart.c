#include <stm32f401xc.h>

void uart_init(void){
    RCC -> APB2ENR |= RCC_APB2ENR_USART1EN; 

    //Baud = f_ck / [8 * (2- OVER8) * USARTDIV]
    // 460.8Kbps -> 2.1875 in usartdiv
    //  - 2 = 2
    //  - 0.1875 = 3/16 -> 3
    USART1 -> BRR |= (0xFFF0 & (2 << 4));
    USART1 -> BRR |= (0x000F & 3);


    USART1 -> CR1 |= USART_CR1_TCIE;

    USART1 -> CR1 |= USART_CR1_TE;
    USART1 -> CR1 |= USART_CR1_UE;
    return;
}

void uart_transmit(uint8_t data){
    if(USART1 -> SR & USART_SR_TC){
        USART1 -> DR = data;
    }
    return;
}