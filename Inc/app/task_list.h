#ifndef TASK_LIST_H
#define TASK_LIST_H
#include "servo.h"


struct APP_TaskTypeDef
{
    uint32_t targetTick;
    void (* const fn)(void);
};

extern struct APP_TaskTypeDef TASK_DisableServo;

void APP_TASK_Execute(struct APP_TaskTypeDef* task);
void APP_TASK_CheckTick(uint32_t tick);
void APP_TASK_Defer(struct APP_TaskTypeDef* task, uint32_t delayTicks);

#endif //TASK_LIST_H