#include "tim1.h"

void TIM1_Enable(void)
{
    RCC->APBENR2 |= RCC_APBENR2_TIM1EN;
    RCC->APBSMENR2 |= RCC_APBSMENR2_TIM1SMEN;
}

void TIM1_Init(const TIM1_ConfigTypeDef* TIM_ConfigStruct)
{
    TIM1->ARR = TIM_ConfigStruct->ARR;
    TIM1->PSC = TIM_ConfigStruct->PSC;
    TIM1->CCR1 = TIM_ConfigStruct->CCR1;
    TIM1->CCR2 = TIM_ConfigStruct->CCR2;
    TIM1->CCR3 = TIM_ConfigStruct->CCR3;
    TIM1->CCR4 = TIM_ConfigStruct->CCR4;
    TIM1->CCR5 = TIM_ConfigStruct->CCR5;
    TIM1->CCR6 = TIM_ConfigStruct->CCR6;
}

void TIM1_Start(void)
{
    TIM1->BDTR |= TIM_BDTR_MOE;
    TIM1->CR1 |= TIM_CR1_CEN;
}

void TIM1_SetARR(uint16_t ARRValue)
{
    TIM1->ARR = ARRValue;
}

void TIM1_SetPrescaler(uint16_t PSCValue)
{
    TIM1->PSC = PSCValue;
}

void TIM1_TRGO2_Config(TIM1_TRGO2_Source TRGO2Source)
{
    TIM1->CR2 |= TRGO2Source << TIM_CR2_MMS2_Pos;
}

void TIM1_EnableChannel(TIM1_CHANNEL channel)
{
    switch (channel)
    {
    case TIM1_CHANNEL_1:
        TIM1->CCER |= TIM_CCER_CC1E;
        break;
    case TIM1_CHANNEL_2:
        TIM1->CCER |= TIM_CCER_CC2E;
        break;
    case TIM1_CHANNEL_3:
        TIM1->CCER |= TIM_CCER_CC3E;
        break;
    case TIM1_CHANNEL_4:
        TIM1->CCER |= TIM_CCER_CC4E;
        break;
    case TIM1_CHANNEL_5:
        TIM1->CCER |= TIM_CCER_CC5E;
        break;
    case TIM1_CHANNEL_6:
        TIM1->CCER |= TIM_CCER_CC6E;
        break;
    }
}

void TIM1_EnableChannelOutput(TIM1_CHANNEL channel)
{
    switch (channel)
    {
    case TIM1_CHANNEL_1:
        TIM1->CCMR1 &= ~TIM_CCMR1_CC1S;
        break;
    case TIM1_CHANNEL_2:
        TIM1->CCMR1 &= ~TIM_CCMR1_CC2S;
        break;
    case TIM1_CHANNEL_3:
        TIM1->CCMR2 &= ~TIM_CCMR2_CC3S;
        break;
    case TIM1_CHANNEL_4:
        TIM1->CCMR2 &= ~TIM_CCMR2_CC4S;
        break;
    case TIM1_CHANNEL_5:
    case TIM1_CHANNEL_6:
        break;
    }
}

void TIM1_DisableChannel(TIM1_CHANNEL channel)
{
    switch (channel)
    {
    case TIM1_CHANNEL_1:
        TIM1->CCER &= ~TIM_CCER_CC1E;
        break;
    case TIM1_CHANNEL_2:
        TIM1->CCER &= ~TIM_CCER_CC2E;
        break;
    case TIM1_CHANNEL_3:
        TIM1->CCER &= ~TIM_CCER_CC3E;
        break;
    case TIM1_CHANNEL_4:
        TIM1->CCER &= ~TIM_CCER_CC4E;
        break;
    case TIM1_CHANNEL_5:
        TIM1->CCER &= ~TIM_CCER_CC5E;
        break;
    case TIM1_CHANNEL_6:
        TIM1->CCER &= ~TIM_CCER_CC6E;
        break;
    }
}

void TIM1_SetOCMode(TIM1_CHANNEL channel, TIM1_OC_ModeTypeDef mode)
{
    switch (channel)
    {
    case TIM1_CHANNEL_1:
        TIM1->CCMR1 |= mode << TIM_CCMR1_OC1M_Pos;
        break;
    case TIM1_CHANNEL_2:
        TIM1->CCMR1 |= mode << TIM_CCMR1_OC2M_Pos;
        break;
    case TIM1_CHANNEL_3:
        TIM1->CCMR2 |= mode << TIM_CCMR2_OC3M_Pos;
        break;
    case TIM1_CHANNEL_4:
        TIM1->CCMR2 |= mode << TIM_CCMR2_OC4M_Pos;
        break;
    case TIM1_CHANNEL_5:
        TIM1->CCMR3 |= mode << TIM_CCMR3_OC5M_Pos;
        break;
    case TIM1_CHANNEL_6:
        TIM1->CCMR3 |= mode << TIM_CCMR3_OC6M_Pos;
        break;
    default: __NOP();
    }
}
