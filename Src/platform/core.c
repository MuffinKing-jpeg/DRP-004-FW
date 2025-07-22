#include "stm32g0xx.h"
#include "../../Inc/platform/core.h"


void CORE_PWRInit(void)
{
    PWR->CR1 |= PWR_CR1_DBP;
    PWR->CR1 |= PWR_CR1_FPD_STOP;
    PWR->CR1 &= ~PWR_CR1_LPR;
}

void CORE_ClockInit(void)
{
    RCC->APBENR1 |= RCC_APBENR1_PWREN;
    RCC->APBENR2 |= RCC_APBENR2_SYSCFGEN;
    RCC->APBENR1 |= RCC_APBENR1_TIM3EN;

    RCC->APBSMENR2 |= RCC_APBSMENR1_TIM3SMEN;

    RCC->CR &= ~RCC_CR_HSIDIV;
    RCC->CFGR |= RCC_CFGR_PPRE;

    #ifdef BUILD_DEBUG
    CORE_AllowDebugInSTOP();
    #endif
}

void CORE_EnterSTOP(void)
{
    RCC->CR |= (3UL << RCC_CR_HSIDIV_Pos);      // Slow down to 2MHz
    RCC->CFGR &= ~RCC_CFGR_PPRE;                // Keep APB at 2MHz

    PWR->CR1 |= PWR_CR1_LPR;                    // Enable LP regulator
    PWR->CR1 &= ~PWR_CR1_LPMS;
    CORE_TickDelay(100);
    __WFI();
}

void CORE_ExitSTOP(void)
{
    PWR->CR1 &= ~PWR_CR1_LPR;                   // Disable LP regulator
    CORE_TickDelay(100);
    RCC->CR &= ~RCC_CR_HSIDIV;                  // Speed-up to 16MHz
    RCC->CFGR |= RCC_CFGR_PPRE;
}

void CORE_TickDelay(uint16_t ticks)
{
    for (uint16_t i = ticks; i > 0; i--);       // YOLO, LOL
}

void CORE_SetPA12Remap(void)
{
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_PA12_RMP;
}

#ifdef BUILD_DEBUG
void CORE_AllowDebugInSTOP(void)
{
    DBG->CR |= DBG_CR_DBG_STOP;
}

#endif
