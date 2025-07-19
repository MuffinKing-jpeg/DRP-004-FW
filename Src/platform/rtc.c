#include "../../Inc/platform/rtc.h"

#include "board.h"
#include "gpio.h"
#define LED_DURATION 100

uint8_t LED_Counter = 0;

void RTC_Init(void)
{
    RCC->APBENR1 |= RCC_APBENR1_RTCAPBEN;
    RCC->BDCR &= ~RCC_BDCR_BDRST;
    RCC->BDCR |= RCC_BDCR_RTCEN;
    RCC->BDCR |= RCC_BDCR_RTCSEL_1;

    RTC->WPR = 0xCA;
    CORE_TickDelay(100);
    RTC->WPR = 0x53;
    CORE_TickDelay(100);

    RTC->CR &= ~RTC_CR_WUTE;
    RTC->ICSR = RTC_ICSR_INIT;

    while (!(RTC->ICSR & RTC_ICSR_WUTWF) && !(RTC->ICSR & RTC_ICSR_INITF));
    

    RTC->CR |= RTC_CR_WUTIE;
    RTC->WUTR = CORE_RTC_SLEEP_PERIOD;

    RTC->CR |= RTC_CR_WUTE;

    RTC->ICSR &= ~ (RTC_ICSR_INIT | RTC_ICSR_INITF);
    
    while ((RTC->ICSR & RTC_ICSR_INITF));

    NVIC_EnableIRQ(RTC_TAMP_IRQn);
}

void RTC_TAMP_IRQHandler(void)
{
    CORE_ExitSTOP();
    RTC->SCR = RTC_SCR_CWUTF;
    LED_Counter++;

    if (LED_Counter >= LED_DURATION)
    {
        LED_Counter = 0;
        GPIO_TogglePin(BOARD_LED.gpioPort, BOARD_LED.gpioPin);
    }
}
