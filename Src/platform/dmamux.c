#include "dmamux.h"

void DMAMUX_Enable(void)
{
    RCC->AHBENR  |= RCC_AHBENR_DMA1EN;
}

void DMAMUX_SetReqID(DMAMUX_Channel_TypeDef* channel, const DMAMUX_RequestID id)
{
    channel->CCR &= ~ DMAMUX_CxCR_DMAREQ_ID_Msk;
    channel->CCR |= id << DMAMUX_CxCR_DMAREQ_ID_Pos;
}

void DMAMUX_Disable(void)
{
    RCC->AHBENR  &= ~RCC_AHBENR_DMA1EN;
}
