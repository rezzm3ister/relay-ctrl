#include "mgr_led.h"
#include "appl_main.h"
uint8_t led_en=0;

void led_toggle_c13(void)
{
    if(led_en==1)
    {
        led_en = 0;
    }
    else 
    {
        led_en = 1;
    }
    
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,led_en);
    
}