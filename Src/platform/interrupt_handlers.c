#include "app_ldr.h"
#include "app_state.h"
#include "core.h"
#include "rtc.h"

void RTC_TAMP_IRQHandler(void)
{
    CORE_ExitSTOP();
    RTC_ClearWUTF();
    APP_State_RTCHandler();
}

void DMA1_Channel1_IRQHandler(void)
{
    CORE_ExitSTOP();
    APP_LDR_InterruptHandler();
    DMA_ClearInterruptFlags();
}
