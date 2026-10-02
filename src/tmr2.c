#include <stm32f401xc.h>

void tmr2_init(void){

    RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;


    TIM2 -> DIER |= TIM_DIER_UIE;   // update interrupts 

    TIM2 -> CNT = 0x00000000;

    // Prescaler
    // f_CK_CNT = f_CK_PSC / (PSC + 1) = 72MHz/(psc + 1)
    // 10kHz max sampling freq
    TIM2 -> PSC = 7199;

    // Sampling Freq 1kHz (1ms)
    // period = (ARR + 1) / 10kHz
    TIM2 -> ARR = 4;

    NVIC_EnableIRQ(TIM2_IRQn);

    TIM2 -> CR1 |= TIM_CR1_CEN;     // counter en


    return;
}