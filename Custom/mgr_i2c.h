#ifndef MGR_I2C
#define MGR_I2C
#include "appl_main.h"

void ds3231_set_from_modbus(void);

void init_i2c(void);

void update_i2c(void);


#endif