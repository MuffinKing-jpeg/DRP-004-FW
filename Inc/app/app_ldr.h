#ifndef __LDR_H
#define __LDR_H

#include "app_config.h"


void LDR_Init(void);
void LDR_Start(void);
void LDR_Stop(void);

void LDR_Handler(APP_ConfigTIMTrigger_TypeDef* LDR_Config);

#endif
