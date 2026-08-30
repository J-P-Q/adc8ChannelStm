#include <stm32f401xc.h>

void uart_init(void){
    RCC -> APB2ENR |= RCC_APB2ENR_USART1EN; 
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    /*
    AF7 = USART1 
    */
    GPIOB -> MODER |= (2 << 6*2);
    GPIOB -> AFR[0] |= (7 << 6*4);

    //Baud = f_ck / [8 * (2- OVER8) * USARTDIV]
    // 230Kbps -> 4.3125 in usartdiv
    //USART1 -> BRR |= (0xFFF0 & (4 << 4));
    //USART1 -> BRR |= (0x000F & 5);

    USART1 -> BRR |= (0xFFF0 & (104 << 4));
    USART1 -> BRR |= (0x000F & 3);

    //USART1 -> CR1 |= USART_CR1_TCIE;

    USART1 -> CR1 |= USART_CR1_TE;
    USART1 -> CR1 |= USART_CR1_UE;
    return;
}

void uart_transmit(uint8_t data){
    if(USART1 -> SR & USART_SR_TXE){
        USART1 -> DR = data;
    }
    return;
}