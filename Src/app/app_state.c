#include "app_state.h"
#include "app_init.h"
#include "app_ldr.h"
#include "app_power.h"
#include "board.h"
#include "gpio.h"

struct TickDiff
{
    APP_ValueTypeDef current;
    APP_ValueTypeDef last;
};

/* Defaults to idle on reset
 * TODO: make saving state to the flash
 */
APP_StateTypeDef currentState = APP_STATE_IDLE;
uint32_t currentTick = 0;


struct TickDiff isBtnPressed = {VALUE_OFF,VALUE_OFF};

void setStateIdle(void)
{
    APP_Power_SetConverterMode(APP_POWER_CONVERTER_MODE_PWM);
    APP_LDRStop();
    GPIO_ResetPin(BOARD_LED.gpioPort, BOARD_LED.gpioPin);
    currentState = APP_STATE_IDLE;
}

void setStateArmed(void)
{
    APP_Power_SetConverterMode(APP_POWER_CONVERTER_MODE_PFM);
    APP_Power_SetBatteryLoad(VALUE_ON);
    APP_Power_SetLDR(VALUE_ON);
    APP_InitADCByTrigger();
    APP_InitADCTransferDMA();
    APP_LDRStart();
    GPIO_SetPin(BOARD_LED.gpioPort, BOARD_LED.gpioPin);
    currentState = APP_STATE_ARMED;
}

void setStateDropped(void)
{
    currentState = APP_STATE_DROPPED;
}

void APP_State_Set(const APP_StateTypeDef state)
{
    switch (state)
    {
    case APP_STATE_IDLE:
        setStateIdle();
        break;
    case APP_STATE_ARMED:
        setStateArmed();
        break;
    case APP_STATE_DROPPED:
        setStateDropped();
        break;
    }
}

void APP_State_TickHandler(void)
{
    isBtnPressed.last = isBtnPressed.current;
    isBtnPressed.current = (APP_ValueTypeDef)GPIO_GetState(BOARD_ON_Detect.gpioPort, BOARD_ON_Detect.gpioPin);

    // isBtnPressed inverted due to how button is implemented on hardware
    if (!isBtnPressed.current && isBtnPressed.last)
    {
        switch (currentState)
        {
        case APP_STATE_IDLE:
        case APP_STATE_DROPPED:
            setStateArmed();
            break;
        case APP_STATE_ARMED:
            setStateIdle();
        }
    }
    currentTick++;
}

APP_StateTypeDef APP_State_Get(void)
{
    return currentState;
}

uint32_t APP_State_GetTick(void)
{
    return currentTick;
}
