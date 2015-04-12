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
#include <stdio.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */
#include "inits.h"
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
    
    int push = 1; //TODO set up pushbutton
    int * sensorArray;
    int finalDest;
    bool atDestination;
    
    if (push) //Pushbutton
    {
        Arm();
        IFS0bits.T3IF = 0; //Clear Timer4 interrupt flag
        IEC1bits.T4IE = 1; // Enable Timer4 interrupt
        T4CONbits.TON = 1; // Start Timer4
        push = 0;
    }
    
    
    while(1)
    {    
        
        sensorArray = getSensorArray();
        atDestination = Navigate(finalDest,sensorArray); //change flight path using sensor data
        
        char ReceivedChar = 0;
        int a;
        
        /* Check for receive errors */
        if(U1STAbits.FERR == 1)
        {
            continue;
        }
        // Must clear the overrun error to keep UART receiving 
        if(U1STAbits.OERR == 1)
        {
            U1STAbits.OERR = 0;
            continue;
        }
        // Get the data
        if(U1STAbits.URXDA == 1)
        {
            a = 1;
            ReceivedChar = U1RXREG;
        }
       
        //printf("Receive Data: %s",ReceivedChar);
        
    }
    
}
