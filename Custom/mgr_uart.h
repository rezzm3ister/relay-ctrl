#ifndef MGR_UART
#define MGR_UART
#include "appl_main.h"
#include "lib_modbus.h"

#define MODB_SIZE 0x100
extern uint16_t modb_db[MODB_SIZE];

#define MODB_ADDR           0x69

#define CUR_SECOND          modb_db[0x00]
#define CUR_MINUTE          modb_db[0x01]
#define CUR_HOUR            modb_db[0x02]
#define CUR_DAY             modb_db[0x03] //day of week
#define CUR_DATE            modb_db[0x04]
#define CUR_MONTH           modb_db[0x05]
#define CUR_YEAR            modb_db[0x06]

#define SET_SECOND          modb_db[0x10]
#define SET_MINUTE          modb_db[0x11]
#define SET_HOUR            modb_db[0x12]
#define SET_DAY             modb_db[0x13] //day of week
#define SET_DATE            modb_db[0x14]
#define SET_MONTH           modb_db[0x15]
#define SET_YEAR            modb_db[0x16]
#define SET_VALUES          modb_db[0x1F]

#define FORCE_TOGGLE        modb_db[0x30]

void uart_mainloop(void);
#endif