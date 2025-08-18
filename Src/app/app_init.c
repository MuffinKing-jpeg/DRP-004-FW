#include "app_init.h"
#include "app_config.h"
#include "app_state.h"
#include "task_list.h"

#include "board.h"
#include "dma.h"
#include "dmamux.h"
#include "rtc.h"
#include "servo.h"
#include "tim1.h"
#include "adc.h"

void APP_Init(void)
{
    BOARD_Init();
    RTC_Init();
    APP_InitSERVO();

    // Handling of saved state. For future use
    switch (APP_State_Get())
    {
        case APP_STATE_IDLE:
        case APP_STATE_DROPPED:
        SERVO_SetAngle(CONFIG_SERVO_TIM, CONFIG_SERVO_TIM_CH, CONFIG_SERVO_START_ANGLE);
        APP_State_Set(APP_STATE_IDLE);
        APP_TaskList.disableServo.targetTick = APP_State_GetTick() + CONFIG_SERVO_OPEN_DELAY;
        break;
        default:
        SERVO_SetAngle(CONFIG_SERVO_TIM, CONFIG_SERVO_TIM_CH, CONFIG_SERVO_END_ANGLE);
        GPIO_ResetPin(BOARD_Servo_EN.gpioPort, BOARD_Servo_EN.gpioPin);
        break;
    }
}

void APP_InitADCByTrigger(void)
{
    ADC_RCC_Enable();
    TIM1_Enable();
    ADC_Calibration();
    ADC_SetExternalTriggerPolarity(ADC_EXT_RISE);
    ADC_SetExternalTriggerSource(ADC_TRG0);
    ADC_SetChannel(CONFIG_BOARD_ADC_CHANNEL_LIST);
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
    DMA_SetArraySize(ADC_Config.DMA_Channel, CONFIG_BOARD_ADC_CHANNEL_QTY);
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
    SERVO_TIMEnable(CONFIG_SERVO_TIM);
    SERVO_TIMConfig(CONFIG_SERVO_TIM, CONFIG_SERVO_TIM_CH);
}
