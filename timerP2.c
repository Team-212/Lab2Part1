/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timerP2.h"

void delayUs(unsigned int delay){

    //TODO: Create a delay for "delay" micro seconds using timer 
    
    /*
    
    TMR2 = 0;
    T2CONbits.TCKPS = 0;
    PR2 = (delay*10) - 1;
    //timerUp = 0;
    T2CONbits.ON = 1;
    while(IFS0bits.T2IF == 0);
    T2CONbits.ON = 0;
    IFS0bits.T2IF = 0;
    
    */
    
    
     
    TMR2 = 0; // clear TMR2
    PR2 = delay*8;//(delay*975)-1; // PR2 so that delay equals 1us * delay //it was 8
    IFS0bits.T2IF = 0; // Lower interrupt flag
    T2CONbits.TON = 1; // Turns on timer
    while(IFS0bits.T2IF == 0); //Delays until TMR2 hits PR
    T2CONbits.TON = 0; // Turns off timer
     
     
    
    
}

void initTimer2(){
    
    
    /*
    TMR2 = 0;
    T2CONbits.TCKPS = 0;
    T2CONbits.TCS = 0;
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;
    IPC2bits.T2IP = 7;
    */
    
    
     
    TMR2 = 0;// clear TMR2
    T2CONbits.TCKPS = 1; // Initialize pre-scalar to 1
    T2CONbits.TCS = 0; // Use internal peripheral clock
    IPC1bits.T1IP = 7;
    IPC1bits.T1IS = 3;
     
     
    
    
}

#define PRESCALAR_256 3 // third possible number

void initTimer1(){
    
    TMR1 = 0;
    T1CONbits.TCKPS = PRESCALAR_256; //set prescaler
    PR1 = 39; //Do calculation // turn on timer // assuming 10MHz oscillator
    T1CONbits.ON = 1; 
    IEC0bits.T1IE = 1; // enables interrupt
    IPC1bits.T1IP = 7; // timer 1 priority
    IFS0bits.T1IF = 0; // put down interrupt flag
    //T1CONbits.ON = 1; // turn on AFTER
    
    //TODO: Initialize Timer 1 to have a period of
    // 1 second. Enable its interrupt
}