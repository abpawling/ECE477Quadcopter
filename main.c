
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
    
    // Positions            F,B,L,R,D,count
    //int * sensorArray;// = {0,0,0,0,0,0};
    int sensorArray [SENSOR_COUNT_AMOUNT]= {30,30,30,30,30,0};
    int batteryLowFlag = 0;
    int goFlag = 0;
    int atDestinationFlag = 0;
    int takeoffDoneFlag = 0;
    int surveyDoneFlag = 0;
    int landDoneFlag = 0;
    int atHQFlag = 0;
    int prevBattLowFlag = 0;
    int interruptError = 0;
    int heartbeatCount = 0;
    gpsUpdate gpsCurr;
    gpsUpdate gpsFinalDest;
    gpsUpdate initialGPS;
    initialGPS = gpsCurr;
    int i = 0;
    int ARMFLAG = 0;
    
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    
    //Testing PWMs
    //OC1R = 4000; //ROLL (pin59 on micro) (pin6 on breakout) (CH1/RC1 on Flight Controller)
    //OC2R = 4000; //PITCH (pin54 on micro) (pin3 on breakout) (CH2/RC2 on Flight Controller)
    //OC3R = 4000; //THROTTLE (pin55 on micro) (pin4 on breakout) (CH3/RC3 on Flight Controller)
    //OC4R = 4000; //YAW (pin58 on micro) (pin5 on breakout) (CH4/RC4 on Flight Controller)
    
    //get GPS location from SD Card
    //gpsFinalDest = grabGPSFinal();
    
    while(1)
    {           
        interruptError = checkInterruptErrors(); //TODO: check if needed
        if (interruptError)
        {
            continue;
        }
        
        //Know if drone is alive
        heartbeatCount = heartBeat(heartbeatCount);
        i = 0;
        //Grab sensor values from interrupt
        for(i = 0; i <= SENSOR_COUNT_AMOUNT;i++)
        {
            sensorArray[i] = getSensorArrayVal(i);
        }
        i = 1;
        gpsCurr = getGPS();
        
        // --------------- Final Main Control Flow ---------------
        if (prevBattLowFlag) //ensures battery low flag is consistent
        {
            batteryLowFlag = 1;
        }
        else
        {
            batteryLowFlag = checkBattery();
        }
        
        if (!batteryLowFlag)
        {
            prevBattLowFlag = 0;
            goFlag = checkGo(ARMFLAG); //press once for go, press again to kill throttle
            
            if (goFlag && !takeoffDoneFlag)
            {
                takeoffDoneFlag = takeoff(sensorArray[4]);
            }
            
            if (takeoffDoneFlag && !atDestinationFlag)
            {
                atDestinationFlag = Navigate(gpsFinalDest,sensorArray,gpsCurr,ARMFLAG);
                
            }
            
            if (atDestinationFlag && !surveyDoneFlag)
            {
                surveyDoneFlag = survey();
            }
            
            if (surveyDoneFlag && !atHQFlag)
            {
                atHQFlag = Navigate(initialGPS,sensorArray,gpsCurr,ARMFLAG);
            }
            
            if (atHQFlag && !landDoneFlag)
            {
                landDoneFlag = land();
            }
            
            if (landDoneFlag)
            {
                printMsgToLCD("Mission",LINE1);
                printMsgToLCD("Complete",LINE2);
            }
        }
        else
        {
            prevBattLowFlag = 1;
            landDoneFlag = land();
            
            if (landDoneFlag)
            {
                printMsgToLCD("Low",LINE1);
                printMsgToLCD("Battery",LINE2);
            }
           
        }

    }
    
}
