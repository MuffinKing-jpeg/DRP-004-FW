#include "../Inc/dmamux.h"

void DMAMUX_Enable()
{
    RCC->AHBENR  |= RCC_AHBENR_DMA1EN;
}

void DMAMUX_SetReqID(DMAMUX_Channel_TypeDef* channel, DMAMUX_RequestID id)
{
    channel->CCR &= ~ DMAMUX_CxCR_DMAREQ_ID_Msk;
    channel->CCR |= id << DMAMUX_CxCR_DMAREQ_ID_Pos;
}

void DMAMUX_Disable()
{
    RCC->AHBENR  &= ~RCC_AHBENR_DMA1EN;
}
