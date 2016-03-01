/*
 * File:   lcd.c
 * Authors:
 *
 * Created on December 31, 2014, 1:39 PM
 */

/* TODO: Make define statements for each pin used in the LCD
 */
#include <xc.h>
#include "lcd.h"
#include "timerP2.h"
#include <string.h>

/* The pins that you will use for the lcd control will be
 * LCD_RS      RC4
 * LCD_E       RC2
 * LCD_D4      RE7
 * LCD_D5      RE5
 * LCD_D6      RE3
 * LCD_D7      RE1
 * Use these so that we will be able to test your code for grading and to
 * help you debug your implementation!
 */

#define LCD_DATA LATE;// is this right??
#define LCD_RS LATCbits.LATC4 
#define LCD_E LATCbits.LATC2
//#define LCD_E2 LATBbits.LATB10
//#define LCD_RS2 LATBbits.LATB12

#define TRIS_D7 TRISEbits.TRISE1
#define TRIS_D6 TRISEbits.TRISE3
#define TRIS_D5 TRISEbits.TRISE5
#define TRIS_D4 TRISEbits.TRISE7
#define TRIS_RS TRISCbits.TRISC4
#define TRIS_E TRISCbits.TRISC2 
//#define TRIS_E2 TRISBbits.TRISB10
//#define TRIS_RS2 TRISBbits.TRISB12


#define LAT_D7 LATEbits.LATE1
#define LAT_D6 LATEbits.LATE3
#define LAT_D5 LATEbits.LATE5
#define LAT_D4 LATEbits.LATE7


#define OUTPUT 0
#define INPUT 1
#define ON 1
#define OFF 0




/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATE. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower){
    //TODO:
    
    // set the commandType (RS value)
    if(lower == 1){
    LAT_D4 = word&0x01;// assigns bit value to output for each
    LAT_D5 = (word&0x02)>>1;
    LAT_D6 = (word&0x04)>>2;
    LAT_D7 = (word&0x08)>>3;
    }
    
    else{ 
    LAT_D4 = (word&0x10)>>4;// assigns bit value to output for each (higher bits)
    LAT_D5 = (word&0x20)>>5;
    LAT_D6 = (word&0x40)>>6;
    LAT_D7 = (word&0x80)>>7;  
    }
    
    
    LCD_RS = commandType;
    
   
    //enable
    LCD_E = 1;// enable
    //delay
    delayUs(1);// 1 for now
    //disable
    LCD_E = 0;// disable
    
    delayUs(delayAfter);
    
}

/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){
    //TODO:
    
    writeFourBits(word, commandType, delayAfter, 0);// higher bits
    
    writeFourBits(word, commandType, delayAfter, 1);// lower bits
            
}

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c) {
    //TODO:
    
    writeLCD(c, 1, 50);
    
}
/*Initialize the LCD
 */
void initLCD(void) {
    // Setup D, RS, and E to be outputs (0).
    
    
    //set as output 
    TRIS_D7 = OUTPUT;// D7
    TRIS_D6 = OUTPUT;// D6
    TRIS_D5 = OUTPUT;// D5
    TRIS_D4 = OUTPUT;// D4
    TRIS_RS = OUTPUT;// RS
    TRIS_E = OUTPUT;// E
    
    ANSELEbits.ANSE5 = 0;// set analog pin to digital
    ANSELEbits.ANSE7 = 0;// set analog pin to digital
    
    //ANSELBbits.ANSB10 = 0;// set analog pin to digital
    //ANSELBbits.ANSB12 = 0;
 
    //set initial values to 0
    LAT_D7 = OFF;
    LAT_D6 = OFF;
    LAT_D5 = OFF;
    LAT_D4 = OFF;
    
    //LCD_E = OFF;
    //LCD_RS = OFF;
  
    
    // Initilization sequence utilizes specific LCD commands before the general configuration
    // commands can be utilized. The first few initilition commands cannot be done using the
    // WriteLCD function. Additionally, the specific sequence and timing is very important.
    
    //******
    
    // wait 15 ms or more after VDD = 4.5V
    delayUs(20000);
    
    //Rs = 0; R/W = 0; DB7 = 0; DB6 = 0; DB5 = 1; DB4 = 1;
   
    writeFourBits(0x03, 0, 4100, 1);
    writeFourBits(0x03, 0, 100, 1);
    writeFourBits(0x03, 0, 100, 1);
    writeFourBits(0x02, 0, 100, 1);
    
    writeFourBits(0x02, 0, 40, 1);
    writeFourBits(0x08, 0, 40, 1);
    
    writeFourBits(0x00, 0, 40, 1);
    writeFourBits(0x08, 0, 40, 1);
    
    writeFourBits(0x00, 0, 1500, 1);
    writeFourBits(0x01, 0, 1500, 1);
    
    writeFourBits(0x00, 0, 40, 1);
    writeFourBits(0x06, 0, 40, 1);
   
    writeFourBits(0x00, 0, 40, 1);    
    writeFourBits(0x0C, 0, 40, 1);
    
    
    /*OR after 4-bit init
     
     writeLCD(0x28, 0, 50);
     writeLCD(0x08, 0, 50);
     writeLCD(0x01, 0, 1700);
     writeLCD(0x07, 0, 50);
     writeLCD(0xCC, 0, 50);
     
     */
    

}

/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s) {
    
    int i = 0;
    
    while(s[i] != '\0'){
        
        printCharLCD(s[i]);
        
        i++;
        
    }
    
    //TODO:
}

/*
 * Clear the display.
 */
void clearLCD(){
    // clear LCD is the bit string "0000000001"
    writeLCD(0x01, 0, 1640);
    
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y){
    //DDRAM is bit string "001ADD" after the first three bits, data can be written or read
    
    unsigned char addr;
    
    addr = (y-1)*0x40+(x-1);
    addr = addr + 0x80;
    
    writeLCD(addr, 0, 50);
    
    
    
}

/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD(){
    initLCD();
    
    int i = 0;
    printCharLCD('c');
    
    
    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    printStringLCD("Hello!");
    moveCursorLCD(1, 2);
    for(i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    for(i = 0; i < 1000; i++) delayUs(1000);
    
}

char* getTimeString(unsigned int c){

    int min=0;
    int sec =0;
    int ms =0;
    static char s[9];




    char minA = '0';
    char minB = '0';
    char minC = '0';
    char secA = '0';
    char secB = '0';
    char secC = '0';
    char msA = '0';
    char msB = '0';
   
/*
    
    min = c / 60000;//MIN_TO_MS;// calculate these values still!!!
    sec = (c - (min * MIN_TO_MS)) / SEC_TO_MS;
    ms = (c - (min * MIN_TO_MS) - (sec * SEC_TO_MS));

*/
    
    min = c / 60000;//MIN_TO_MS;// calculate these values still!!!
    sec = (c - (min * 60000)) / 1000;
    ms = (c - (min * 60000) - (sec * 1000));

    
    minB = (min/10)+'0';
    minC = (min%10)+'0';

    
    secB = (sec/10)+'0';
    secC = (sec%10)+'0';

    msA = (ms/100) +'0';
    msB = ((ms%100)/10) +'0';

    
    // FORMAT TO BE PRINTED!!
    
    s[0] = minB;
    s[1] = minC;
    s[2] = ':';
    s[3] = secB;
    s[4] = secC;
    s[5] = ':';
    s[6] = msA;
    s[7] = msB;
    s[8] = '\0';

    return s;// return the array of chars
}
