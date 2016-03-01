#include <xc.h>
#include "keypad.h"
#include "timerP2.h"

#define INPUT 1
#define OUTPUT 0
#define ONe 1 
#define OFF 0


#define a1 PORTBbits.RB12 //j10 pin 49
#define a2 PORTEbits.RE0  //j10 pin 12
#define a3 PORTBbits.RB10 //j10 pin 47
#define a4 PORTDbits.RD11 //j10 pin 15
#define a5 PORTBbits.RB14 //j10 pin 59
#define a6 PORTDbits.RD5  //j10 pin 13
#define a7 PORTGbits.RG0  //j11 pin 6



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
    TRISGbits.TRISG0 = OUTPUT;
    TRISDbits.TRISD5 = OUTPUT;
    TRISDbits.TRISD11 = OUTPUT;
    
    ODCEbits.ODCE0 = OFF;// open drain collector for outputs
    ODCGbits.ODCG0 = OFF;
    ODCDbits.ODCD5 = OFF;
    ODCDbits.ODCD11 = OFF;
    
    CNCONBbits.ON = 1;
    CNENBbits.CNIEB10 = 1;
    CNENBbits.CNIEB12 = 1;
    CNENBbits.CNIEB14 = 1;
    
     IFS1bits.CNBIF = 0; // put down flag
    
    IPC8bits.CNIP = 7;                  // Configure interrupt priority
    IPC8bits.CNIS = 3;                  // Configure the interrupt sub-priority
    IEC1bits.CNBIE = 1;
    
    
    

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
    
    
    //IEC1bits.CNBIE = 0;
    
    ODCEbits.ODCE0 = ONe;// open drain collector for outputs
    ODCGbits.ODCG0 = OFF;
    ODCDbits.ODCD5 = OFF;
    ODCDbits.ODCD11 = OFF;
    
    delayUs(500);
    
    if(a3 == 0){
        keyPressed = '1';
    }
    
    else if(a1 == 0)    {
           keyPressed = '2'; 
    }
    else if(a5 == 0) {    
           keyPressed = '3'; 
    
    }
    ODCEbits.ODCE0 = OFF;// open drain collector for outputs
    ODCGbits.ODCG0 = ONe;
    ODCDbits.ODCD5 = OFF;
    ODCDbits.ODCD11 = OFF;
    
    delayUs(500);
    
    if(a3 == 0){
        keyPressed = '4';
    }
    else if(a1 == 0)   {  
           keyPressed = '5'; 
    }
    else if(a5 == 0)    { 
           keyPressed = '6'; 
    }
    ODCEbits.ODCE0 = OFF;// open drain collector for outputs
    ODCGbits.ODCG0 = OFF;
    ODCDbits.ODCD5 = ONe;
    ODCDbits.ODCD11 = OFF;
    
    delayUs(500);
    
    if(a3 == 0){
        keyPressed = '7';
    }
            
    else if(a1 == 0)    { 
           keyPressed = '8'; 
    }
    else if(a5 == 0)     {
           keyPressed = '9'; 
    }
    
    ODCEbits.ODCE0 = OFF;// open drain collector for outputs
    ODCGbits.ODCG0 = OFF;
    ODCDbits.ODCD5 = OFF;
    ODCDbits.ODCD11 = ONe;
    
    delayUs(500);
    
    if(a3 == 0){
        keyPressed = '*';
    }
            
    else if(a1 == 0)     {
           keyPressed = '0'; 
    }
    
    else if(a5 == 0)     {
           keyPressed = '#'; 
    }
           
    
      
   // IEC1bits.CNBIE = 1;
    //IFS1bits.CNBIF = 0;
    
    
    return keyPressed;
}
