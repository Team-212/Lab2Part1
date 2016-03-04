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

//#define ON 1
#define OFF 0

typedef enum stateTypeEnum{
    
    DeBounce, DeBounceRelease, Wait, Wait2, SearchKeypad, WriteLCD
    
}stateType;

volatile stateType state = Wait;
volatile char keyPressed = 'f';
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
   
   //TRISA.RA7
   TRISAbits.TRISA7 = 0;
   
   //TRISCbits.TRISC4 = 0;
    while(1)
    {
       LATAbits.LATA7 = 1;
        
        switch(state){
            
            case Wait: 
               // while(1)
              // testLCD();
//                while(1){
//                    
//                    delayUs(50);
//                            LATAbits.LATA7 = 1;
//                     delayUs(50);
//                            LATAbits.LATA7 = 0;
//                    
//                }
          //     IEC1bits.CNBIE = ON; //enable interrupt
                
//                              
               // moveCursorLCD(1,1); //first line 
               // printStringLCD("Wait State");  
                
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
                
               // moveCursorLCD(1,2); //first line 
               // printStringLCD("WAIT 2");
                
                if((PORTBbits.RB10 == 1) && (PORTBbits.RB12 == 1) && (PORTBbits.RB14 == 1) ) {
         
    
                
                state = DeBounceRelease;
                break;
    }
                
                else state = Wait2;
                break;
                
            case DeBounce: 
                 
                //moveCursorLCD(1,1); //first line 
                //printStringLCD("DeBounce State");
                
                delayUs(500);
                state = SearchKeypad;
                
                break;
                
            case DeBounceRelease: 
                 
                //moveCursorLCD(1,1); //first line 
                //printStringLCD("DeBounce State");
                
                delayUs(500);
               // moveCursorLCD(1,2); //first line 
               // printStringLCD("Button Released");
                state = WriteLCD;
                //IEC1bits.CNBIE = ON;
                break;
                
                
                
                
            case SearchKeypad: 
                
                //moveCursorLCD(1,1); //first line 
                //printStringLCD("Search Keypad");
                //delayUs(5000);
                
              //  IEC1bits.CNBIE = OFF;// turn off ISR 
                
                CNCONBbits.ON = 0; //turn change notifications off 
                
                LATEbits.LATE0 = 1;// open drain collector for outputs
                LATEbits.LATE2 = 1;
                LATEbits.LATE4 = 1;
                LATEbits.LATE6 = 1;
                
                keyPressed = scanKeypad();
                
                LATEbits.LATE0 = 0;// open drain collector for outputs
                LATEbits.LATE2 = 0;
                LATEbits.LATE4 = 0;
                LATEbits.LATE6 = 0;
                
                CNCONBbits.ON = 1; // CN on 
                
               state = Wait2;
               //state = WriteLCD;
                break;
                
            case WriteLCD: 
                
                if (counter == 9){
                    row = ~row;
                    counter = 1;
                }
                
                moveCursorLCD(counter,row);
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



void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button
    
    IFS1bits.CNBIF = 0;
    
    PORTB;
                                          
    state = DeBounce;
    
    //if((PORTBbits.RB10 == 0) || (PORTBbits.RB12 == 0) || (PORTBbits.RB14 == 0)){// button pressed
      
       //moveCursorLCD(1,2); //first line 
             //  printStringLCD("ISR Works");
    
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
