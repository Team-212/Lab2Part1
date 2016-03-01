// File:         lab2p1.c
// Date:         2-29-2016
// Authors:      Brad Nees 
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timerP2.h"
#include "config.h"
#include "interruptP1.h"
#include "keypad.h"
//#include "delay.h"


// ******************************************************************************************* //

#define ON 1
#define OFF 0

typedef enum stateTypeEnum{
    
    DeBounce, Wait, SearchKeypad, WriteLCD
    
}stateType;

volatile stateType state = Wait;
volatile char keyPressed = '\0';
volatile int row = 0;
volatile int position = 0; 


int main(void)
{
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
   initTimer2();
   initKeypad();
   
   
   
   initLCD();
    
   //TRISCbits.TRISC4 = 0;
    while(1)
    {
       // LATCbits.LATC4 = ~LATCbits.LATC4;
        //delayUs(1);
        //testLCD();
        
        switch(state){
            
            case Wait: 
                
               IEC1bits.CNBIE = ON; //enable interupt 
//                moveCursorLCD(1,1);
//                printCharLCD('d');
               
                 moveCursorLCD(1,1); //first line 
                printStringLCD("Hi Luke");  
                //scanKeypad();
                 moveCursorLCD(1,2);
                printCharLCD(scanKeypad());
                //IFS1bits.CNBIF = 1;
                break;
                
            case DeBounce: 
                 
                 
                
                delayUs(5000);
                state = SearchKeypad;
                
                break;
                
            case SearchKeypad: 
                
                IEC1bits.CNBIE = OFF;// turn off ISR 
                keyPressed = scanKeypad();
                
                state = WriteLCD; 
                break;
                
            case WriteLCD: 
                
                for(row = 1; row < 3 ; row++){
                    
                    for(position = 1; position < 9; position++){
                       
                        //moveCursorLCD(1,1); //first position, first line
                        
                        moveCursorLCD(position,row); //first position, first line
                        printCharLCD(keyPressed);
                        
                        //printStringLCD(keyPressed);
                        
                        state = Wait; 
               
                    }
                
                }
                break;
            
            
            
        }
    }
    
    return 0;
}

/*

void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt(void){
    IFS0bits.T1IF = 0;
    timerUp = 1;
}
 * 
 */

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button
    
    IFS1bits.CNBIF = 0;
    
    PORTB;
    
    
    
//    TRISBbits.TRISB10 = INPUT;
//    TRISBbits.TRISB12 = INPUT;
 //  TRISBbits.TRISB14 = INPUT;
    
    moveCursorLCD(1,1); //first line 
                printStringLCD("DeBounce");
                        
    state = DeBounce;
    
    if((PORTBbits.RB10 == 0) || (PORTBbits.RB12 == 0) || (PORTBbits.RB14 == 0)){// button pressed
      
        moveCursorLCD(1,1); //first line 
                printStringLCD("DeBounce");
        
    }
    
    
}



void __ISR(_TIMER_1_VECTOR, IPL7SRS) _TInterrupt(){
    // should control timing of stopwatch
        IFS0bits.T1IF = 0;
    
    
   // if(state == RUN_LED){
        // update time 
        // reset timer1
       // Counter++;
        //TMR1 = 0;
    //}
    
    /*else{
        
        T1CONbits.TON = 0;
        
    }*/
    
    
    
}
