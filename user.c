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

#include <stdint.h>          /* For uint32_t definition */
#include <stdbool.h>         /* For true/false definition */
#include <stdlib.h>


#include "user.h"            /* variables/params used by user.c */
#include "system.h"        /* System funct/params, like osc/peripheral config */

#include "p24EP512GP806.h"
//#include "p24EP512GU810.h"

#define COLLISION_COUNT 20
gpsUpdate collisions [COLLISION_COUNT];
int collisionIndex = 0;

/******************************************************************************
 * 
 * Arms Flight Controller
 * 
 ******************************************************************************/
void Arm()
{
    OC4R = 7000; //YAW
    OC3R = 4000; //7000; //THROTTLE
}

/******************************************************************************
 * 
 * Keeps track of objects in flight path
 * 
 ******************************************************************************/
gpsUpdate* addToCollisionArray(gpsUpdate currGPS)
{
    collisions[collisionIndex] = currGPS;
    collisionIndex++;
    return collisions;

}

/******************************************************************************
 * 
 * Controls quadcopter
 * 
 ******************************************************************************/
 bool Navigate(gpsUpdate GPSFinal, int* sensorArray, gpsUpdate currentGPS)
{
    
    //face GPSFinal location
    orientQuad(currentGPS,GPSFinal);
    
    flyToFinalDest(currentGPS,GPSFinal,sensorArray);
 }
 
 bool flyToFinalDest(gpsUpdate currGPS, gpsUpdate finalGPS, int * sensorArray)
 {
    #define DETECTION_CUTOFF 25 
    bool frontFlag,backFlag,leftFlag,rightFlag,downFlag,objectDetected = 0;
    
    while (currGPS.latitude != finalGPS.latitude && currGPS.longitude != finalGPS.longitude) //TODO: add error tolerance
    {
        currGPS = getGPS();
        if (sensorArray[0] >= DETECTION_CUTOFF) {frontFlag = 1;} //FRONT Sensor value
        if (sensorArray[1] >= DETECTION_CUTOFF) {backFlag = 1;} //BACK Sensor value
        if (sensorArray[2] >= DETECTION_CUTOFF) {leftFlag = 1;} //LEFT Sensor value
        if (sensorArray[3] >= DETECTION_CUTOFF) {rightFlag = 1;} //RIGHT Sensor value
        if (sensorArray[4] >= DETECTION_CUTOFF) {downFlag = 1;} //DOWN Sensor value

        if (frontFlag || backFlag || leftFlag || rightFlag)
        {
            objectDetected = 1;
            //pause navigation for testing
            //collisions = addToCollisionArray(currGPS);
        }

        //TODO: Finish
        if (frontFlag) // && currGPS.latitude < finalGPS.latitude) // && 
        {
            if (currGPS.longitude < finalGPS.longitude)
            {
                //go east
            }
            else
            {
                //go west
            }
        }
        
        //?
        if (backFlag) // && currGPS.latitude < finalGPS.latitude) // && 
        {
            if (currGPS.longitude < finalGPS.longitude)
            {
                //go east
            }
            else
            {
                //go west
            }
        }
        
        if (leftFlag)
        {
            if (currGPS.latitude < finalGPS.latitude)
            {
                //go north
            }
            else
            {
                //go south
            }
        }
        
        if (rightFlag)
        {
            if (currGPS.latitude < finalGPS.latitude)
            {
                //go north
            }
            else
            {
                //go south
            }
        }
        
        
    
    }
    
    
 }
 
 void orientQuad(gpsUpdate currentGPS, gpsUpdate GPSFinal)
 {
     //TODO: add error tolerance
     if (currentGPS.longitude < GPSFinal.longitude)
    {
        //east
        while (currentGPS.eastWest != 'E')
        {
            //spin east
        }
        
    }
    
    if (currentGPS.longitude > GPSFinal.longitude)
    {
        //east
        while (currentGPS.eastWest != 'W')
        {
            //spin west
        }
        
    }
    
    if (currentGPS.latitude < GPSFinal.latitude)
    {
        //east
        while (currentGPS.northSouth != 'N')
        {
            //spin north
        }
        
    }
    
    if (currentGPS.latitude > GPSFinal.latitude)
    {
        //east
        while (currentGPS.northSouth != 'S')
        {
            //spin south
        }
        
    }
 }
 
 gpsUpdate grabGPSFinal()
 {
     gpsUpdate final;
     
     //final.latitude = ;
     //final.longitude = ;
     
     /*final.altitude = ;
     final.eastWest = ;
     final.northSouth = ;*/
     return final;
 }
 
 bool survey(void)
 {
     int done = 0;
     
     //survey
     done = 1;
     
     return done;
 }
 
