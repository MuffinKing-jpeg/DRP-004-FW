#ifndef APP_STATE_H
#define APP_STATE_H

typedef enum
{
    APP_STATE_IDLE = 0x00,
    APP_STATE_ARMED = 0x01,
    APP_STATE_DROPED = 0x02,
} APP_StateTypeDef;

void APP_State_Set(APP_StateTypeDef state);
APP_StateTypeDef APP_State_Get(void);

#endif
