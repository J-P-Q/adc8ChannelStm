#include <stm32f401xc.h>
#include <stdint.h>

#include <tmr2.h>
#include <adc.h>

//volatile uint16_t msCounter = 0;

volatile uint16_t frame[8];
volatile uint8_t adcIndex = 0;

int main(void){
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    GPIOC -> MODER |= (1 << 13*2);

    adc_init();
    tmr2_init();
    while(1){


    }

    return 0;
}

void TIM2_IRQHandler(void){
    if(TIM2 -> SR & TIM_SR_UIF){
        TIM2 -> SR &= ~TIM_SR_UIF;

        adc_convert();
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

void ADC1_IRQHandler(void){
    if(ADC1 -> SR & ADC_SR_EOC){
        frame[adcIndex] = (uint16_t)(ADC1 -> DR);
        adcIndex = (adcIndex+ 1)%8;

    }
    return;
}