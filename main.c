// ******************************************************************************************* //
//
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
    
    DeBounce, DeBounceRelease, Wait, Wait2, SearchKeypad, WriteLCD
    
}stateType;

volatile stateType state = Wait;
volatile char keyPressed = '\0';
volatile int row = 1;
volatile int position = 0; 
volatile int counter = 1;


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
       
        
        switch(state){
            
            case Wait: 
             //   while(1)
              //  testLCD();
                
          //     IEC1bits.CNBIE = ON; //enable interrupt
                
//                moveCursorLCD(1,1);
//                printCharLCD('d');
              
                //moveCursorLCD(1,1); //first line 
                //printStringLCD("Wait State");  
                //scanKeypad();
                // moveCursorLCD(1,2);
                // printStringLCD("Wait2 State");
                //printCharLCD(scanKeypad());
                //IFS1bits.CNBIF = 1;
                break;
                
            case Wait2:
                //IEC1bits.CNBIE = ON;
//               if((PORTBbits.RB10 == 1) && (PORTBbits.RB12 == 1) && (PORTBbits.RB14 == 1)){// button released
//      
//                    //delayUs(500);
//                    state = DeBounceRelease;
//                    IEC1bits.CNBIE = ON;
//                }
                if((PORTBbits.RB10 == 1) && (PORTBbits.RB12 == 1) && (PORTBbits.RB14 == 1) ) {
         state = DeBounceRelease;
    
                //moveCursorLCD(1,2); //first line 
                //printStringLCD("WAIT 2");
    }
                
                else state = Wait2;
                break;
                
            case DeBounce: 
                 
                //moveCursorLCD(1,1); //first line 
                //printStringLCD("DeBounce State");
                
                delayUs(50);
                state = SearchKeypad;
                
                break;
                
            case DeBounceRelease: 
                 
                //moveCursorLCD(1,1); //first line 
                //printStringLCD("DeBounce State");
                
                delayUs(50);
                state = WriteLCD;
                //IEC1bits.CNBIE = ON;
                break;
                
                
                
                
            case SearchKeypad: 
                
                //moveCursorLCD(1,1); //first line 
                //printStringLCD("Search Keypad");
                //delayUs(5000);
                
              //  IEC1bits.CNBIE = OFF;// turn off ISR 
                keyPressed = scanKeypad();
                //
               state = Wait2; 
                break;
                
            case WriteLCD: 
                //counter = counter + 1;
                if (counter == 9){
////                    if (row == 1)
//                        row = 2;
//                    else if (row == 2)
//                        row = 1;
//                    moveCursorLCD(1,row);
                    counter = 1;
                }
                moveCursorLCD(counter,1);
                printCharLCD(keyPressed);
                //IEC1bits.CNBIE = ON;
                 //keyPressed = '\0';
                counter = counter + 1;
                                           
                        state = Wait; 
                
               //IEC1bits.CNBIE = ON;
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
                                          
   
    
    //if((PORTBbits.RB10 == 0) || (PORTBbits.RB12 == 0) || (PORTBbits.RB14 == 0)){// button pressed
      
       //moveCursorLCD(1,2); //first line 
             //  printStringLCD("ISR Works");
     state = DeBounce;
    //}
    
//    if((state == Wait2) && ((PORTBbits.RB10 == 1) && (PORTBbits.RB12 == 1) && (PORTBbits.RB14 == 1)) ) {
//         state = DeBounceRelease;
//    
//                //moveCursorLCD(1,2); //first line 
//                //printStringLCD("WAIT 2");
//    }
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
