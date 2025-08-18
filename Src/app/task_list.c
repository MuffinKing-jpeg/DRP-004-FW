#include "task_list.h"

#include "app_state.h"
#include "app_config.h"

#define TASK_COUNT (uint8_t)(sizeof(taskArray) / sizeof(taskArray[0]))

static void openServo(void)
{
    SERVO_SetAngle(CONFIG_SERVO_TIM, CONFIG_SERVO_TIM_CH, CONFIG_SERVO_START_ANGLE);
}

static void closeServo(void)
{
    SERVO_SetAngle(CONFIG_SERVO_TIM, CONFIG_SERVO_TIM_CH, CONFIG_SERVO_END_ANGLE);
}

static void disableServo(void)
{
    SERVO_TIMDisable(CONFIG_SERVO_TIM);
    GPIO_SetPin(BOARD_Servo_EN.gpioPort, BOARD_Servo_EN.gpioPin);
}

struct APP_TaskListTypeDef APP_TaskList = {
    .openServo = {
        .targetTick = 0,
        .fn = &openServo
    },
    .closeServo = {
        .targetTick = 0,
        .fn = &closeServo,
    },
    .disableServo = {
        .targetTick = 0,
        .fn = &disableServo,
    }
};

struct APP_TaskTypeDef *taskArray[] = {
    &APP_TaskList.openServo,
    &APP_TaskList.closeServo,
    &APP_TaskList.disableServo
};

void APP_TASK_Execute(struct APP_TaskTypeDef task)
{
    task.targetTick = 0;
    task.fn();
}

void APP_TASK_CheckTick(uint32_t tick)
{
    for (uint8_t i = 0; i < TASK_COUNT; i++) {
        if (taskArray[i]->targetTick == tick) {
            taskArray[i]->fn();
        }
    }
}
