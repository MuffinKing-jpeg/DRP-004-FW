#include "core.h"
#include "rtc.h"
#include "app_state.h"

void RTC_TAMP_IRQHandler(void)
{
    CORE_ExitSTOP();
    RTC_ClearWUTF();
    APP_State_TickHandler();
}

void DMA1_Channel1_IRQHandler(void)
{
    __NOP();
}
