#include "app_init.h"
#include "app_config.h"
#include "app_state.h"

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
    APP_LDRInit();
}

void APP_InitADCByTrigger(void)
{
    ADC_RCC_Enable();
    TIM1_Enable();
    ADC_Calibration();
    ADC_SetExternalTriggerPolarity(ADC_EXT_RISE);
    ADC_SetExternalTriggerSource(ADC_TRG0);
    ADC_SetChannel(BOARD_ADC_CHANNEL_LIST);
    ADC_EnableCircularDMA();
    ADC_EnableWaitMode();
    TIM1_Init(&TIM1_Config);
    TIM1_EnableChannel(TIM1_CHANNEL_5);
    TIM1_TRGO2_Config(TIM_MMS2_UPDATE);
}

void APP_InitADCTransferDMA(void)
{

    DMA_Init(ADC_Config.DMA_Channel);
    DMA_SetPeripherySize(ADC_Config.DMA_Channel, DMA_SIZE_32);
    DMA_SetMemorySize(ADC_Config.DMA_Channel, DMA_SIZE_32);
    DMA_SetDirection(ADC_Config.DMA_Channel,PERIPHERY_TO_MEMORY);
    DMA_SetArraySize(ADC_Config.DMA_Channel, BOARD_ADC_CHANNEL_QTY);
    DMA_SetPeripheryBaseAddr(ADC_Config.DMA_Channel, (uint32_t*)&ADC1->DR);
    DMA_SetMemoryBaseAddr(ADC_Config.DMA_Channel, (uint32_t*)&ADC_Data);
    DMA_SetIncrementType(ADC_Config.DMA_Channel,DMA_INCREMENT_MEMORY);
    DMA_EnableCircularMode(ADC_Config.DMA_Channel);

    DMAMUX_Enable();
    DMAMUX_SetReqID(DMAMUX1_Channel0, DMAMUX_ADC);
}

void APP_InitDefaultGPIO(void)
{
#ifdef USE_POWER_LATCH
    GPIO_SetPin(BOARD_ON_LATCH.gpioPort, BOARD_ON_LATCH.gpioPin);
#endif
}

void APP_InitSERVO(void)
{
    SERVO_TIMConfig(TIM3, TIM_CHANNEL_2);
    SERVO_SetAngle(TIM3, TIM_CHANNEL_2, 18000);
}
