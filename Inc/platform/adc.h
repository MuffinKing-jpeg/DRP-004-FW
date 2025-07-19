#ifndef __ADC_H
#define __ADC_H

#include "stm32g0xx.h"

#ifndef ADC_CHANNEL_QTY
#define ADC_CHANNEL_QTY 1
#endif

typedef enum
{
    ADC_CHANNEL_0 = 0x000001,
    ADC_CHANNEL_1 = 0x000002,
    ADC_CHANNEL_2 = 0x000004,
    ADC_CHANNEL_3 = 0x000008,
    ADC_CHANNEL_4 = 0x000010,
    ADC_CHANNEL_5 = 0x000020,
    ADC_CHANNEL_6 = 0x000040,
    ADC_CHANNEL_7 = 0x000080,
    ADC_CHANNEL_8 = 0x000100,
    ADC_CHANNEL_9 = 0x000200,
    ADC_CHANNEL_10 = 0x000400,
    ADC_CHANNEL_11 = 0x000800,
    ADC_CHANNEL_TEMP = 0x001000,
    ADC_CHANNEL_VREFI = 0x002000,
    ADC_CHANNEL_VBAT = 0x004000,
    ADC_CHANNEL_15 = 0x008000,
    ADC_CHANNEL_16 = 0x010000,
    ADC_CHANNEL_17 = 0x020000,
    ADC_CHANNEL_18 = 0x040000,
} ADC_ChannelTypeDef;

typedef enum
{
    ADC_TRG0,
    ADC_TRG1,
    ADC_TRG2,
    ADC_TRG3,
    ADC_TRG4,
    ADC_TRG5,
    ADC_TRG6,
    ADC_TRG7,
} ADC_ExtTrigger;

typedef enum
{
    ADC_EXT_DISABLE,
    ADC_EXT_RISE,
    ADC_EXT_FALL,
    ADC_EXT_RISE_FALL,
} ADC_ExtPolarity;


extern uint16_t ADC_Data[ADC_CHANNEL_QTY];

void ADC_RCC_Enable(void);
void ADC_RCC_Disable(void);
void ADC_Reset(void);
void ADC_SetChannel(ADC_ChannelTypeDef channel);
void ADC_ResetChannel(ADC_ChannelTypeDef channel);
void ADC_SetExternalTriggerSource(ADC_ExtTrigger source);
void ADC_SetExternalTriggerPolarity(ADC_ExtPolarity polarity);
void ADC_Calibration(void);
void ADC_Start(void);
void ADC_Enable(void);

void ADC_MultiModeEnable(void);
void ADC_EnableCircularDMA(void);
void ADC_EnableSingleShotDMA(void);

#endif
