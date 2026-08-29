#include <stm32f401xc.h>
#include <stdint.h>

#include <tmr2.h>

volatile uint16_t msCounter = 0;

int main(void){
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    GPIOC -> MODER |= (1 << 13*2);

    tmr2_init();
    while(1){


    }

    return 0;
}

void TIM2_IRQHandler(void){
    if(TIM2 -> SR & TIM_SR_UIF){
        TIM2 -> SR &= ~TIM_SR_UIF;
        
        msCounter ++;
        if(msCounter > 1000){
            GPIOC -> ODR ^= (1 << 13);
            msCounter = 0;
        }    
    }
}
