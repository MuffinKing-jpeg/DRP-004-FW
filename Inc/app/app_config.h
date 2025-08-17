#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <stdint.h>

#include "board.h"
#include "dma.h"
#include "tim1.h"

// #define USE_POWER_LATCH

#ifdef BOARD_ADC_CHANNEL_QTY
#undef BOARD_ADC_CHANNEL_QTY
#endif
#define BOARD_ADC_CHANNEL_QTY 2

#define BOARD_ADC_BATT    ADC_CHANNEL_4
#define BOARD_ADC_LDR     ADC_CHANNEL_15

#define BOARD_ADC_CHANNEL_LIST (BOARD_ADC_BATT | BOARD_ADC_LDR)

static uint32_t ADC_Data[BOARD_ADC_CHANNEL_QTY] = {0};

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
    .PSC = 0x0080,
    .ARR = 0xFFFF,
    .CCR1 = 0,
    .CCR2 = 0,
    .CCR3 = 0,
    .CCR4 = 0,
    .CCR5 = 0,
    .CCR6 = 0,
};

#endif //APP_CONFIG_H
