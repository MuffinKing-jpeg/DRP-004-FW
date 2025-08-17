#ifndef APP_STATE_H
#define APP_STATE_H

#include <stdint.h>
#include "board.h"

typedef enum
{
    APP_STATE_IDLE = 0x00,
    APP_STATE_ARMED = 0x01,
    APP_STATE_DROPPED = 0x02,
} APP_StateTypeDef;

typedef enum
{
    VALUE_OFF = 0x00,
    VALUE_ON = 0x01,
} APP_ValueTypeDef;

void APP_State_Set(APP_StateTypeDef state);
void APP_State_TickHandler(void);

APP_StateTypeDef APP_State_Get(void);
uint32_t APP_State_GetTick(void);

#endif
