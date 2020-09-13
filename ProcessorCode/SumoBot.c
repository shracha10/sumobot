/*==============================================================================
	Project: Activity 3 - Variables
	Version: 3.1				Date: December 10, 2018
	Target: CHRP3.1				Processor: PIC16F886

	A demonstration of constant and variable assignment and the use of variables
    as event counters.
==============================================================================*/

#include    "xc.h"              // XC compiler general include file

#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "CHRP3.h"            // Include user-created constants and functions

/*==============================================================================
    Program constant definitions. Constants must be assigned before compilation
    but cannot be changed while the program is running.
==============================================================================*/

//const char ledsOn = 0b11110000;
//const char ledsOff = 0;

//const char pivotLLeft = 0b00000010;
//const char pivotRRight = 0b00000100;

//Sumo constants
#define FORWARD     0b00000110
#define BACKWARD    0b00001001
#define RIGHT       0b00000101
#define LEFT        0b00001010

const char stop = 0;
const char search = 0;
const char attack = 1;
const char attackSearch;
//const char attackSearchLeft = 3;

/*==============================================================================
    Program variable definitions. Variables can be assigned before compilation
    and can also be changed while the program is running.
==============================================================================*/
unsigned char range;
bool dir = true;
unsigned char mode = search;
unsigned char targetCounter = 0;
unsigned char c = 50;

//unsigned char presses = 0;
//bool isPressed = false;
void delay(void)
{
    for(unsigned char s=5; s!=0; s--)
    {
        for(unsigned char i=200; i!=0;i--)
        {
            BEEPER = !BEEPER;
            __delay_us(500);
        }
        __delay_ms(900);
    }
}

unsigned char sonar(void)
    {
        while (ECHO == 1);
        
        __delay_ms(1);
        TRIG = 1;
        __delay_us(20);
        TRIG =0;
        range = 0;
        
        while (ECHO == 0);
        
        while (ECHO == 1)
        {
            __delay_us(50);
                if (range < 100)
                {
                    range ++;
                }
                else
                {
                    return (0);
                }
        }
        return (range);
    }
/*==============================================================================
    Main program loop. The main() function is called first by the compiler.
==============================================================================*/

int main(void)                  // Run this code on every startup
{
    initPorts();                // Initialize I/O pins and peripherals
    
    while (S6 == 1 && S7 == 1);
    
    if (S7 == 0)             //Sets bot to turn right
    {
        LED12 = 1;
        dir = true;
        delay();
        mode = search;
    }
    if (S6 == 0)             //Sets bot to turn left
    {
        LED12 = 1;
        dir = false;
        delay();
        mode = search;
    }

    while(1)
    {
        while(mode == search)       //Search mode
        {
            LED3 = 0;
            if(Q1 == 0)
            {
                PORTB = BACKWARD;
                __delay_ms(1000);
                PORTB = RIGHT;
                __delay_ms(3000);
            }
            if(Q2 == 0)
            {
                PORTB = BACKWARD;
                __delay_ms(1000);
                PORTB = LEFT;
                __delay_ms(3000);
            }

            if (dir == true)
            {
                PORTB = RIGHT;            
            }
            else
            {
                PORTB = LEFT;
            }

            if (sonar() > 0)
            {
                targetCounter = 3;
                mode = attack;
            }
            __delay_ms(50);
        }

        while(mode == attack)               //Attack mode
        {
            PORTB = FORWARD;                //Starts going forward
            LED3 = 1;
            if(Q1 == 0)                     //Checks Q1
            {
                PORTB = BACKWARD;
                __delay_ms(1000);
                PORTB = RIGHT;
                __delay_ms(3000);
            }
            if(Q2 == 0)                     //Checks Q2
            {
                PORTB = BACKWARD;
                __delay_ms(1000);
                PORTB = LEFT;
                __delay_ms(3000);
            }
            
            if (sonar() == 0)               // decreases the "target counter" variable
            {

                targetCounter--;
                mode = attackSearch;
                if(targetCounter == 0)
                {
                    dir = !dir;
                    mode = search;
                }    
            }
            if (sonar() == 0)               // if the target counter hits 0 the bot goes into search mode
            {
                targetCounter = 3;
                dir = !dir;
            }
            __delay_ms(50);
        }
    }
    
    while (mode == attackSearch)                            // quickly searches if the target is lost
        {
            if (dir == true)
            {
                PORTB = RIGHT;
                for(unsigned char r = c; r != 0; r --)
                {
                    if (sonar() > 0)
                    {
                        mode = attack;
                    }
                }
                PORTB = LEFT;
                for(unsigned char rl = c; rl != 0; rl --)
                {
                    if (sonar() > 0)
                    {
                        mode = attack;
                    }
                }
            }
            else
            {
                PORTB = LEFT;
                for(unsigned char l = c; l != 0; l --)
                {
                    if (sonar() > 0)
                    {
                        mode = attack;
                    }
                }
                PORTB = RIGHT;
                for(unsigned char lr = c; lr != 0; lr --)
                {
                    if (sonar() > 0)
                    {
                        mode = attack;
                    }
                }
            }
            __delay_ms(50);
        }
}
    
//    while(1)                  
//    {
//        PORTB = sonar();
//        __delay_ms(100);
//    }

//     while(1)
//    {
//        PORTB = FORWARD;
//    }
//        
//    PORTB = pivotRRight;
//    SLEEP();
    
//    LED12 = 1;
//        while(1)              // LED and Phototransistor Tester
//        {
//            if(Q1==0)
//            {
//                LED3 = 1;
//            }
//            else
//            {
//                LED3 = 0;
//            }
//            if(Q2==0)
//            {
//                LED4 = 1;
//            }
//            else
//            {
//                LED4 = 0;
//            }
//        }
//}