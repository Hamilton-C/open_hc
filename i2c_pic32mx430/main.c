/*
 * File:   main.c 
 * 
 * Author: Hamilton Canoquela
 *
 * Created on 7 de Março de 2023, 11:31
 * 
 * Este firmware é para termos os valores da temperatura e da humidade medida pelo sensor SHT4xL 
 * 
 */


#include <xc.h>
#include <sys/attribs.h>
#include "config_bits.h"
#include "var_func_I2C.h"





void main(void) {
    
    I2Cconf_master(); 
    int Ack = 0;
    int Nack = 1;
    
    uint8_t Tab_tem[3];
    uint8_t Tab_hum[3];

    
    while(1)
    {
        I2C2_start();
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        I2C2_write(device_address_wr);
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        I2C2_write(command);
        //---------------------------------------------------------------------------------------------------------------------------------------------------------        
        I2C2_stop();
        delay_ms(10);
        //---------------------------------------------------------------------------------------------------------------------------------------------------------        
        I2C2_start();
        //---------------------------------------------------------------------------------------------------------------------------------------------------------        
        I2C2_write(device_address_rd);

        Tab_tem[0] = I2C2_read(Ack);
        Tab_tem[1] = I2C2_read(Ack);
        Tab_tem[2] = I2C2_read(Ack);
        
        Tab_hum[0] = I2C2_read(Ack);
        Tab_hum[1] = I2C2_read(Ack);
        Tab_hum[2] = I2C2_read(Nack);    
    
        I2C2_stop();
        
        delay_ms(50);
    }
    
    
    return;
}
