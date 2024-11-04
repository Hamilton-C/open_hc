/*
 * File:   func_I2C.c
 * Author: Hamilton Canoquela 
 * 
 * Created on 8 de Março de 2023, 17:21
 */

#include <xc.h>
#include "var_func_I2C.h"


void I2Cconf_master()
{   
    I2C2CONbits.ON = 1;    
    I2C2BRG = (CPU_CLOCK_FREQUENCY/(2*100000)) - 2;                            // Baud rate de 400kHz
                    
    I2C2CONbits.SIDL = 1;    // Stop in idle mode
    I2C2CONbits.I2CEN = 0;   // Disable I2C2 module
    I2C2CONbits.A10M = 0;    // 7-bit slave address
    I2C2CONbits.DISSLW = 1;  // Disable slew rate control
    I2C2CONbits.SMEN = 0;    // Disable SMBus input thresholds
    I2C2CONbits.GCEN = 0;    // Disable general call address
    I2C2CONbits.STRICT = 0;  // Disable strict address checking
    I2C2CONbits.STREN = 0;   // Disable SCL clock stretching
    I2C2CONbits.IPMIEN = 0;  // Disable IPMI support
    I2C2CONbits.ACKDT = 0;   // Send ACK on receive
    I2C2CONbits.ACKEN = 0;   // No ACK sequence in progress
    I2C2CONbits.RCEN = 0;    // Receive sequence not in progress
    I2C2CONbits.PEN = 0;     // Stop sequence not in progress
    I2C2CONbits.RSEN = 0;    // Repeated start sequence not in progress
    I2C2CONbits.SEN = 0;     // Start sequence not in progress
    I2C2CONbits.I2CEN = 1;   // Enable I2C2 module
    I2C2ADD = 0x50;
}

void I2C2_write(unsigned char data)
{
    I2C2TRN = data;                                // Send the address of sensor and bit for write
    while(I2C2STATbits.TRSTAT){;}
    while(I2C2STATbits.ACKSTAT){;}
}

uint8_t I2C2_read(int i)
{
    uint8_t val;

    I2C2CONbits.RCEN = 1;
    while (!I2C2STATbits.RBF){;}

    if(i == 0)
    {
        val = I2C2RCV;
        I2C2CONbits.ACKDT = 0;
        I2C2CONbits.ACKEN = 1;
        while (I2C2CONbits.ACKEN){;};
        I2C2CONbits.RCEN = 0;
    }

    if(i == 1)
    {
        val = I2C2RCV;
        I2C2CONbits.ACKDT = 1;
        I2C2CONbits.ACKEN = 1;
        while (I2C2CONbits.ACKEN){;};
        I2C2CONbits.RCEN = 0;
    }
    
    return val;
}
    

void I2C2_start(void)
{
    I2C2CONbits.SEN = 1;                                // Activate Start event (I2C1CON, bit SEN)
    while (I2C2CONbits.SEN == 1){;}     
}

void I2C2_stop(void)
{   
    I2C2CONbits.PEN = 1;                                // Activate Start event (I2C1CON, bit SEN)
    while (I2C2CONbits.PEN == 1){;}     
}


void delay_ms(unsigned int us)
{
    us *= 1000;
    // Convert microseconds us into how many clock ticks it will take
     us *= CPU_CLOCK_FREQUENCY / 1000000 / 2;  // Core Timer updates every 2 ticks
    _CP0_SET_COUNT(0); // Set Core Timer count to 0
    while (us > _CP0_GET_COUNT()); // Wait until Core Timer count reaches the number we calculated earlier
}