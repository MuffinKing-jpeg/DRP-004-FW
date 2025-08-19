#ifndef TIM1_H
#define TIM1_H

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

typedef enum {
    TIM_MMS2_RESET                = 0x0,  // 0000: UG bit from TIMx_EGR is used as trigger output (TRGO2)
    TIM_MMS2_ENABLE               = 0x1,  // 0001: Counter Enable signal CNT_EN is used as trigger output (TRGO2)
    TIM_MMS2_UPDATE               = 0x2,  // 0010: Update event is used as trigger output (TRGO2)
    TIM_MMS2_COMPARE_PULSE        = 0x3,  // 0011: Compare pulse (CC1IF flag) is used as trigger output (TRGO2)
    TIM_MMS2_COMPARE_OC1REFC      = 0x4,  // 0100: OC1REFC signal is used as trigger output (TRGO2)
    TIM_MMS2_COMPARE_OC2REFC      = 0x5,  // 0101: OC2REFC signal is used as trigger output (TRGO2)
    TIM_MMS2_COMPARE_OC3REFC      = 0x6,  // 0110: OC3REFC signal is used as trigger output (TRGO2)
    TIM_MMS2_COMPARE_OC4REFC      = 0x7,  // 0111: OC4REFC signal is used as trigger output (TRGO2)
    TIM_MMS2_COMPARE_OC5REFC      = 0x8,  // 1000: OC5REFC signal is used as trigger output (TRGO2)
    TIM_MMS2_COMPARE_OC6REFC      = 0x9,  // 1001: OC6REFC signal is used as trigger output (TRGO2)
    TIM_MMS2_COMPARE_PULSE_OC4F_OC6F = 0xA, // 1010: OC4REFC rising or OC6REFC rising/falling edges generate pulses on TRGO2
    TIM_MMS2_COMPARE_PULSE_OC6F      = 0xB, // 1011: OC6REFC rising or falling edges generate pulses on TRGO2
    TIM_MMS2_COMPARE_PULSE_OC4F_OC6R = 0xC, // 1100: OC4REFC or OC6REFC rising edges generate pulses on TRGO2
    TIM_MMS2_COMPARE_PULSE_OC4F_OC6F2= 0xD, // 1101: OC4REFC rising or OC6REFC falling edges generate pulses on TRGO2
    TIM_MMS2_COMPARE_PULSE_OC5F_OC6R = 0xE, // 1110: OC5REFC or OC6REFC rising edges generate pulses on TRGO2
    TIM_MMS2_COMPARE_PULSE_OC5F_OC6F = 0xF  // 1111: OC5REFC rising or OC6REFC falling edges generate pulses on TRGO2
} TIM1_TRGO2_Source;

typedef enum {
    TIM1_OCMode_Timing    = 0x0,  // Frozen mode: output is inactive
    TIM1_OCMode_Active    = 0x1,  // Set output active on match
    TIM1_OCMode_Inactive  = 0x2,  // Set output inactive on match
    TIM1_OCMode_Toggle    = 0x3,  // Toggle output on match
    TIM1_OCMode_ForceLow  = 0x4,  // Force output low
    TIM1_OCMode_ForceHigh = 0x5,  // Force output high
    TIM1_OCMode_PWM1      = 0x6,  // PWM mode 1
    TIM1_OCMode_PWM2      = 0x7   // PWM mode 2
} TIM1_OC_ModeTypeDef;

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
void TIM1_SetOCMode(TIM1_CHANNEL channel, TIM1_OC_ModeTypeDef mode);


void TIM1_Init(const TIM1_ConfigTypeDef* TIM_ConfigStruct);
void TIM1_Start(void);


void TIM1_SetPrescaler(uint16_t PSCValue);
void TIM1_SetARR(uint16_t ARRValue);
void TIM1_TRGO2_Config(TIM1_TRGO2_Source TRGO2Source);

#endif
