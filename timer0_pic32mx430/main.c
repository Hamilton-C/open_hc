/*
 * File:   main.c
 * Author: mcuser
 *
 * Created on 25 de Agosto de 2022, 14:42
 */


#include <xc.h>
#include "configs_bits.h"

#define _XTAL_FREQ 20000000 // 20MHz crystal

void configTimers(void);

void main(void) {
    
    configTimers();
           
    TRISBbits.TRISB0 = 0;
    ANSELBbits.ANSELB0 = 0;
    
    while(1){
        LATBbits.LATB0 = 1;
        __delay_ms(50);
        LATBbits.LATB0 = 0;
        __delay_ms(250);
    }
    
    
    return;
}


void configTimers(void){
  
    T0CON0bits.T0OUTPS0=0x0001; //postcaler = 1:2
    T0CON0bits.T016BIT = 0; // Operating 8 Bit timer
    T0CON1bits.T0CS0=0x010; //clock source FOSC/4 for timer0
    T0CON1bits.T0ASYNC=0; //sync to fosc/4
    T0CON1bits.T0CKPS0=0x0001; //prescaler = 1:2
    
    // clear timer1 high and low holding registers
    TMR0H = 0;
    TMR0L = 25;
    
    T0CON0bits.T0EN =1; //enable timer0 
    
    /*
    INTCONbits.GIE = 1; // enable global interrupts  
    INTCONbits.PEIE = 1; // enable peripheral interrupts
    INTCONbits.IPEN = 1; // interupt priority
    PIE0bits.TMR0IE = 1; // enable interrupt flag for timer 1
    IPR0bits.TMR0IP = 1; // TMR0 priority high
    PIR0bits.TMR0IF = 0; // reset the overflow interrupt flag
    */
    
}