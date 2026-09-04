#include <stm32f401xc.h>
#include <stdint.h>

#include <tmr2.h>
#include <adc.h>
#include <uart.h>
#include <pll.h>

volatile uint16_t msCounter = 0;

volatile uint8_t ringBuffer[32];
volatile uint8_t adcIndex = 0;
volatile uint8_t uartIndex = 0;
volatile uint8_t count = 0;

volatile uint8_t data1 = 0;
volatile uint8_t data0 = 0;
volatile uint16_t data = 0;

volatile uint8_t testUart = 0xff;

int main(void){
    pll_init();
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    GPIOC -> MODER |= (1 << 13*2);
    GPIOC -> ODR &= ~(1 << 13);

    adc_init();
    uart_init();
    tmr2_init();
    while(1){
        


    }

    return 0;
}

void TIM2_IRQHandler(void){
    if(TIM2 -> SR & TIM_SR_UIF){
        TIM2 -> SR &= ~TIM_SR_UIF;

        adc_convert();

        uart_transmit(0xAA);
        NVIC_EnableIRQ(USART1_IRQn);
        
        /*
        //TEST 1sec blink

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

        data = ADC1 -> DR;
        
        data1 = (data >> 8) & 0xFF;
        data0 = data & 0x00FF;
        
        ringBuffer[adcIndex] = data1;
        count++;
        adcIndex = (adcIndex + 1)%32;

        ringBuffer[adcIndex] = data0;
        count++;
        adcIndex = (adcIndex + 1)%32; 
       
        NVIC_EnableIRQ(USART1_IRQn);
    }
    return;
}

void USART1_IRQHandler(void){
    if(USART1 -> SR & USART_SR_TC){
        if(count > 0){
            uart_transmit(ringBuffer[uartIndex]);
            uartIndex = (uartIndex + 1)%32;
            count --;
            testUart--;
        }
        else{
            NVIC_DisableIRQ(USART1_IRQn);
        }
    }

}