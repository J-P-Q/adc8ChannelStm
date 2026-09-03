#include <stm32f401xc.h>

void clockTree_init(){

    RCC -> CFGR |= (RCC_CFGR_SW_1); // PLL
    return;
}