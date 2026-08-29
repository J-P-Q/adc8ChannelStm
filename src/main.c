#include <stm32f401xc.h>
#include <stdint.h>

void main(void){
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    while(1){

    }

    return;
}