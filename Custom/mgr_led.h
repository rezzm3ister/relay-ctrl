#ifndef MGR_LED_H
#define MGR_LED_H

typedef enum {
    LED_OFF = 0,
    LED_MAINS,
    LED_SOLAR
} led_state_t;  



void led_toggle_c13(void);
void update_led(void);


#endif