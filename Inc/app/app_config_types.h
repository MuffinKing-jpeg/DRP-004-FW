#ifndef APP_CONFIG_TYPES_H
#define APP_CONFIG_TYPES_H
#include "stm32g0xx.h"
#include "tim1.h"

struct ADC_DMA_BufferTypeDef
{
    uint32_t data_batt;
    uint32_t data_ldr;
};

extern volatile struct ADC_DMA_BufferTypeDef ADC_Data;

typedef enum
{
    APP_CONF_LDR_ARR_INDEX,
    APP_CONF_BATT_ARR_INDEX,
} APP_ConfigADCIndex;

typedef struct
{
    DMA_Channel_TypeDef* DMA_Channel;
} APP_ConfigTIMTrigger_TypeDef;


extern const APP_ConfigTIMTrigger_TypeDef ADC_Config;

extern const TIM1_ConfigTypeDef TIM1_Config;

#endif //APP_CONFIG_TYPES_H