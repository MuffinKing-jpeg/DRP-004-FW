#ifndef APP_POWER_H
#define APP_POWER_H

#include "app_state.h"
// Currently this is placeholders
#define BATTERY_LOW_THRESHOLD 2000
#define BATTERY_DEAD_THRESHOLD 1500

#define BATTERY_VALUE_HYSTERESIS 100

typedef enum
{
    APP_POWER_BATTERY_OK = 0x00,
    APP_POWER_BATTERY_LOW = 0x01,
    APP_POWER_BATTERY_DEAD = 0x02,
} APP_BatteryStatusTypeDef;

void APP_Power_CheckBatteryState(uint16_t battValue);
void APP_Power_SetServoPower(APP_ValueTypeDef value);
void APP_Power_SetBatteryLoad(APP_ValueTypeDef value);
void APP_Power_SetLDR(APP_ValueTypeDef value);
#endif //APP_POWER_H
