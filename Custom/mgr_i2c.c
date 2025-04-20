#include "mgr_i2c.h"
#include "mgr_uart.h"
#define DS3231_ADDRESS (0xD0)

extern I2C_HandleTypeDef hi2c1;

int bcdToDec(uint8_t val)
{
	uint8_t bin;
	bin=((val & 0xf0)>>4)*10 +(val & 0x0f);
  return (bin);
  //return (int)( (val/16*10) + (val%16) );
}


uint8_t decToBcd(int val)
{
  uint8_t y;
	y = (val/10) <<4;
	y = y | (val % 10);
	return (y);	
	//return (uint8_t)( (val/10*16) + (val%10) );
}

void ds3231_getall(uint8_t* data)
{
    uint8_t i2c_data[7];
    memset(i2c_data,0xff,7);
    memset(&modb_db[0x20],0,5);
    modb_db[0x21]=HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, i2c_data, 7, HAL_MAX_DELAY);
    // modb_db[0x21]=HAL_I2C_Mem_Read_DMA(&hi2c1, DS3231_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, i2c_data, 19);
    modb_db[0x22]=hi2c1.State;
    for (int i = 0; i < 7; i++)
    {
        data[i] = bcdToDec(i2c_data[i]);
        // modb_db[i] = i2c_data[i];
    }
}

void ds3231_setall(uint8_t* data,uint8_t len)
{

    // HAL_I2C_Mem_Write_DMA(&hi2c1, DS3231_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, data, len);
    HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, data, len,HAL_MAX_DELAY);
    // HAL_I2C_Mem_Write_DMA(&hi2c1, DS3231_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, data, 1);
    // HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}

void ds3231_set_from_modbus(void)
{
    uint8_t setdata[7];
    memset(setdata,0xff,7);
    setdata[0] = decToBcd(SET_SECOND);
    setdata[1] = decToBcd(SET_MINUTE);
    setdata[2] = decToBcd(SET_HOUR);
    setdata[3] = decToBcd(SET_DAY);
    setdata[4] = decToBcd(SET_DATE);
    setdata[5] = decToBcd(SET_MONTH);
    setdata[6] = decToBcd(SET_YEAR);
    ds3231_setall(setdata,7);
}


void testi2c(void)
{
    HAL_StatusTypeDef result;
    result = HAL_I2C_IsDeviceReady(&hi2c1, 0xD0, 2, 2);
    modb_db[0x20] = result;
    // if (result != HAL_OK) // HAL_ERROR or HAL_BUSY or HAL_TIMEOUT
    // {
    //     // printf("."); // No ACK received at that address
    // }
    // if (result == HAL_OK)
    // {
    //     // printf("0x%X", i); // Received an ACK at that address
    // }
}


void init_i2c(void)
{
                        // second, minute, hour, day, date, month, year
    uint8_t initdata[7] = {decToBcd(0),decToBcd(30),decToBcd(20),decToBcd(1),decToBcd(20),decToBcd(4),decToBcd(2025)};
    // uint8_t initdata[]= {0, (1<<4) | (5), 0b0010000+7, 0, 2<<4, 4, (20<<4 )+ 25};
    // testi2c();
    // ds3231_setall(initdata,7);

}

void update_i2c(void)
{
    uint8_t tempdata[7];
    memset(tempdata,0xff,7);
    // testi2c();
    ds3231_getall(tempdata);
    for(int i=0;i<19;i++)
    {
        modb_db[i]=tempdata[i];
    }
}