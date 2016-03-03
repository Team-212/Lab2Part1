#include <xc.h>
#include "keypad.h"
#include "timerP2.h"

#define INPUT 1
#define OUTPUT 0
#define ONe 1 
#define OFF 0


#define a1 PORTBbits.RB12 //j10 pin 49 1
#define a2 PORTEbits.RE0  //j10 pin 12 2
#define a3 PORTBbits.RB10 //j10 pin 47 3 
#define a4 PORTEbits.RE4 //j10 pin 8 4
#define a5 PORTBbits.RB14 //j10 pin 59 5
#define a6 PORTEbits.RE2  //j10 pin 10 6
#define a7 PORTEbits.RE6  //j10 pin 6  7



/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
void initKeypad(void){
    
    //columns rb10, rb12, rb14
    //rows re0, rg0, rd5, rd11
    TRISBbits.TRISB10 = INPUT;   //sets columns 
    TRISBbits.TRISB12 = INPUT;
    TRISBbits.TRISB14 = INPUT;
    
    ANSELBbits.ANSB10 = 0;// set analog pin to digital
    ANSELBbits.ANSB12 = 0;// set analog pin to digital
    ANSELBbits.ANSB14 = 0;// set analog pin to digital
     
    CNPUBbits.CNPUB10 = OFF;// pull up resistors
    CNPUBbits.CNPUB12 = OFF;
    CNPUBbits.CNPUB14 = OFF;
    
    TRISEbits.TRISE0 = OUTPUT;  //sets rows 
    TRISEbits.TRISE2 = OUTPUT;
    TRISEbits.TRISE4 = OUTPUT;
    TRISEbits.TRISE6 = OUTPUT;
    
    LATEbits.LATE0 = OFF;// open drain collector for outputs
    LATEbits.LATE2 = OFF;
    LATEbits.LATE4 = OFF;
    LATEbits.LATE6 = OFF;
    
    ODCEbits.ODCE0 = ONe;// open drain collector for outputs
    ODCEbits.ODCE2 = ONe;
    ODCEbits.ODCE4 = ONe;
    ODCEbits.ODCE6 = ONe;
    
    CNCONBbits.ON = 1;
    CNENBbits.CNIEB10 = 1;
    CNENBbits.CNIEB12 = 1;
    CNENBbits.CNIEB14 = 1;
    
     IFS1bits.CNBIF = 0; // put down flag
    
    IPC8bits.CNIP = 7;                  // Configure interrupt priority
    //IPC8bits.CNIS = 3;                  // Configure the interrupt sub-priority
    IEC1bits.CNBIE = 1;  //interrupt enable 
    
    
    

}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed. The ascii character c programmatically is just 'c'
 */
char scanKeypad(void){
    char keyPressed = -1;
   // int row = 0; 
    //int column = 0;
    
    
    CNCONBbits.ON = 0;
    
//    ODCEbits.ODCE0 = ONe;// open drain collector for outputs
//    ODCGbits.ODCG0 = OFF;
//    ODCDbits.ODCD5 = OFF;
//    ODCDbits.ODCD11 = OFF;
    
    LATEbits.LATE0 = OFF;// open drain collector for outputs
    LATEbits.LATE2 = 1;
    LATEbits.LATE4 = 1;
    LATEbits.LATE6 = 1;
    
    delayUs(50);
    
    if(a3 == 0){
        keyPressed = '1';CNCONBbits.ON = 1;
        return keyPressed;
    }
    
    else if(a1 == 0)    {
           keyPressed = '2'; CNCONBbits.ON = 1;
           return keyPressed;
    }
    else if(a5 == 0) {    
           keyPressed = '3'; CNCONBbits.ON = 1;
           return keyPressed;
    
    }
    
    LATEbits.LATE0 = 1;// open drain collector for outputs
    LATEbits.LATE2 = 0;
    LATEbits.LATE4 = 1;
    LATEbits.LATE6 = 1;
    
    delayUs(50);
    
    if(a3 == 0){
        keyPressed = '4';CNCONBbits.ON = 1;
        return keyPressed;
    }
    else if(a1 == 0)   {  
           keyPressed = '5'; 
          return keyPressed;
    }
    else if(a5 == 0)    { 
           keyPressed = '6'; CNCONBbits.ON = 1;
           return keyPressed;
    }
    
    LATEbits.LATE0 = 1;// open drain collector for outputs
    LATEbits.LATE2 = 1;
    LATEbits.LATE4 = 0;
    LATEbits.LATE6 = 1;
    
    delayUs(50);
    
    if(a3 == 0){
        keyPressed = '7';CNCONBbits.ON = 1;
       return keyPressed;
    }
            
    else if(a1 == 0)    { 
           keyPressed = '8'; CNCONBbits.ON = 1;
          return keyPressed;
    }
    else if(a5 == 0)     {
           keyPressed = '9'; CNCONBbits.ON = 1;
          return keyPressed;
    }
    
    LATEbits.LATE0 = 1;// open drain collector for outputs
    LATEbits.LATE2 = 1;
    LATEbits.LATE4 = 1;
    LATEbits.LATE6 = 0;
    
    delayUs(50);
    
    if(a3 == 0){
        keyPressed = '*';
        return keyPressed;CNCONBbits.ON = 1;
    }
            
    else if(a1 == 0)     {
           keyPressed = '0';CNCONBbits.ON = 1; 
          return keyPressed;
    }
    
    else if(a5 == 0)     {
           keyPressed = '#';CNCONBbits.ON = 1; 
           return keyPressed;
    }
           
    
    LATEbits.LATE0 = 0;// open drain collector for outputs
    LATEbits.LATE2 = 0;
    LATEbits.LATE4 = 0;
    LATEbits.LATE6 = 0;
    
      
   // IEC1bits.CNBIE = 1;
    //IFS1bits.CNBIF = 0;
    
    CNCONBbits.ON = 1;
     
    return keyPressed;
}
