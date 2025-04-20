#ifndef MGR_RELAY
#define MGR_RELAY


#include "appl_main.h"


typedef enum {
    RELAY_OFF=0,
    RELAY_TURN_ON,
    RELAY_ON,
    RELAY_TURN_OFF
} relay_state_t;


typedef enum
{
    RELAY_MAINS=0,
    RELAY_MAINS_TO_SOLAR,
    RELAY_SOLAR,
    RELAY_SOLAR_TO_MAINS,
    RELAY_OVERRIDE_MAINS,
    RELAY_OVERRIDE_MAINS_TO_SOLAR,
    RELAY_OVERRIDE_SOLAR,
    RELAY_OVERRIDE_SOLAR_TO_MAINS,
} relay_arr_state_t


#endif