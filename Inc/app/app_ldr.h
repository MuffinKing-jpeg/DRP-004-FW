#ifndef __LDR_H
#define __LDR_H

#include "app_config.h"


void APP_LDRInit(void);
void APP_LDRStart(void);
void APP_LDRStop(void);

void LDR_Handler(APP_ConfigTIMTrigger_TypeDef* LDR_Config);

#endif
