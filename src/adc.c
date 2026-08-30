#include <stm32f401xc.h>

void adc_init(void){
    RCC -> APB2ENR |= RCC_APB2ENR_ADC1EN;
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    volatile uint8_t i;
    for(i = 0; i<8; i++){
        GPIOA -> MODER |= (3 << i*2);
    }

    // 12 bit = 15 ADC_CLK cycles       00
    // 10 bit = 13 ADC_CLK cycles       01
    // 8 bit = 11 ADC_CLK_cycles        10
    //ADC1 -> CR1 |= ADC_CR1_RES_0;
    //ADC1 -> CR1 |= ADC_CR1_RES_1;

    /*
    Convertion + sampling time computation
    [(15 cycles + 480 cycles)/8MHz] * 8channels = 0.50ms
    [(15 cycles + 84 cycles)/8MHz] * 8 channels = 0.99us
    Cant say for sure min requirements of output impedance
    */
    // Using 84 cycles for sampling
    for(i = 0; i < 8; i++){
        ADC1 -> SMPR2 |= (4 << i*3);
    }

    ADC1 -> SQR1 |= (7 << 20);      // 7 conversions


    // channel sequence regs
    for(i = 0; i< 6; i++){
        ADC1 -> SQR3 |= (i << i*5);
    }
    for(i = 6; i < 8; i++){
        ADC1 -> SQR2 |= (i << (i-6)*5);
    }


    NVIC_EnableIRQ(ADC_IRQn);
    ADC1 -> CR1 |= ADC_CR1_EOCIE;   // INT EN
    ADC1 -> CR2 |= ADC_CR2_EOCS;    // INT per channel

    ADC1 -> CR1 |= ADC_CR1_SCAN;

    ADC1 -> CR2 |= ADC_CR2_ADON;
    return;   
}

void adc_convert(void){
    ADC1 -> CR2 |= ADC_CR2_SWSTART; //convert
    return;
}

