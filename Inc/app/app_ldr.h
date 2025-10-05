#ifndef LDR_H
#define LDR_H

#include "app_config.h"

void APP_LDRStart(void);
void APP_LDRStop(void);

void APP_LDR_TickHandler(void);
void APP_LDR_InterruptHandler(void);

void APP_LDR_CheckThreshold(void);

#endif
