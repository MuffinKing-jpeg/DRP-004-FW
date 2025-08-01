#ifndef __GPIO_H
#define __GPIO_H

#include "stm32g0xx.h"

extern GPIO_TypeDef* GPIO_PORT_MAP[5];

extern volatile uint32_t* const PWR_PDCR_MAP[5];

extern volatile uint32_t* const PWR_PUCR_MAP[5];

typedef enum
{
    GPIO_PULL_NONE,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN,
}GPIO_PullTypeDef;

typedef enum
{
    GPIO_PORT_A,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_F,

}GPIO_PortTypeDef;

typedef enum
{
    GPIO_PIN0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,
    GPIO_PIN8,
    GPIO_PIN9,
    GPIO_PIN10,
    GPIO_PIN11,
    GPIO_PIN12,
    GPIO_PIN13,
    GPIO_PIN14,
    GPIO_PIN15,

}GPIO_PinTypeDef;

typedef enum
{
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_AF,
    GPIO_MODE_RST
}GPIO_ModeTypeDef;

typedef enum
{
    GPIO_OP_MODE_PUSHPULL,
    GPIO_OP_MODE_OPENDRAIN,
}GPIO_OpModeTypeDef;

typedef enum
{
    GPIO_AF0,
    GPIO_AF1,
    GPIO_AF2,
    GPIO_AF3,
    GPIO_AF4,
    GPIO_AF5,
    GPIO_AF6,
    GPIO_AF7,
    GPIO_AF_NONE = 0xFF,
}GPIO_AFTypeDef;

void GPIO_TogglePin(GPIO_PortTypeDef port, GPIO_PinTypeDef pin);
void GPIO_SetPin(GPIO_PortTypeDef port, GPIO_PinTypeDef pin);
void GPIO_ResetPin(GPIO_PortTypeDef port, GPIO_PinTypeDef pin);

void GPIO_EnablePort(GPIO_PortTypeDef port_pos);
void GPIO_SelectMode(GPIO_PortTypeDef port, GPIO_PinTypeDef pin, GPIO_ModeTypeDef mode);
void GPIO_SelectOpMode(GPIO_PortTypeDef port, GPIO_PinTypeDef pin, GPIO_OpModeTypeDef mode);
void GPIO_SetAF(GPIO_PortTypeDef port, GPIO_PinTypeDef pin, GPIO_AFTypeDef af);

void GPIO_SetPullDown(GPIO_PortTypeDef port, GPIO_PinTypeDef pin);
void GPIO_ResetPullDown(GPIO_PortTypeDef port, GPIO_PinTypeDef pin);

void GPIO_SetPullUp(GPIO_PortTypeDef port, GPIO_PinTypeDef pin);
void GPIO_ResetPullUp(GPIO_PortTypeDef port, GPIO_PinTypeDef pin);

void GPIO_ApplyPull();

#endif
