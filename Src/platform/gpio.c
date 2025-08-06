#include "../../Inc/platform/gpio.h"

volatile uint32_t* const PWR_PDCR_MAP[5] = {
    &(PWR->PDCRA),  // PORT_A - PWR->PDCRA
    &(PWR->PDCRB),  // PORT_B - PWR->PDCRB
    &(PWR->PDCRC),  // PORT_C - PWR->PDCRC
    &(PWR->PDCRD),  // PORT_D - PWR->PDCRD
    &(PWR->PDCRF)   // PORT_F - PWR->PDCRF
};

volatile uint32_t* const PWR_PUCR_MAP[5] = {
    &(PWR->PUCRA),  // PORT_A - PWR->PDCRA
    &(PWR->PUCRB),  // PORT_B - PWR->PDCRB
    &(PWR->PUCRC),  // PORT_C - PWR->PDCRC
    &(PWR->PUCRD),  // PORT_D - PWR->PDCRD
    &(PWR->PUCRF)   // PORT_F - PWR->PDCRF
};

GPIO_TypeDef* GPIO_PORT_MAP[5] = {
    GPIOA,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOF
};

void GPIO_EnablePort(GPIO_PortTypeDef port_pos)
{
    RCC->IOPENR |= (1UL << port_pos);
}

void GPIO_SelectMode(GPIO_PortTypeDef port, GPIO_PinTypeDef pin, GPIO_ModeTypeDef mode)
{
    GPIO_PORT_MAP[port]->MODER = (GPIO_PORT_MAP[port]->MODER & ~(3UL << pin*2)) | (mode << pin*2);
}

void GPIO_SelectOpMode(GPIO_PortTypeDef port, GPIO_PinTypeDef pin, GPIO_OpModeTypeDef mode)
{
    GPIO_PORT_MAP[port]->OTYPER = (GPIO_PORT_MAP[port]->OTYPER & ~(1 << pin)) | (mode << pin);
}

void GPIO_TogglePin(GPIO_PortTypeDef port, GPIO_PinTypeDef pin)
{
    GPIO_PORT_MAP[port]->ODR ^= (1UL << pin);
}

void GPIO_SetPin(GPIO_PortTypeDef port, GPIO_PinTypeDef pin)
{
    GPIO_PORT_MAP[port]->BSRR = (1UL << pin);
}

void GPIO_ResetPin(GPIO_PortTypeDef port, GPIO_PinTypeDef pin)
{
    GPIO_PORT_MAP[port]->BSRR = ((1UL << pin) << 16);
}



void GPIO_SetAF(GPIO_PortTypeDef port, GPIO_PinTypeDef pin, GPIO_AFTypeDef af)
{
    uint8_t AFR_Index = 0;

    if(pin > 7)
    {
        AFR_Index = 1;
        pin = pin - 8; 
    }

    GPIO_PORT_MAP[port]->AFR[AFR_Index] = (GPIO_PORT_MAP[port]->AFR[AFR_Index] & ~(15UL << pin*4)) | (af << pin*4);
}

void GPIO_SetPullDown(GPIO_PortTypeDef port, GPIO_PinTypeDef pin)
{
    *PWR_PDCR_MAP[port] |= (1UL << pin);
}

void GPIO_ResetPullDown(GPIO_PortTypeDef port, GPIO_PinTypeDef pin)
{
    *PWR_PDCR_MAP[port] &= ~ (1UL << pin);
}

void GPIO_SetPullUp(GPIO_PortTypeDef port, GPIO_PinTypeDef pin)
{
    *PWR_PUCR_MAP[port] |= (1UL << pin);
}

void GPIO_ResetPullUp(GPIO_PortTypeDef port, GPIO_PinTypeDef pin)
{
    *PWR_PUCR_MAP[port] &= ~ (1UL << pin);
}

void GPIO_ApplyPull(void)
{
    PWR->CR3 |= PWR_CR3_APC;
}

GPIO_StateTypeDef GPIO_GetState(GPIO_PortTypeDef port, GPIO_PinTypeDef pin)
{
    return (GPIO_StateTypeDef)(GPIO_PORT_MAP[port]->IDR & (1UL << pin))>>pin;
}
