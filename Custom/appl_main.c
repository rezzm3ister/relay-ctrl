#include "appl_main.h"
#include "mgr_led.h"
#include "mgr_i2c.h"
#include "mgr_uart.h"


extern TIM_HandleTypeDef htim2;


uint32_t t1=0;
uint8_t one_sec_flag=0;
uint32_t uptime_timer=0;

void custom_init(void)
{
    // HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_Base_Start_IT(&htim2);
    init_i2c();

}

//does things every 1ms
void ms_loop(void) //1khz
{
    if(t1<1000)
    {
        t1++;
    }
    else
    {
        t1=0;
        one_sec_flag=1;
    }

}

//does things every 1s
void sec_loop(void) //operates every second
{
    led_toggle_c13();
    update_i2c();
}

//does things whenever it can
void main_loop(void)
{
    if(one_sec_flag)
    {
        sec_loop();

        one_sec_flag = 0;
        uptime_timer++;
    }
    uart_mainloop();
    update_led();
}

