#include "task_list.h"

#include "app_state.h"
#include "app_config.h"

#include "board.h"

#define TASK_COUNT (uint8_t)(sizeof(taskArray) / sizeof(taskArray[0]))

static void disableServo(void)
{
    SERVO_TIMDisable(CONFIG_SERVO_TIM);
    GPIO_SetPin(BOARD_Servo_EN.gpioPort, BOARD_Servo_EN.gpioPin);
}

struct APP_TaskTypeDef TASK_DisableServo = {
    .targetTick = 0,
    .fn = &disableServo,
};

struct APP_TaskTypeDef *taskArray[] = {
    &TASK_DisableServo
};

void APP_TASK_Execute(struct APP_TaskTypeDef* task)
{
    task->targetTick = 0;
    task->fn();
}

void APP_TASK_CheckTick(const uint32_t tick)
{
    for (uint8_t i = 0; i < TASK_COUNT; i++) {
        if (taskArray[i]->targetTick <= tick && taskArray[i]->targetTick != 0) {
            APP_TASK_Execute(taskArray[i]);
        }
    }
}
void APP_TASK_Defer(struct APP_TaskTypeDef* task, const uint32_t delayTicks)
{
    task->targetTick = delayTicks + APP_State_GetTick();
}
