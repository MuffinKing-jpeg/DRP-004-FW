#ifndef CORE_H
#define CORE_H

#include "stm32g0xx.h"

#define CORE_RTC_SLEEP_PERIOD (100-1)

typedef enum{
    CORE_OK,
    CORE_ERR,
    CORE_BUSY,
}CORE_HandleTypeDef;

void CORE_EnterSTOP(void);
void CORE_ExitSTOP(void);

void CORE_ClockInit(void);
void CORE_PWRInit(void);

void CORE_SetPA12Remap(void);

void CORE_TickDelay(uint16_t ticks);

#ifdef BUILD_DEBUG
void CORE_AllowDebugInSTOP(void);
#endif

#endif