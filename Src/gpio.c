#include "gpio.h"

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

void GPIO_EnablePort(GPIO_TypePortDef port_pos)
{
    RCC->IOPENR |= (1UL << port_pos);
}

void GPIO_SelectMode(GPIO_TypeDef *port, GPIO_TypePinDef pin, GPIO_TypeModeDef mode)
{
    port->MODER = (port->MODER & ~(3UL << pin*2)) | (mode << pin*2);
}

void GPIO_SelectOpMode(GPIO_TypeDef *port, GPIO_TypePinDef pin, GPIO_TypeOpModeDef mode)
{
    port->OTYPER = (port->OTYPER & ~(1 << pin)) | (mode << pin);
}

void GPIO_TogglePin(GPIO_TypeDef *port, GPIO_TypePinDef pin)
{
    port->ODR ^= (1UL << pin);
}

void GPIO_SetPin(GPIO_TypeDef *port, GPIO_TypePinDef pin)
{
    port->BSRR = (1UL << pin);
}

void GPIO_ResetPin(GPIO_TypeDef *port, GPIO_TypePinDef pin)
{
    port->BSRR = ((1UL << pin) << 16);
}



void GPIO_SetAF(GPIO_TypeDef *port, GPIO_TypePinDef pin, GPIO_TypeAFDef af)
{
    uint8_t AFR_Index = 0;

    if(pin > 7)
    {
        AFR_Index = 1;
        pin = pin - 8; 
    }

    port->AFR[AFR_Index] = (port->AFR[AFR_Index] & ~(15UL << pin*4)) | (af << pin*4);
}

void GPIO_SetPullDown(GPIO_TypePortDef port, GPIO_TypePinDef pin)
{
    *PWR_PDCR_MAP[port] |= (1UL << pin);
}

void GPIO_ReSetPullDown(GPIO_TypePortDef port, GPIO_TypePinDef pin)
{
    *PWR_PDCR_MAP[port] &= ~ (1UL << pin);
}

void GPIO_SetPullUp(GPIO_TypePortDef port, GPIO_TypePinDef pin)
{
    *PWR_PUCR_MAP[port] |= (1UL << pin);
}

void GPIO_ReSetPullUp(GPIO_TypePortDef port, GPIO_TypePinDef pin)
{
    *PWR_PUCR_MAP[port] &= ~ (1UL << pin);
}

void GPIO_ConfigALL(void)
{
    GPIO_EnablePort(GPIO_PORT_B);
    GPIO_EnablePort(GPIO_PORT_A);

    // Config CTRL_LED (PA7) pin
    GPIO_SelectMode(GPIOA, GPIO_PIN7, GPIO_MODE_OUTPUT);
    GPIO_SelectOpMode(GPIOA, GPIO_PIN7, GPIO_OP_MODE_OPENDRAIN);

    // Config SERVO (PB5) pin
    GPIO_SelectOpMode(GPIOB, GPIO_PIN5, GPIO_OP_MODE_PUSHPULL);
    GPIO_SelectMode(GPIOB, GPIO_PIN5, GPIO_MODE_AF);
    GPIO_SetAF(GPIOB, GPIO_PIN5, GPIO_AF1);
    // GPIO_SetPullDown(GPIO_PORT_B,GPIO_PIN5);

    // Config SERVO power control
    // GPIO_SetPullDown(GPIO_PORT_B,GPIO_PIN8);
    GPIO_SelectMode(GPIOB, GPIO_PIN8, GPIO_MODE_OUTPUT);
    GPIO_SelectOpMode(GPIOB, GPIO_PIN8, GPIO_OP_MODE_PUSHPULL);

    // Config LDR_EN (PA12) pin
    GPIO_SelectOpMode(GPIOA, GPIO_PIN12, GPIO_OP_MODE_PUSHPULL);
    GPIO_SelectMode(GPIOA, GPIO_PIN12, GPIO_MODE_OUTPUT);
    GPIO_SetPullDown(GPIO_PORT_A,GPIO_PIN12);

    PWR->CR3 |= PWR_CR3_APC;
}
