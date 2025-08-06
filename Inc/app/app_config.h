#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <stdint.h>
#include "dma.h"
#include "tim1.h"

// #define USE_POWER_LATCH

typedef enum
{
    APP_CONF_LDR_ARR_INDEX,
    APP_CONF_BATT_ARR_INDEX,
} APP_ConfigADCIndex;

typedef struct
{
    uint16_t TIM_ARR;
    uint16_t TIM_PSC;
    DMA_Channel_TypeDef* DMA_Channel;
} APP_ConfigTIMTrigger_TypeDef;


static const APP_ConfigTIMTrigger_TypeDef ADC_Config = {
    .TIM_ARR = 0xFFFF,
    .TIM_PSC = 0,
    .DMA_Channel = DMA1_Channel1,
};

static const TIM1_ConfigTypeDef TIM1_Config = {
    .PSC = 0,
    .ARR = 0xFFFF,
    .CCR1 = 0,
    .CCR2 = 0,
    .CCR3 = 0,
    .CCR4 = 0,
    .CCR5 = 0,
    .CCR6 = 0,
};

#endif //APP_CONFIG_H
