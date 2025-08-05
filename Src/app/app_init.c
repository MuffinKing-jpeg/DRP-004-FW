#include "app_init.h"
#include "app_config.h"

#include "board.h"
#include "dma.h"
#include "dmamux.h"
#include "rtc.h"
#include "servo.h"
#include "tim1.h"
#include "adc.h"
#include "app_ldr.h"

void APP_Init(void)
{
    BOARD_Init();
    RTC_Init();
    SERVO_TIMConfig(TIM3, TIM_CHANNEL_2);
    SERVO_SetAngle(TIM3, TIM_CHANNEL_2, 18000);
    LDR_Init();
}

void APP_InitADC(void)
{
    ADC_RCC_Enable();
    TIM1_Enable();
    ADC_Calibration();
    ADC_SetExternalTriggerPolarity(ADC_EXT_RISE);
    ADC_SetExternalTriggerSource(ADC_TRG0);
    ADC_SetChannel(BOARD_ADC_CHANNEL_LIST);
    ADC_EnableCircularDMA();
    ADC1->CFGR1 |= ADC_CFGR1_WAIT; // BRUH. just for quick prototyping. Move to driver ASAP.
    TIM1_Init(&TIM1_Config);
    TIM1_EnableChannel(TIM1_CHANNEL_5);
    TIM1_TRGO2_Config(TIM_MMS2_UPDATE);
}

void APP_initDMA(void)
{

    DMA_Init(ADC_Config.DMA_Channel);
    DMA_SetPeripherySize(ADC_Config.DMA_Channel, DMA_SIZE_16);
    DMA_SetMemorySize(ADC_Config.DMA_Channel, DMA_SIZE_16);
    DMA_SetDirection(ADC_Config.DMA_Channel,PERIPHERY_TO_MEMORY);
    DMA_SetArraySize(ADC_Config.DMA_Channel, BOARD_ADC_CHANNEL_QTY);
    DMA_SetPeripheryBaseAddr(ADC_Config.DMA_Channel, (uint32_t*)&ADC1->DR);
    DMA_SetMemoryBaseAddr(ADC_Config.DMA_Channel, ADC_Data);
    DMA_SetIncrementType(ADC_Config.DMA_Channel,DMA_INCREMENT_MEMORY);
    DMA_EnableCircularMode(ADC_Config.DMA_Channel);

    DMAMUX_Enable();
    DMAMUX_SetReqID(DMAMUX1_Channel0, DMAMUX_ADC);
}

void APP_InitGPIO(void)
{
    GPIO_SetPin(BOARD_Servo_EN.gpioPort, BOARD_Servo_EN.gpioPin);
    GPIO_SetPin(BOARD_LDR_EN.gpioPort, BOARD_LDR_EN.gpioPin);
    GPIO_SetPin(BOARD_BAT_load.gpioPort, BOARD_BAT_load.gpioPin);
}

void APP_InitSERVO(void)
{
    SERVO_TIMConfig(TIM3, TIM_CHANNEL_2);
    SERVO_SetAngle(TIM3, TIM_CHANNEL_2, 18000);
}
