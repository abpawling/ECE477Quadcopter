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
#include "inits.h"
#include "utils.h"
#include "string.h"
#include "p24EP512GP806.h"
//#include "p24EP512GU810.h"

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
    
    int push = 1; //TODO: set up pushbutton
    int * sensorArray;
    bool atDestination,surveyed,landed = 0;
    int heartbeatCount = 0;
    gpsUpdate gpsCurr;
    gpsUpdate gpsFinalDest;
    gpsUpdate initialGPS;
    initialGPS = gpsCurr;
    char * quadcopterState = "Idle";
    
    gpsFinalDest = grabGPSFinal();
    
    if (push && strcmp(quadcopterState,"Idle")) //Pushbutton
    {
        Arm();
        IFS0bits.T3IF = 0; //Clear Timer4 interrupt flag
        IEC1bits.T4IE = 1; // Enable Timer4 interrupt
        T4CONbits.TON = 1; // Start Timer4
        push = 0;
    }
    
    sensorArray = getSensorArray();
    
    //LEDs
    //PORTBbits.RB12 = 1; //yellow heartbeat LED
    //PORTBbits.RB13 = 1; //green LED
    //PORTBbits.RB14 = 1; //green LED
    //PORTFbits.RF5 = 1; //doesn't work
    
    //TODO: set up battery monitoring
    
    //takeoff
    while (sensorArray[4] < 100) //TODO: test for cutoff value
    {
        quadcopterState = "Takeoff";
        //increase altitude
    }
    
    quadcopterState = "Navigate";
    
    //while(1)
    while (!strcmp(quadcopterState,"MissionComplete"))
    {    
        
        
        gpsCurr = getGPS();
        atDestination = Navigate(gpsFinalDest,sensorArray,gpsCurr); //change flight path using sensor data
        
        //Survey
        if (atDestination && !strcmp(quadcopterState,"FlyBack"))
        {
            PORTBbits.RB13 = 1; //green LED
            quadcopterState = "Survey";
            surveyed = survey();
        }
        
        //Return Home
        if (surveyed)
        {
            quadcopterState = "FlyBack";
            atDestination = Navigate(initialGPS,sensorArray,gpsCurr);
        }
        
        //Land
        if (atDestination && strcmp(quadcopterState,"FlyBack"))
        {
            quadcopterState = "Landing";
            //TODO: add land function
            //landed = land();
            
        }
        
        if (landed)
        {
            quadcopterState = "MissionComplete";
        }
        
        if (heartbeatCount >= 8000)
        {
            PORTBbits.RB12 = 1; //yellow heartbeat LED
            if (heartbeatCount >= 10000)
            {
                heartbeatCount = 0;
                //U1TXREG = 0b01010101; //for testing
            }
        }
        else
        {
            PORTBbits.RB12 = 0; //yellow heartbeat LED
        }
        heartbeatCount++;
        
        /*
        // Check for receive errors
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
        */
    }
    
    /*while (strcmp(quadcopterState,"Survey"))
    {
        //take pictures and store to SD card
    }*/
    
}
