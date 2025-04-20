#include "mgr_uart.h"
#include "mgr_i2c.h"

extern UART_HandleTypeDef huart1;


uint16_t modb_db[MODB_SIZE];
uint8_t uart_rx_buffer[300];
uint8_t uart_tx_buffer[300];
uint16_t uart_rx_size;
uint16_t uart_tx_size;

uint8_t rx_cplt=0;

void uart_testwrite(void)
{
    uint8_t testmsg[5]={1,2,3,4,5};
    // HAL_UART_Transmit(&huart1,testmsg,5,100);
    HAL_UART_Transmit_IT(&huart1,testmsg,5);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    // if(Size<6) return;
    uart_rx_size=Size;
    rx_cplt=1;
    // HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,0);
}

void uart_ondatarecv(void)
{
    if(uart_rx_buffer[0]!=MODB_ADDR) return;

    //add crc check here
    uint16_t reg_addr = (uart_rx_buffer[2]<<8) | uart_rx_buffer[3];
    uint16_t payload_len = (uart_rx_buffer[4]<<8) | uart_rx_buffer[5];
    uint8_t w_payload[300];
    uint8_t r_buf[300];
    uint8_t rsp_msg[300];
    uint16_t rsp_len = 3 + payload_len*2;
    // memcpy(w_payload,uart_rx_buffer,(payload_len*2));
    rsp_msg[0]=MODB_ADDR;
    rsp_msg[1]=uart_rx_buffer[1];
    // uart_testwrite();
    //do r/w functions
    switch(uart_rx_buffer[1])
    {
        case MODB_READ:
        case MODB_READ2:
            modbus_read(&modb_db[reg_addr],r_buf,payload_len);
            // HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,0);
            rsp_msg[2]=payload_len*2;
            memcpy(&rsp_msg[3],r_buf,payload_len*2);

            break;
        case MODB_WRITE:
            memcpy(&rsp_msg[0],&uart_rx_buffer[0],6);
            modbus_write(&modb_db[reg_addr],&uart_rx_buffer[4],1);
            rsp_len=6;
            break;
        case MODB_WRITEMULT:
            // memcpy(w_payload,&uart_rx_buffer[7],uart_rx_buffer[6]);
            modbus_write(&modb_db[reg_addr],&uart_rx_buffer[7],payload_len);
            memcpy(&rsp_msg[2],&uart_rx_buffer[2],4);
            rsp_len=6;
            break;
        default:
            break;
    }
    
    uint16_t crc=0;

    crc=crc_modbus(rsp_msg,rsp_len);
    rsp_msg[rsp_len]=crc&0xff;
    rsp_msg[rsp_len+1]=crc>>8;
    HAL_UART_Transmit_DMA(&huart1,rsp_msg,rsp_len+2);

    //post-write functions
    if(SET_VALUES)
    {
        ds3231_set_from_modbus();
        SET_VALUES=0;
    }

}



void uart_mainloop(void)
{
    HAL_UARTEx_ReceiveToIdle_IT(&huart1,uart_rx_buffer,300);
    // HAL_UART_Receive_IT(&huart1,uart_rx_buffer,1);
    if(USART1->SR & 0b1111)
    {
        // HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,0);

    }

    if(rx_cplt)
    {
        uart_ondatarecv();
        rx_cplt=0;

    }
}