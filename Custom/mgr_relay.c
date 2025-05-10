#include "mgr_relay.h"
#include "mgr_uart.h"

relay_state_t relay_state=RELAY_OFF;

//relay 1: GPIOB0
//relay 2: GPIOB1
//relay 3: GPIOB3
//relay 4: GPIOB4

static bool relay_istoggletime(void)
{
    if(CUR_HOUR==23 && CUR_MINUTE==0 && CUR_SECOND==0)
    {
        return true;
    }
    else if(CUR_HOUR==4 && CUR_MINUTE==0 && CUR_SECOND==0)
    {
        return true;
    }
    else if(CUR_HOUR==5 && CUR_MINUTE==30 && CUR_SECOND==0)
    {
        return true;
    }
    else if(CUR_HOUR==7 && CUR_MINUTE==0 && CUR_SECOND==0)
    {
        return true;
    }
    //debug time check
    // else if(CUR_HOUR==20 && CUR_MINUTE==54 && CUR_SECOND==0)
    // {
    //     return true;
    // }
    else if(FORCE_TOGGLE)
    {
        FORCE_TOGGLE=0;
        return true;
    }
    return false;

    //double off at noon has been removed due to solar addition
    
}

uint32_t relay_timer=0;
void relay_1k(void)
{
    if(relay_state == RELAY_ON)
    {
        relay_timer++;
        if(relay_timer>=500)
        {
            relay_timer=0;
            relay_state=RELAY_TURN_OFF;
        }
    }
    else if(relay_state == RELAY_TURN_OFF)
    {
        relay_timer++;
        if(relay_timer>=700)
        {
            relay_timer=0;
            relay_state=RELAY_OFF;
        }
    }
    else
    {
        relay_timer=0;
    }
}

void relay_update(void)
{
    switch(relay_state)
    {
        case RELAY_OFF:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
            if(relay_istoggletime())
            {
                relay_state=RELAY_TURN_ON;
            }
            break;
        case RELAY_TURN_ON:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
            relay_state=RELAY_ON;
            break;
        case RELAY_ON:
            break;
        case RELAY_TURN_OFF:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
            // relay_state=RELAY_OFF;
            break;
    }
}