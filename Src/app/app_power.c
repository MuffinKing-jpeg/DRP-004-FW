#include "app_power.h"
#include "board.h"
#include "gpio.h"

APP_ValueTypeDef isLDRPowered   = VALUE_OFF;
APP_ValueTypeDef isBatteryLoaded = VALUE_OFF;

void APP_Power_SetServoPower(const APP_ValueTypeDef value)
{
    if (value == VALUE_OFF)
    {
        GPIO_ResetPin(BOARD_Servo_EN.gpioPort, BOARD_Servo_EN.gpioPin);
    } else
    {
        GPIO_SetPin(BOARD_Servo_EN.gpioPort, BOARD_Servo_EN.gpioPin);
    }
}

void APP_Power_CheckBatteryState(uint16_t battValue)
{
}

void APP_Power_SetBatteryLoad(const APP_ValueTypeDef value)
{
    switch (value)
    {
    case VALUE_OFF:
        GPIO_ResetPin(BOARD_BAT_load.gpioPort, BOARD_BAT_load.gpioPin);
        break;
    case VALUE_ON:
        GPIO_SetPin(BOARD_BAT_load.gpioPort, BOARD_BAT_load.gpioPin);
        break;
    }
}

void APP_Power_SetLDR(const APP_ValueTypeDef value)
{
    switch (value)
    {
    case VALUE_OFF:
        GPIO_ResetPin(BOARD_LDR_EN.gpioPort, BOARD_LDR_EN.gpioPin);
        break;
    case VALUE_ON:
        GPIO_SetPin(BOARD_LDR_EN.gpioPort, BOARD_LDR_EN.gpioPin);
        break;
    }
}