#include "app_ldr.h"

#include "adc.h"
#include "tim1.h"
#include "app_config.h"
#include "dma.h"

void APP_LDRInit(void)
{
    __NOP();
}
void APP_LDRStart(void)
{
    // BRUH, again platform code
#ifdef BUILD_DEBUG
    DBG->APBFZ2 |= DBG_APB_FZ2_DBG_TIM1_STOP;
#endif
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
