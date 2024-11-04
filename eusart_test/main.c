/*
 * File:   main.c
 * Author: Hamilton Canoquela
 *
 * Created on 24 de Agosto de 2022, 11:03
 */

#include <xc.h>
#include <stdio.h>
#include "configs_bit.h"


#define _XTAL_FREQ 1000000 // 1MHz crystal


unsigned char serial_data;

void configPIN();
void configEUSART();
void configOSCI();


void main(void) {
   
    configPIN();
    configOSCI();
    configEUSART();
    
    
    while(1){

        while(PIR3bits.RC1IF == 0);                            
        serial_data = RC1REG;          // Armazenar os dados a serem recebidos
        
        __delay_ms(1000);
        
        TX1REG = serial_data + 1;                   // Armazenar os dados a serem transmitidos 
        while(PIR3bits.TX1IF == 0);     // PIR3---> Registro de Solicita��o de Interrup��o Perif�rica 3
                                        // TXxIF: Este � o bit sinalizador de interrup��o do transmissor. Ele se torna alto quando o registrador TXxREG est� vazio. 
                                        // RCxIF: Este � o bit sinalizador de interrup��o do receptor. Torna-se alto quando o registrador RCREG est� cheio.
        
        __delay_ms(1000);

        
        // PIE1 ---> Registro de Habilita��o de Interrup��o Perif�rica 3    
        // PIE3bits.TX2IE == 1;  TXxIE: Este bit � definido como alto para habilitar a interrup��o da transmiss�o.
        // PIE3bits.RC2IE == 1;  RCxIE: Este bit � definido como alto para habilitar a interrup��o de recep��o. 
    }
 
    return;
}



void configEUSART(){
           
    // Para termos a Taxa de transmis�o desejada:
    BAUD1CONbits.BRG16 = 1;                                 // Habilita/desabilita registrador de taxa de transmiss�o de 16 bits. BRG16 = 1 --> 16bits habilitados e a taxa � definida pelos registros SPxBRGL e SPxBRGH
    TX1STAbits.BRGH = 1;                                    // Velocidade da comunica��o serial, depende do bit SYNC     
    TX1STAbits.SYNC = 0;                                    // Modo de comunica��o - Ass�ncrono = 0; S�ncrono = 1;
    
    //SP1BRG = 25;                                          // O valor depende dos bits SYNC, BRGH e BRG16 
    SP1BRGH = 0;
    SP1BRGL = 0x19;                                         // Baud Rate = 9600
       
    // Habilitando a transmiss�o: 
    RC1STAbits.SPEN = 1;                    // Habilita a porta Serial
    TX1STAbits.TXEN = 1;                    // Habilita a transmiss�o 
    RC2STAbits.CREN = 1;                    // Habilita a recep��o
    
    }

void configOSCI()
{ 
     //Fosc = 1MHz
    OSCCON1bits.NOSC = 0x110;           // Fonte do clock --- HFINTOSC
    OSCCON1bits.NDIV = 0x0010;          // Divisor do clock = 4MHz
    OSCCON3 = 0x00;                     // CSWHOLD may proceed; SOSCPWR Low power;
    OSCEN = 0X00;                       // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled;   
    OSCFRQbits.HFFRQ = 0x010;           // HFFRQ = 4MHZ
    OSCTUNE = 0x00;                     // TUN 0;
    //  
}

void configPIN()
{
    // Pino para sa�da da transmiss�o TX (RC4), placa BTC:
    TRISCbits.TRISC6 = 0;                                   // Definir a porta RC6 como sa�da 
    ANSELCbits.ANSELC6 = 1;                                 // Definir a porta RC6 como Digital
    RC6PPS = 0x09;                                          // Definir a porta RC6 para sa�da TX
    
    // Pino para entrada da transmiss�o RX (RC7), placa BTC: 
    TRISCbits.TRISC7 = 1;
    ANSELCbits.ANSELC7 = 0;
    RX1PPS = 0x17;  
    
    //H_Beat BTC:
    TRISBbits.TRISB4 = 0;
    ANSELBbits.ANSELB4 = 0;


}