#include "app_state.h"

#include "board.h"
#include "gpio.h"

/* Defaults to idle on reset
 * TODO: make saving state to the flash
 */
APP_StateTypeDef currentState = APP_STATE_IDLE;
uint32_t currentTick = 0;

void setStateIdle(void)
{
    currentState = APP_STATE_IDLE;
}
void setStateArmed(void)
{
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
void APP_State_TickHandler()
{
    GPIO_StateTypeDef isBtnPressed = GPIO_GetState(BOARD_ON_Detect.gpioPort, BOARD_ON_Detect.gpioPin);
    // isBtnPressed inverted due to how button is implemented on hardware
    if (!isBtnPressed && currentState != APP_STATE_ARMED)
    {
        APP_State_Set(APP_STATE_ARMED);
    }
    else
    {
        APP_State_Set(APP_STATE_IDLE);
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