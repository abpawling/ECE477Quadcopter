/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__PIC24E__)
    	#include <p24Exxxx.h>
    #elif defined (__PIC24F__)||defined (__PIC24FK__)
	#include <p24Fxxxx.h>
    #elif defined(__PIC24H__)
	#include <p24Hxxxx.h>
    #endif
#endif

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */
//#include "p24EP512GP806.h"
#include "p24EP512GU810.h"

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    TRISD = 0; //Trisiodhf


    //PWM initilization
    OC1CON1 = 0; /* It is a good practice to clear off the control bits initially */
    OC1CON2 = 0;
    OC1CON1bits.OCTSEL = 0; /* This selects the peripheral clock as the clock input to the OC
module */
    OC1R = 1000; /* This is just a typical number, user must calculate based on the
waveform requirements and the system clock */
    OC1RS = 2000; /* Determines the Period */
    OC1CON2bits.SYNCSEL = 0x1F; /* This selects the synchronization source as itself */
    OC1CON1bits.OCM = 6; /* This selects and starts the Edge Aligned PWM mode*/

    // Initialize Timer2
    T2CONbits.TON = 0; // Disable Timer
    T2CONbits.TCS = 0; // Select internal instruction cycle clock
    T2CONbits.TGATE = 0; // Disable Gated Timer mode
    T2CONbits.TCKPS = 0b00; // Select 1:1 Prescaler
    TMR2 = 0x00; // Clear timer register
    PR2 = 500; // Load the period value'

    // Enable Timer
    T2CONbits.TON = 1; // Start Timer

    RPOR5bits.RP84R = 0b010000; //Maps Output Compare 1 to output pin RP84 (pin 100)


    /* TODO <INSERT USER APPLICATION CODE HERE> */

    while(1)
    {

        PORTD = 0xff;
    }
}
