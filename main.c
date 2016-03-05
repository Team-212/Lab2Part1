/*
  
 / ******************************************************************************************* //
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
    
    
    
///}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

// ******************************************************************************************* //
//
// File:         lab2p2.c
// Date:         3-4-2016
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
#include "string.h"
//#include "delay.h"


// ******************************************************************************************* //

//#define ON 1
#define OFF 0

typedef enum stateTypeEnum{
    
    DeBounce, DeBounceRelease, Wait, Wait2, SearchKeypad, WriteLCD, CheckPassword, CheckNewPassword, EnterPassword, Set
    
}stateType;

volatile stateType state = Wait;






int main(void)
{
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
   initTimer2();
   initKeypad();
   initLCD();
   
    char password1[5] = {'a','a','a','a','\0'}; //2D array of passwords 
 char password2[5] = {'a','a','a','a','\0'};
 char password3[5] = {'a','a','a','a','\0'};
 char password4[5] = {'a','a','a','a','\0'};
 char tempPassword[5] = {'\0','\0','\0','\0','\0'}; //password being entered

 char keyPressed = 'f';
 int row = 1;
 int position = 0; 
 int counter = 1;
 int numPasswords = 0; //number of passwords 
 int i =0; 
 int j =0;
 int set = 0; 
 
   //TRISA.RA7
   TRISAbits.TRISA7 = 0;
   
   //TRISCbits.TRISC4 = 0;
    while(1)
    {
       
        
        switch(state){
            
            case Wait: 
                            
                if( set == 1){
//                moveCursorLCD(1,1); //first line 
//                printStringLCD("Set Mode");
                }              
                else {
                    
                moveCursorLCD(1,1); //first line 
                printStringLCD("Enter"); 
                }
                
               
                break;
                
            case Wait2:
                
                
                if((PORTBbits.RB10 == 1) && (PORTBbits.RB12 == 1) && (PORTBbits.RB14 == 1) ) { //waits for button release
         
                   
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
                state = EnterPassword;
                //IEC1bits.CNBIE = ON;
                break;
                
            case Set:
                moveCursorLCD(1,1); //first line 
                printStringLCD("Set Mode");
                
                moveCursorLCD(1,2); // clears second line 
                    clearLCD;
                set = 1; 
                state = Wait; 
                
                break; 
                
            case EnterPassword:
                
                                                
                if(i == 4){
                    i = 0;
                                        
                }
               tempPassword[i] =  keyPressed;
               i = i + 1;
               
               if( i == 2){
                        
                        //if((passwords[0][numPasswords] == '*') && (passwords[1][numPasswords] == '*')) {
                         if((tempPassword[0] == '*') && (tempPassword[1] == '*')) {   
                            i = 0;
                            state = Set;
                        } 
                    }
               
               state = WriteLCD;
                break;
                
              case CheckNewPassword:
                        
                for(j = 0; j < 4; j++){ //checks all stored passwords 
                    
                    if ((tempPassword[j] == '*') || (tempPassword[j] == '#')){
                        moveCursorLCD(1,1); //first line 
                        printStringLCD("Invalid"); //print valid
                        delayUs(2000000);
                        moveCursorLCD(1,2); // clears second line 
                        clearLCD;
                        set = 0;
                        state = Wait;
                 
                        }
                }
                
                
                    moveCursorLCD(1,1); //first line 
                    printStringLCD("Valid"); //print invalid
                    delayUs(2000000);
                    moveCursorLCD(1,2); // clears second line 
                    clearLCD;
                    
                    numPasswords = numPasswords +1;
                    
                      if(numPasswords == 4){
                        numPasswords = 0;
                    }
                    
                    if(numPasswords == 0){
                        
                        for(j =0; j < 5; j++){
                            password1[j] = tempPassword[j];
                        }
                    }
                    
                    else if(numPasswords == 1){
                        
                        for(j =0; j < 5; j++){
                            password2[j] = tempPassword[j];
                        }
                    }
                    
                    else if(numPasswords == 2){
                        
                        for(j =0; j < 5; j++){
                            password3[j] = tempPassword[j];
                        }
                    }
                    
                    else if(numPasswords = 3){
                        
                        for(j =0; j < 5; j++){
                            password4[j] = tempPassword[j];
                        }
                    }
                    set = 0;
                    
                    state = Wait;
                
                    
                        
                        
                break;
                
            case CheckPassword:
                        
                                  
                    if (strcmp(password1, tempPassword) == 0){
                        moveCursorLCD(1,1); //first line 
                        printStringLCD("Good"); //print valid
                        delayUs(20000);
                        moveCursorLCD(1,2); // clears second line 
                        clearLCD;
                 
                        state = Wait;
                 
                        }
                     if (strcmp(password2, tempPassword) == 0){
                        moveCursorLCD(1,1); //first line 
                        printStringLCD("Good"); //print valid
                        delayUs(20000);
                        moveCursorLCD(1,2); // clears second line 
                        clearLCD;
                 
                        state = Wait;
                 
                        }
                    
                     if (strcmp(password3, tempPassword) == 0){
                        moveCursorLCD(1,1); //first line 
                        printStringLCD("Good"); //print valid
                        delayUs(20000);
                        moveCursorLCD(1,2); // clears second line 
                        clearLCD;
                 
                        state = Wait;
                 
                        }
                    
                     if (strcmp(password4, tempPassword) == 0){
                        moveCursorLCD(1,1); //first line 
                        printStringLCD("Good"); //print valid
                        delayUs(20000);
                        moveCursorLCD(1,2); // clears second line 
                        clearLCD;
                 
                        state = Wait;
                 
                        }
                
                
                
                    moveCursorLCD(1,1); //first line 
                    printStringLCD("Bad"); //print invalid
                    delayUs(20000);
                    moveCursorLCD(1,2); // clears second line 
                    clearLCD;
                    
                    
                    state = Wait;
                
                    
                        
                        
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
//                    row = ~row;
                    counter = 1;
                }
                
                moveCursorLCD(counter,2);
                  delayUs(2000);
                printCharLCD(keyPressed);
                delayUs(200);
                counter = counter + 1;
                  
                if(i == 3){
                    
                    if(set == 1){
                        state = CheckNewPassword;
                    }
                    state = CheckPassword;
                }
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
