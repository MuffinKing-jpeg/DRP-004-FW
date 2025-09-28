#include "app_ldr.h"

#include "adc.h"
#include "tim1.h"
#include "app_config.h"
#include "core.h"
#include "dma.h"

uint8_t newDataFlag = 0;
float lastData = 0;

volatile struct ADC_DMA_BufferTypeDef ADC_Data = {0};

void APP_LDR_TickHandler(void)
{
    if (newDataFlag >= 1)
    {
        lastData = lastData * CONFIG_LDR_EMA_FILTER_COEF_INV + (float)ADC_Data.data_ldr * CONFIG_LDR_EMA_FILTER_COEF;
        newDataFlag = 0;
    }
}

APP_LDR_ThresholdReachedTypeDef APP_LDR_CheckThreshold(void)
{
    if (lastData >= CONFIG_LDR_THRESHOLD)
    {
        return APP_LDR_THRESHOLD_REACHED;
    }
    return APP_LDR_THRESHOLD_NOT_REACHED;
}

void APP_LDR_InterruptHandler(void)
{
    newDataFlag = 1;
}

void APP_LDRStart(void)
{
    ADC_Start();
    DMA_EnableInterrupt(ADC_Config.DMA_Channel, DMA1_Channel1_IRQn);
    DMA_Enable(ADC_Config.DMA_Channel);
    TIM1_Start();
    ADC_Enable();
}

void APP_LDRStop(void)
{
    ADC_Reset();
    DMA_Disable(ADC_Config.DMA_Channel);
    DMA_DisableInterrupt(ADC_Config.DMA_Channel, DMA1_Channel1_IRQn);
}
