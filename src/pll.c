#include <stm32f401xc.h>

void pll_init(){


    /*
    freq_VCO = f_pllInput * (PLLN/PLLM)
             = 16MHz * (PLLN/PLLM)

    PLL output freq = VCO / PLLP

    ADCCLK max = 36MHz -> Needed PLL = 72MHz with 2 adc prescaler

    72MHz = VCO / PLLP = 16MHz * PLLN / (PLLM * PLLP)
    PLLM = 16   within 1-2 MHz
    PLLN = 288
    PLLP = 4
    */
    RCC -> PLLCFGR &= ~RCC_PLLCFGR_PLLP;
    RCC -> PLLCFGR |= (RCC_PLLCFGR_PLLP & (1 << 16)); // PLLP = 4
    
    RCC -> PLLCFGR &= ~RCC_PLLCFGR_PLLN;
    RCC -> PLLCFGR |= (RCC_PLLCFGR_PLLN & (288 << 6)); // PLLN = 288

    RCC -> PLLCFGR &= ~RCC_PLLCFGR_PLLM;
    RCC -> PLLCFGR |= (RCC_PLLCFGR_PLLM & 16); // PLLM = 16


    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH -> ACR |= FLASH_ACR_LATENCY_2WS;
    FLASH -> ACR |= FLASH_ACR_PRFTEN;

    RCC -> CR |= RCC_CR_PLLON;                  // On PLL
    while(!(RCC -> CR & RCC_CR_PLLRDY));        // Wait PLL stabilize
    RCC -> CFGR |= (RCC_CFGR_SW_1);             // use pll
    while ((RCC -> CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); // check flag

    return;
}