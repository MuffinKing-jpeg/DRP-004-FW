#include "board.h"
#include "core.h"

const BOARD_GpioConfTypeDef BOARD_Servo_PWM = {
    .gpioPin = GPIO_PIN5,
    .gpioPort = GPIO_PORT_B,
    .gpioOpMode = GPIO_OP_MODE_PUSHPULL,
    .gpioMode = GPIO_MODE_AF,
    .gpioAF = GPIO_AF1,
    .gpioPull = GPIO_PULL_NONE,
};

const BOARD_GpioConfTypeDef BOARD_Servo_EN = {
    .gpioPin = GPIO_PIN8,
    .gpioPort = GPIO_PORT_B,
    .gpioOpMode = GPIO_OP_MODE_PUSHPULL,
    .gpioMode = GPIO_MODE_OUTPUT,
    .gpioAF = GPIO_AF_NONE,
    .gpioPull = GPIO_PULL_DOWN,
};

const BOARD_GpioConfTypeDef BOARD_LDR_ADC = {
    .gpioPin = GPIO_PIN11,
    .gpioPort = GPIO_PORT_A,
    .gpioOpMode = GPIO_OP_MODE_PUSHPULL,
    .gpioMode = GPIO_MODE_RST,
    .gpioAF = GPIO_AF_NONE,
    .gpioPull = GPIO_PULL_NONE,
};

const BOARD_GpioConfTypeDef BOARD_LDR_EN = {
    .gpioPin = GPIO_PIN12,
    .gpioPort = GPIO_PORT_A,
    .gpioOpMode = GPIO_OP_MODE_PUSHPULL,
    .gpioMode = GPIO_MODE_OUTPUT,
    .gpioAF = GPIO_AF_NONE,
    .gpioPull = GPIO_PULL_DOWN,
};

const BOARD_GpioConfTypeDef BOARD_BAT_load = {
    .gpioPin = GPIO_PIN5,
    .gpioPort = GPIO_PORT_A,
    .gpioOpMode = GPIO_OP_MODE_PUSHPULL,
    .gpioMode = GPIO_MODE_OUTPUT,
    .gpioAF = GPIO_AF_NONE,
    .gpioPull = GPIO_PULL_NONE,
};

const BOARD_GpioConfTypeDef BOARD_BAT_ADC = {
    .gpioPin = GPIO_PIN4,
    .gpioPort = GPIO_PORT_A,
    .gpioOpMode = GPIO_OP_MODE_PUSHPULL,
    .gpioMode = GPIO_MODE_RST,
    .gpioAF = GPIO_AF_NONE,
    .gpioPull = GPIO_PULL_NONE,
};

const BOARD_GpioConfTypeDef BOARD_DCMode_SW = {
    .gpioPin = GPIO_PIN0,
    .gpioPort = GPIO_PORT_A,
    .gpioOpMode = GPIO_OP_MODE_PUSHPULL,
    .gpioMode = GPIO_MODE_OUTPUT,
    .gpioAF = GPIO_AF_NONE,
    .gpioPull = GPIO_PULL_NONE,
};

const BOARD_GpioConfTypeDef BOARD_PMIC_CHRG = {
    .gpioPin = GPIO_PIN0,
    .gpioPort = GPIO_PORT_B,
    .gpioOpMode = GPIO_OP_MODE_PUSHPULL,
    .gpioMode = GPIO_MODE_INPUT,
    .gpioAF = GPIO_AF_NONE,
    .gpioPull = GPIO_PULL_NONE,
};

const BOARD_GpioConfTypeDef BOARD_PMIC_PG = {
    .gpioPin = GPIO_PIN1,
    .gpioPort = GPIO_PORT_B,
    .gpioOpMode = GPIO_OP_MODE_PUSHPULL,
    .gpioMode = GPIO_MODE_INPUT,
    .gpioAF = GPIO_AF_NONE,
    .gpioPull = GPIO_PULL_NONE,
};

const BOARD_GpioConfTypeDef BOARD_LED = {
    .gpioPin = GPIO_PIN7,
    .gpioPort = GPIO_PORT_A,
    .gpioOpMode = GPIO_OP_MODE_OPENDRAIN,
    .gpioMode = GPIO_MODE_OUTPUT,
    .gpioAF = GPIO_AF_NONE,
    .gpioPull = GPIO_PULL_NONE,
};

const BOARD_GpioConfTypeDef BOARD_ON_LATCH = {
    .gpioPin = GPIO_PIN1,
    .gpioPort = GPIO_PORT_A,
    .gpioOpMode = GPIO_OP_MODE_PUSHPULL,
    .gpioMode = GPIO_MODE_OUTPUT,
    .gpioAF = GPIO_AF_NONE,
    .gpioPull = GPIO_PULL_NONE,
};

const BOARD_GpioConfTypeDef BOARD_ON_Detect = {
    .gpioPin = GPIO_PIN2,
    .gpioPort = GPIO_PORT_A,
    .gpioOpMode = GPIO_OP_MODE_PUSHPULL,
    .gpioMode = GPIO_MODE_INPUT,
    .gpioAF = GPIO_AF_NONE,
    .gpioPull = GPIO_PULL_DOWN
};

BOARD_GpioConfTypeDef BOARD_PinConfig[] = {
    BOARD_Servo_PWM,
    BOARD_Servo_EN,
    BOARD_LDR_ADC,
    BOARD_LDR_EN,
    BOARD_BAT_load,
    BOARD_BAT_ADC,
    BOARD_DCMode_SW,
    BOARD_PMIC_CHRG,
    BOARD_PMIC_PG,
    BOARD_LED,
    BOARD_ON_LATCH,
    BOARD_ON_Detect
};

void BOARD_Init(void)
{
    CORE_ClockInit();
    CORE_PWRInit();
    GPIO_EnablePort(GPIO_PORT_B);
    GPIO_EnablePort(GPIO_PORT_A);

    uint8_t len = sizeof(BOARD_PinConfig) / sizeof(BOARD_GpioConfTypeDef);

    for (int i = 0; i < len; ++i)
    {
        if (BOARD_PinConfig[i].gpioMode != GPIO_MODE_RST)
        {
            GPIO_SelectMode(
                BOARD_PinConfig[i].gpioPort,
                BOARD_PinConfig[i].gpioPin,
                BOARD_PinConfig[i].gpioMode);
            GPIO_SelectOpMode(
                BOARD_PinConfig[i].gpioPort,
                BOARD_PinConfig[i].gpioPin,
                BOARD_PinConfig[i].gpioOpMode);

            if (BOARD_PinConfig[i].gpioAF != GPIO_AF_NONE)
            {
                GPIO_SetAF(
                    BOARD_PinConfig[i].gpioPort,
                    BOARD_PinConfig[i].gpioPin,
                    BOARD_PinConfig[i].gpioAF);
            }

            switch (BOARD_PinConfig[i].gpioPull)
            {
            case GPIO_PULL_UP:
                GPIO_SetPullUp(BOARD_PinConfig[i].gpioPort, BOARD_PinConfig[i].gpioPin);
                break;
            case GPIO_PULL_DOWN:
                GPIO_SetPullDown(BOARD_PinConfig[i].gpioPort, BOARD_PinConfig[i].gpioPin);
                break;
            default:
                __NOP();
            }
        }
    }

    GPIO_ApplyPull();
}
