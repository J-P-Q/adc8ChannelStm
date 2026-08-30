#include <stm32f401xc.h>
#include <stdint.h>

#include <tmr2.h>
#include <adc.h>
#include <uart.h>

volatile uint16_t msCounter = 0;

volatile uint16_t frame[8];
volatile uint8_t adcIndex = 0;
volatile uint8_t i = 0;

int main(void){
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    GPIOC -> MODER |= (1 << 13*2);
    GPIOC -> ODR &= ~(1 << 13);

    //adc_init();
    uart_init();
    tmr2_init();
    while(1){
        //GPIOC -> ODR |= (1 << 13);
        //uart_transmit(i);
        //i++;


    }

    return 0;
}

void TIM2_IRQHandler(void){
    if(TIM2 -> SR & TIM_SR_UIF){
        TIM2 -> SR &= ~TIM_SR_UIF;

        adc_convert();
        msCounter++;
        /* 
        TEST 1sec blink

        msCounter ++;
        if(msCounter > 1000){
            GPIOC -> ODR ^= (1 << 13);
            msCounter = 0;
        }    
        */
    }
    return;
}

void ADC_IRQHandler(void){
    if(ADC1 -> SR & ADC_SR_EOC){
        ADC1 -> SR &= ~ADC_SR_EOC;
        frame[adcIndex] = (uint16_t)(ADC1 -> DR);
        adcIndex = (adcIndex+ 1)%8;
        uart_transmit(msCounter);
    }
    return;
}

void USART1_IRQHandler(void){
    if(USART1 -> SR & USART_SR_TC){
        //if(count > 0){
            uart_transmit(0xAA);
        //}
    }

}