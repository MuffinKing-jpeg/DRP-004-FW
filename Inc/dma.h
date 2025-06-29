#ifndef __DMA_H
#define __DMA_H

#include "stm32g0xx.h"

typedef enum
{
    MEMORY_TO_MEMORY,
    MEMORY_TO_PERIPHERAL,
    PERIPHERAL_TO_MEMORY,
    PERIPHERAL_TO_PERIPHERAL,
}DMA_DirectionTypeDef;

typedef enum
{
    DMA_SIZE_8 = 0x00,
    DMA_SIZE_16 = 0x01,
    DMA_SIZE_32 = 0x02,
}DMA_DataSizeTypeDef;

typedef enum
{
    DMA_INCREMENT_MEMORY,
    DMA_INCREMENT_PERIPHERAL,
    DMA_INCREMENT_DISABLE,
}DMA_IncrementTypeDef;

void DMA_Init(DMA_Channel_TypeDef* DMA_Channel);

void DMA_SetDirection(DMA_Channel_TypeDef* DMA_Channel, DMA_DirectionTypeDef DMA_Direction);
void DMA_SetPeripheralBaseAddr(DMA_Channel_TypeDef* DMA_Channel, uint32_t Address);
void DMA_SetMemoryBaseAddr(DMA_Channel_TypeDef* DMA_Channel, uint32_t Address);
void DMA_SetArraySize(DMA_Channel_TypeDef* DMA_Channel, uint32_t Size);
void DMA_SetPeripheralSize(DMA_Channel_TypeDef* DMA_Channel, DMA_DataSizeTypeDef Size);
void DMA_SetMemorySize(DMA_Channel_TypeDef* DMA_Channel, DMA_DataSizeTypeDef Size);
void DMA_SetIncrementType(DMA_Channel_TypeDef* DMA_Channel, DMA_IncrementTypeDef Increment);

void DMA_EnableCircularMode(DMA_Channel_TypeDef* DMA_Channel);
void DMA_DisableCircularMode(DMA_Channel_TypeDef* DMA_Channel);

void DMA_Enable(DMA_Channel_TypeDef* DMA_Channel);
void DMA_Disable(DMA_Channel_TypeDef* DMA_Channel);

void DMA_EnableInterrupt(DMA_Channel_TypeDef* DMA_Channel, IRQn_Type IRQn);
void DMA_DisableInterrupt(DMA_Channel_TypeDef* DMA_Channel, IRQn_Type IRQn);

#endif
