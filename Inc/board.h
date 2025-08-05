#ifndef BOARD_H
#define BOARD_H

#include "gpio.h"

#ifdef BOARD_ADC_CHANNEL_QTY
#undef BOARD_ADC_CHANNEL_QTY
#endif
#define BOARD_ADC_CHANNEL_QTY 2

#define BOARD_ADC_BATT    ADC_CHANNEL_4
#define BOARD_ADC_LDR     ADC_CHANNEL_15

#define BOARD_ADC_CHANNEL_LIST (BOARD_ADC_BATT | BOARD_ADC_LDR)

typedef struct
{
    GPIO_PinTypeDef gpioPin;
    GPIO_PortTypeDef gpioPort;
    GPIO_OpModeTypeDef gpioOpMode;
    GPIO_ModeTypeDef gpioMode;
    GPIO_AFTypeDef gpioAF;
    GPIO_PullTypeDef gpioPull;
} BOARD_GpioConfTypeDef;

extern const BOARD_GpioConfTypeDef BOARD_Servo_PWM;
extern const BOARD_GpioConfTypeDef BOARD_Servo_EN;
extern const BOARD_GpioConfTypeDef BOARD_LDR_ADC;
extern const BOARD_GpioConfTypeDef BOARD_LDR_EN;
extern const BOARD_GpioConfTypeDef BOARD_BAT_load;
extern const BOARD_GpioConfTypeDef BOARD_BAT_ADC;
extern const BOARD_GpioConfTypeDef BOARD_DCMode_SW;
extern const BOARD_GpioConfTypeDef BOARD_PMIC_CHRG;
extern const BOARD_GpioConfTypeDef BOARD_PMIC_PG;
extern const BOARD_GpioConfTypeDef BOARD_LED;
extern const BOARD_GpioConfTypeDef BOARD_ON_LATCH;
extern const BOARD_GpioConfTypeDef BOARD_ON_Detect;

void BOARD_Init(void);

#endif //BOARD_H
