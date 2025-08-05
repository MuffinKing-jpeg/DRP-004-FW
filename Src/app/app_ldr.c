#include "app_ldr.h"
#include "board.h"
#include "tim1.h"
#include "app_config.h"
#include "dma.h"

void LDR_Init(void)
{

}
void LDR_Start(const APP_ConfigADC_TypeDef* ADC_Config)
{
#ifdef BUILD_DEBUG
    DBG->APBFZ2 |= DBG_APB_FZ2_DBG_TIM1_STOP;
#endif
    ADC_Start();
    DMA_EnableInterrupt(ADC_Config->DMA_Channel, DMA1_Channel1_IRQn);
    DMA_Enable(ADC_Config->DMA_Channel);
    TIM1_Start();
    ADC_Enable();
}

void LDR_Stop(APP_ConfigADC_TypeDef* LDR_Config)
{
    // TODO: HOW TO STOP LDR? LOL
}
