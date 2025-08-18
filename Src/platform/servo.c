#include "../../Inc/platform/servo.h"

uint8_t SERVO_CalibrationOffset = 0;

void SERVO_TIMEnable(TIM_TypeDef* tim)
{
    switch ((uint32_t)tim)
    {
        case TIM1_BASE:
        RCC->APBENR2 |= RCC_APBENR2_TIM1EN;
        break;
        case TIM2_BASE:
        RCC->APBENR1 |= RCC_APBENR1_TIM2EN;
        break;
        case TIM3_BASE:
        RCC->APBENR1 |= RCC_APBENR1_TIM3EN;
        break;
        case TIM14_BASE:
        RCC->APBENR2 |= RCC_APBENR2_TIM14EN;
        break;
        case TIM16_BASE:
        RCC->APBENR2 |= RCC_APBENR2_TIM16EN;
        break;
        case TIM17_BASE:
        RCC->APBENR2 |= RCC_APBENR2_TIM17EN;
        break;
        default:
        __NOP();
        break;
    }
}

void SERVO_TIMDisable(TIM_TypeDef* tim)
{
    switch ((uint32_t)tim)
    {
    case TIM1_BASE:
        RCC->APBENR2 &= ~RCC_APBENR2_TIM1EN;
        break;
    case TIM2_BASE:
        RCC->APBENR1 &= ~RCC_APBENR1_TIM2EN;
        break;
    case TIM3_BASE:
        RCC->APBENR1 &= ~RCC_APBENR1_TIM3EN;
        break;
    case TIM14_BASE:
        RCC->APBENR2 &= ~RCC_APBENR2_TIM14EN;
        break;
    case TIM16_BASE:
        RCC->APBENR2 &= ~RCC_APBENR2_TIM16EN;
        break;
    case TIM17_BASE:
        RCC->APBENR2 &= ~RCC_APBENR2_TIM17EN;
        break;
    default:
        __NOP();
        break;
    }
}


void SERVO_TIMConfig(TIM_TypeDef *tim, const TIM_ChannelTypeDef channel)
{
    tim->PSC = 0;
    tim->ARR = 40000 - 1;

    for (uint8_t i = 0; i < 4; i++)
    {
        if (channel & 1 << i)
        {
            if (i < 2)
            {
                tim->CCMR1 &= ~(7UL << (4 + 8 * i));
                tim->CCMR1 |= 6UL << (4 + 8 * i);
                tim->CCMR1 |= 1UL << (8 + 8 * i);
            }
            else
            {
                tim->CCMR2 &= ~(7UL << (4 + 8 * (i-2)));
                tim->CCMR2 |= 6UL << (4 + 8 * (i-2));
                tim->CCMR2 |= 1UL << (8 + 8 * (i-2));
            }
            tim->CCER |= 1UL << 4*i;

            tim->BDTR |= TIM_BDTR_MOE;
            tim->CR1 |= TIM_CR1_CEN;
        }

    }
}

void SERVO_SetAngle(TIM_TypeDef *tim, const TIM_ChannelTypeDef channel, const uint16_t angle)
{
    const uint16_t mapped_angle = 2500 + angle * 2500 / 18000 - SERVO_CalibrationOffset; // Some mapping shenanigans. Numbers picked by experiment.
    volatile uint32_t* channels[] = {&tim->CCR1,&tim->CCR2,&tim->CCR3,&tim->CCR4};

    for (uint8_t i = 0; i < 4; i++)
    {
        if (channel & 1 << i)
        {
            *channels[i] = mapped_angle;
        }

    }

}
