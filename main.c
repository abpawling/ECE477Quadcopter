
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

//#include "system.h"        /* System funct/params, like osc/peripheral config */
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
    /* Declarations */
    
    int * sensorArray;
    bool atDestination,surveyed,landed = 0;
    int heartbeatCount = 0;
    gpsUpdate gpsCurr;
    gpsUpdate gpsFinalDest;
    gpsUpdate initialGPS;
    initialGPS = gpsCurr;
    char * quadcopterState = "Idle";
    char test [7] = "ABCDEFG";
    
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    
    //gpsFinalDest = grabGPSFinal();
    //push = LATGbits.LATG9;

    
    //sensorArray = getSensorArray();
    
    //Testing PWMs
    //OC1R = 4000; //ROLL (pin59 on micro) (pin6 on breakout) (CH1/RC1 on Flight Controller)
    //OC2R = 4000; //PITCH (pin54 on micro) (pin3 on breakout) (CH2/RC2 on Flight Controller)
    //OC3R = 4000; //THROTTLE (pin55 on micro) (pin4 on breakout) (CH3/RC3 on Flight Controller)
    //OC4R = 4000; //YAW (pin58 on micro) (pin5 on breakout) (CH4/RC4 on Flight Controller)
    
    //TODO: set up battery monitoring
    
    //quadcopterState = "Navigate";
    
    while(1)
    //while (!strcmp(quadcopterState,"MissionComplete"))
    {        
        heartbeatCount = heartBeat(heartbeatCount); //know if drone is alive
        
        // ----- Flow of things -----
        checkGo(); //press once for go, press again to kill throttle
        //checkUART();
        //Takeoff();
        //Nav();
        //Survey();
        //Land();
        
        //takeoff
        /*while (sensorArray[4] < 100) //TODO: test for cutoff value
        {
            quadcopterState = "Takeoff";
            //increase altitude
        }*/
        
        //gpsCurr = getGPS();
        //atDestination = Navigate(gpsFinalDest,sensorArray,gpsCurr); //change flight path using sensor data
        
        //Survey
        /*if (atDestination && !strcmp(quadcopterState,"FlyBack"))
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
        }*/
        //LCDWrite(CLEAR,0,0);
        //printMsgToLCD((char*)sensorArray,LINE1);
        
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
    
}
