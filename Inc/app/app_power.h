#ifndef APP_POWER_H
#define APP_POWER_H

#include "board.h"
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

typedef enum
{
    APP_POWER_CONVERTER_MODE_PWM = 0x00,
    APP_POWER_CONVERTER_MODE_PFM = 0x01,
} APP_PowerConverterModeTypeDef;

void APP_Power_SetConverterMode(APP_PowerConverterModeTypeDef mode);
void APP_Power_CheckBatteryState(uint16_t battValue);

#endif //APP_POWER_H
