/*
 * File:   main.c
 * Author: mcuser
 *
 * Created on 9 de Junho de 2023, 16:36
 */


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/attribs.h>
#include "config_bits.h"
#include "func.h"


uint16_t Temp;
uint16_t Temp1;

uint16_t Hum;


void main(void) {
    
    I2Cconf_master(); 
    configPIN();
    configEUSART();
    
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

        Temp = I2C2_read_temp();
        Hum = I2C2_read_hum();    
    
        I2C2_stop();

        while (U1STAbits.UTXBF);                                // Aguarda o buffer de transmissão estar vazio
        U1TXREG = (Temp & 0xFF00) >> 8;                           // Envia o caractere
    
        while (U1STAbits.UTXBF);                                // Aguarda o buffer de transmissão estar vazio
        U1TXREG = Temp & 0x00FF;  
        
        while (U1STAbits.UTXBF);                                // Aguarda o buffer de transmissão estar vazio
        U1TXREG = (Hum & 0xFF00) >> 8;                           // Envia o caractere
    
        while (U1STAbits.UTXBF);                                // Aguarda o buffer de transmissão estar vazio
        U1TXREG = Hum & 0x00FF;  
        
        while (U1STAbits.UTXBF);                                // Aguarda o buffer de transmissão estar vazio
        U1TXREG = 0x0A;       
        delay_ms(2500);
    }
    
    
    return;
}
