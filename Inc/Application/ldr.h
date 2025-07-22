#ifndef __LDR_H
#define __LDR_H

#include "stm32g0xx.h"
#include "../platform/adc.h"
#include "../platform/dmamux.h"
#include "../platform/gpio.h"
#include "dma.h"
#include "TIM/tim1.h"

typedef struct
{
    uint16_t TIM_ARR;
    uint16_t TIM_PSC;
    DMA_Channel_TypeDef* DMA_Channel;
    ADC_ChannelTypeDef ADC_Channel;
} LDR_ConfigTypeDef;

void LDR_Init(const LDR_ConfigTypeDef* LDR_Config);
void LDR_Start(const LDR_ConfigTypeDef* LDR_Config);
void LDR_Stop(LDR_ConfigTypeDef* LDR_Config);

void LDR_Handler(LDR_ConfigTypeDef* LDR_Config);

#endif
