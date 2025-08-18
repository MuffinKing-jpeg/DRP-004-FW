#ifndef TASK_LIST_H
#define TASK_LIST_H
#include "servo.h"


struct APP_TaskTypeDef
{
    uint32_t targetTick;
    void (* const fn)(void);
};

struct APP_TaskListTypeDef
{
    struct APP_TaskTypeDef openServo;
    struct APP_TaskTypeDef closeServo;
    struct APP_TaskTypeDef disableServo;
};

extern struct APP_TaskListTypeDef APP_TaskList;

void APP_TASK_Execute(struct APP_TaskTypeDef task);
void APP_TASK_CheckTick(uint32_t tick);

#endif //TASK_LIST_H