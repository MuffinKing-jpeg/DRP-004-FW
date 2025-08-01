#include "ldr.h"
#include "board.h"

TIM1_ConfigTypeDef TIM1_Config = {
    .PSC = 0,
    .ARR = 0xFFFF,
    .CCR1 = 0,
    .CCR2 = 0,
    .CCR3 = 0,
    .CCR4 = 0,
    .CCR5 = 0,
    .CCR6 = 0,
};



void LDR_Init(const LDR_ConfigTypeDef* LDR_Config)
{
    ADC_RCC_Enable();
    TIM1_Enable();
    DMA_Init(LDR_Config->DMA_Channel);
    ADC_Calibration();
    ADC_SetExternalTriggerPolarity(ADC_EXT_RISE);
    ADC_SetExternalTriggerSource(ADC_TRG0);
    ADC_SetChannel(BOARD_ADC_CHANNEL_LIST);
    ADC_EnableCircularDMA();
    ADC1->CFGR1 |= ADC_CFGR1_WAIT; // BRUH. just for quick prototyping. Move to driver ASAP.
    TIM1_Init(&TIM1_Config);
    TIM1_EnableChannel(TIM1_CHANNEL_5);
    TIM1_TRGO2_Config(TIM_MMS2_UPDATE);
    DMA_SetPeripherySize(LDR_Config->DMA_Channel, DMA_SIZE_16);
    DMA_SetMemorySize(LDR_Config->DMA_Channel, DMA_SIZE_16);
    DMA_SetDirection(LDR_Config->DMA_Channel,PERIPHERY_TO_MEMORY);
    DMA_SetArraySize(LDR_Config->DMA_Channel, BOARD_ADC_CHANNEL_QTY);
    DMA_SetPeripheryBaseAddr(LDR_Config->DMA_Channel, (uint32_t*)&ADC1->DR);
    DMA_SetMemoryBaseAddr(LDR_Config->DMA_Channel, ADC_Data);
    DMA_SetIncrementType(LDR_Config->DMA_Channel,DMA_INCREMENT_MEMORY);
    DMA_EnableCircularMode(LDR_Config->DMA_Channel);
    DMAMUX_Enable();
    DMAMUX_SetReqID(DMAMUX1_Channel0, DMAMUX_ADC);

    // CORE_SetPA12Remap();

    // Config LDR_EN (PA12) pin
    // GPIO_SelectOpMode(GPIOA, GPIO_PIN12, GPIO_OP_MODE_PUSHPULL);
    // GPIO_SelectMode(GPIOA, GPIO_PIN10, GPIO_AF2);
    // // GPIO_SetPullDown(GPIO_PORT_A,GPIO_PIN10);
    // GPIO_SetPullUp(GPIO_PORT_A,GPIO_PIN10);
    //
    // TIM1_SetOCMode(TIM1_CHANNEL_3, TIM1_OCMode_PWM1);
    // TIM1_EnableChannel(TIM1_CHANNEL_3);
    // TIM1->BDTR |= TIM_BDTR_MOE;

    /* So, actually PA12 mapping not working as intended...
     * It is just remaps GPIO functionality, but not alternative function.
     * FUUUUUUUUUUUUUUCK, NEW HW REVISION NEEDED!
     */

}
void LDR_Start(const LDR_ConfigTypeDef* LDR_Config)
{
#ifdef BUILD_DEBUG
    DBG->APBFZ2 |= DBG_APB_FZ2_DBG_TIM1_STOP;
#endif
    ADC_Start();
    DMA_EnableInterrupt(LDR_Config->DMA_Channel, DMA1_Channel1_IRQn);
    DMA_Enable(LDR_Config->DMA_Channel);
    TIM1_Start();
    ADC_Enable();
}

void LDR_Stop(LDR_ConfigTypeDef* LDR_Config)
{
    // TODO: HOW TO STOP LDR? LOL
}

void LDR_Handler(LDR_ConfigTypeDef* LDR_Config)
{
    // TODO: ADC trigger first!
}
