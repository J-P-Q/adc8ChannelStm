#include <stm32f401xc.h>

void tmr2_init(void){

    RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;


    TIM2 -> DIER |= TIM_DIER_UIE;   // update interrupts 

    TIM2 -> CNT = 0x00000000;

    // Prescaler
    // f_tmr = f_CK_PSC / (PSC + 1) = 16MHz/(psc + 1)
    // 1kHz sampling rate
    TIM2 -> PSC = 15999;
    TIM2 -> ARR = 0xffffffff;

    NVIC_EnableIRQ(TIM2_IRQn);

    TIM2 -> CR1 |= TIM_CR1_CEN;     // counter en


    return;
}