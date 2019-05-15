#include "beep.h"

// 蜂鸣器发出闹钟声
void beep_blink(uint8_t Switch)
{
    static uint8_t n=0;
    if(Switch == 0)
    {
        HAL_GPIO_WritePin(BEE_GPIO_Port,BEE_Pin,GPIO_PIN_RESET);
        return;
    }
    switch (n)
    {
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        n++;
        break;
    case 9:
        n=0;
        HAL_GPIO_WritePin(BEE_GPIO_Port,BEE_Pin,GPIO_PIN_RESET);
        break;
    
    default:
        HAL_GPIO_TogglePin(BEE_GPIO_Port,BEE_Pin);
        n++;
        break;
    }
}

