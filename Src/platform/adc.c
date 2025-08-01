#include "../../Inc/platform/adc.h"
#include "../../Inc/platform/core.h"

uint16_t ADC_Data[BOARD_ADC_CHANNEL_QTY] = {0};

void ADC_RCC_Enable(void){
    RCC->APBENR2 |= RCC_APBENR2_ADCEN;
    RCC->APBSMENR2 |= RCC_APBSMENR2_ADCSMEN;
    ADC1->CR |= ADC_CR_ADVREGEN;
    CORE_TickDelay(1000);
}

void ADC_RCC_Disable(void){
    RCC->APBENR2 &= ~RCC_APBENR2_ADCEN;
    RCC->APBSMENR2 &= ~RCC_APBSMENR2_ADCSMEN;
}

void ADC_Reset(void){
    RCC->APBRSTR2 |= RCC_APBRSTR2_ADCRST;
    CORE_TickDelay(50);
    RCC->APBRSTR2 &= ~RCC_APBRSTR2_ADCRST;
}

void ADC_SetChannel(ADC_ChannelTypeDef channel)
{
    ADC1->CHSELR |= channel;
}

void ADC_ResetChannel(ADC_ChannelTypeDef channel)
{
    ADC1->CHSELR &= ~channel;
}

void ADC_SetExternalTriggerSource(ADC_ExtTrigger source)
{
    ADC1->CFGR1 &= ~ADC_CFGR1_EXTSEL;
    ADC1->CFGR1 |= (source << ADC_CFGR1_EXTSEL_Pos);
}

void ADC_Calibration(void)
{
    ADC1->CR |= ADC_CR_ADCAL;
    while (ADC1->CR & ADC_CR_ADCAL);
}

void ADC_Enable(void)
{
    ADC1->CR |= ADC_CR_ADEN;
    while (!(ADC1->ISR & ADC_ISR_ADRDY));
}

void ADC_Start(void)
{
    ADC1->CR |= ADC_CR_ADSTART;
}

void ADC_SetExternalTriggerPolarity(ADC_ExtPolarity polarity)
{
    ADC1->CFGR1 &= ~ADC_CFGR1_EXTEN;
    ADC1->CFGR1 |= (polarity << ADC_CFGR1_EXTEN_Pos);
}

void ADC_MultiModeEnable(void)
{
    ADC1->CFGR1 |= ADC_CFGR1_SCANDIR;
    ADC1->CFGR1 |= ADC_CFGR1_CONT;
}

void ADC_EnableCircularDMA(void)
{
    ADC1->CFGR1 |= ADC_CFGR1_DMAEN;
    ADC1->CFGR1 |= ADC_CFGR1_DMACFG;
}

void ADC_EnableSingleShotDMA(void)
{
    ADC1->CFGR1 &= ~ADC_CFGR1_DMACFG;
    ADC1->CFGR1 |= ADC_CFGR1_DMAEN;
}