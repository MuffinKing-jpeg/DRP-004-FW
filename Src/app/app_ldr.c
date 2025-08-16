#include "app_ldr.h"

#include "adc.h"
#include "board.h"
#include "tim1.h"
#include "app_config.h"
#include "dma.h"

void APP_LDRInit(void)
{

}
void APP_LDRStart()
{
    // BRUH, again platform code
#ifdef BUILD_DEBUG
    DBG->APBFZ2 |= DBG_APB_FZ2_DBG_TIM1_STOP;
#endif
    ADC_Start();
    ADC_Enable();
    DMA_EnableInterrupt(ADC_Config.DMA_Channel, DMA1_Channel1_IRQn);
    TIM1_Start();
    DMA_Enable(ADC_Config.DMA_Channel);
}

void APP_LDRStop(void)
{
    // TODO: HOW TO STOP LDR? LOL
}
