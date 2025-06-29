#include "dma.h"

void DMA_Init(DMA_Channel_TypeDef* DMA_Channel)
{
    DMA_Disable(DMA_Channel);
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;
}

void DMA_SetDirection(DMA_Channel_TypeDef* DMA_Channel, DMA_DirectionTypeDef DMA_Direction)
{
    switch (DMA_Direction)
    {
    case MEMORY_TO_MEMORY:
        DMA_Channel->CCR |= DMA_CCR_MEM2MEM;
        DMA_Channel->CCR &= ~DMA_CCR_MEM2MEM;
        break;
    case PERIPHERY_TO_MEMORY:
    case PERIPHERY_TO_PERIPHERY:
        DMA_Channel->CCR &= ~DMA_CCR_DIR;
        DMA_Channel->CCR &= ~DMA_CCR_MEM2MEM;
        break;
    case MEMORY_TO_PERIPHERY:
        DMA_Channel->CCR |= DMA_CCR_DIR;
        DMA_Channel->CCR &= ~DMA_CCR_MEM2MEM;
        break;
    }
}

void DMA_SetPeripherySize(DMA_Channel_TypeDef* DMA_Channel, DMA_DataSizeTypeDef Size)
{
    DMA_Channel->CCR |= Size << DMA_CCR_PSIZE_Pos;
}

void DMA_SetMemorySize(DMA_Channel_TypeDef* DMA_Channel, DMA_DataSizeTypeDef Size)
{
    DMA_Channel->CCR |= Size << DMA_CCR_MSIZE_Pos;
}

void DMA_SetIncrementType(DMA_Channel_TypeDef* DMA_Channel, DMA_IncrementTypeDef Increment)
{
    switch (Increment)
    {
    case DMA_INCREMENT_MEMORY:
        DMA_Channel->CCR |= DMA_CCR_MINC;
        DMA_Channel->CCR &= ~DMA_CCR_PINC;
        break;
    case DMA_INCREMENT_PERIPHERY:
        DMA_Channel->CCR &= ~DMA_CCR_MINC;
        DMA_Channel->CCR |= DMA_CCR_PINC;
        break;
    case DMA_INCREMENT_DISABLE:
        DMA_Channel->CCR &= ~DMA_CCR_PINC;
        DMA_Channel->CCR &= ~DMA_CCR_MINC;
        break;
    }
}

void DMA_SetArraySize(DMA_Channel_TypeDef* DMA_Channel, uint32_t Size)
{
    DMA_Channel->CNDTR = Size;
}

void DMA_SetPeripheryBaseAddr(DMA_Channel_TypeDef* DMA_Channel, const uint32_t* Address)
{
    DMA_Channel->CPAR = (uint32_t)Address;
}

void DMA_SetMemoryBaseAddr(DMA_Channel_TypeDef* DMA_Channel, const uint32_t* Address)
{
    DMA_Channel->CMAR = (uint32_t)Address;
}

void DMA_EnableCircularMode(DMA_Channel_TypeDef* DMA_Channel)
{
    DMA_Channel->CCR |= DMA_CCR_CIRC;
}

void DMA_DisableCircularMode(DMA_Channel_TypeDef* DMA_Channel)
{
    DMA_Channel->CCR &= ~DMA_CCR_CIRC;
}

void DMA_Enable(DMA_Channel_TypeDef* DMA_Channel)
{
    DMA_Channel->CCR |= DMA_CCR_EN;
}

void DMA_Disable(DMA_Channel_TypeDef* DMA_Channel)
{
    DMA_Channel->CCR &= ~DMA_CCR_EN;
}

void DMA_EnableInterrupt(DMA_Channel_TypeDef* DMA_Channel, IRQn_Type IRQn)
{
    DMA_Channel->CCR |= DMA_CCR_TCIE;
    NVIC_EnableIRQ(IRQn);
}

void DMA_DisableInterrupt(DMA_Channel_TypeDef* DMA_Channel, IRQn_Type IRQn)
{
    DMA_Channel->CCR &= ~DMA_CCR_TCIE;
    NVIC_DisableIRQ(IRQn);
}
