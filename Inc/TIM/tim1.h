#ifndef __TIM1_H
#define __TIM1_H

#include "stm32g0xx.h"

typedef struct
{
    uint16_t PSC;
    uint16_t ARR;
    uint16_t CCR1;
    uint16_t CCR2;
    uint16_t CCR3;
    uint16_t CCR4;
    uint16_t CCR5;
    uint16_t CCR6;
} TIM1_ConfigTypeDef;

typedef enum
{
    TRGO2_RESET = 0x00, // 0b0000
    OC1REFC = 0x04, // 0b0100
    OC2REFC = 0x05, // 0b0101
    OC3REFC = 0x06, // 0b0110
    OC4REFC = 0x07, // 0b0111
    OC5REFC = 0x08, // 0b1000
    OC6REFC = 0x09, // 0b1001
} TIM1_TRGO2_Source;

typedef enum
{
    TIM1_CHANNEL_1,
    TIM1_CHANNEL_2,
    TIM1_CHANNEL_3,
    TIM1_CHANNEL_4,
    TIM1_CHANNEL_5,
    TIM1_CHANNEL_6,
} TIM1_CHANNEL;

void TIM1_Enable(void);
void TIM1_EnableChannel(TIM1_CHANNEL channel);
void TIM1_DisableChannel(TIM1_CHANNEL channel);

void TIM1_Init(const TIM1_ConfigTypeDef* TIM_ConfigStruct);
void TIM1_Start(void);


void TIM1_SetPrescaler(uint16_t PSCValue);
void TIM1_SetARR(uint16_t ARRValue);
void TIM1_TRGO2_Config(TIM1_TRGO2_Source TRGO2Source);

#endif
