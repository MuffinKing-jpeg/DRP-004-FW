#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <stdint.h>

#include "dma.h"
#include "tim1.h"

// #define USE_POWER_LATCH

// Servo config

#define CONFIG_SERVO_TIM                TIM3
#define CONFIG_SERVO_TIM_CH             TIM_CHANNEL_2

#define CONFIG_SERVO_TIM_PSC            1
#define CONFIG_SERVO_TIM_ARR            (20000-1)

#define CONFIG_SERVO_MIN_BASE           500
#define CONFIG_SERVO_MAX_BASE           2500

#define CONFIG_SERVO_MIN_ANGLE          0
#define CONFIG_SERVO_MAX_ANGLE          180

#define CONFIG_SERVO_MAP_SLOPE         ((CONFIG_SERVO_MAX_BASE-CONFIG_SERVO_MIN_BASE)/(CONFIG_SERVO_MAX_ANGLE- CONFIG_SERVO_MIN_ANGLE))
// #define CONFIG_SERVO_MAP_SLOPE          2
#define CONFIG_SERVO_MOVE_DELAY         (uint32_t)400U

#define CONFIG_SERVO_START_ANGLE        0
#define CONFIG_SERVO_END_ANGLE          180

// ADC config

#define CONFIG_BOARD_ADC_CHANNEL_QTY    sizeof(ADC_Data)/sizeof(uint32_t)
#define CONFIG_BOARD_ADC_BATT           ADC_CHANNEL_4
#define CONFIG_BOARD_ADC_LDR            ADC_CHANNEL_16

#define CONFIG_BOARD_ADC_CHANNEL_LIST   (CONFIG_BOARD_ADC_BATT | CONFIG_BOARD_ADC_LDR)

// TIM1 (ADC trigger) config

#define CONFIG_TIM1_ARR                 2048
#define CONFIG_TIM1_PSC                 0
#define CONFIG_TIM1_CCR1                0
#define CONFIG_TIM1_CCR2                0
#define CONFIG_TIM1_CCR3                0
#define CONFIG_TIM1_CCR4                0
#define CONFIG_TIM1_CCR5                0
#define CONFIG_TIM1_CCR6                0

// LDR Config
// Probably I should store threshold inside flash for calibration purposes
#define CONFIG_LDR_THRESHOLD            1750.0f
/* EMA (exponential moving average)
 * S = S * CONFIG_LDR_EMA_FILTER_COEF_INV + data * CONFIG_LDR_EMA_FILTER_COEF
 */
#define CONFIG_LDR_EMA_FILTER_COEF      0.9f
#define CONFIG_LDR_EMA_FILTER_COEF_INV  (1.0f - CONFIG_LDR_EMA_FILTER_COEF)



#endif //APP_CONFIG_H
