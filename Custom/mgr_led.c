#include "mgr_led.h"
#include "appl_main.h"
#include "mgr_uart.h"


uint8_t led_en=0;


//B12: MAINS
//B13: SOLAR
//B14: OVERRIDE

led_state_t led_state = LED_OFF;

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


void update_led(void)
{

    if(CUR_HOUR>=7 && CUR_HOUR<19)
    {
        led_state = LED_SOLAR;
    }
    else if(CUR_HOUR>=19 || CUR_HOUR<7)
    {
        led_state = LED_MAINS;
    }
    else
    {
        led_state = LED_OFF;
    }

    // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
    // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 1);
    // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);

    switch(led_state)
    {
        case LED_OFF:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
            break;
        case LED_MAINS: 
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
            break;
        case LED_SOLAR:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
            break;
        default:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
            break;
    }
}
