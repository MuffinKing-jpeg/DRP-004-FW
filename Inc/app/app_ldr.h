#ifndef LDR_H
#define LDR_H

#include "app_config.h"

typedef enum
{
    APP_LDR_THRESHOLD_NOT_REACHED = 0,
    APP_LDR_THRESHOLD_REACHED = 1,
} APP_LDR_ThresholdReachedTypeDef;

void APP_LDRStart(void);
void APP_LDRStop(void);

void APP_LDR_TickHandler(void);
void APP_LDR_InterruptHandler(void);

APP_LDR_ThresholdReachedTypeDef APP_LDR_CheckThreshold(void);

#endif
