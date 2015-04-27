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
#include "LinkedList.h"
#include "system.h"        /* System funct/params, like osc/peripheral config */

#include "p24EP512GP806.h"
//#include "p24EP512GU810.h"

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
waypoint * InitCollisionList(int coord)
{
    /*
    //declarations
    waypoint *head = NULL;
    waypoint *current;
    int i;

    #define COLLISION_COUNT 20
    static waypoint collisions [COLLISION_COUNT];

    //get current GPS waypoint
    //data = getCurrPos();

     */
    
}

/******************************************************************************
 * 
 * Controls quadcopter
 * 
 ******************************************************************************/
 bool Navigate(int finalDest, int* sensorArray)
{
     //char orientation;
     
    bool frontFlag = 0;
    bool backFlag = 0;
    bool leftFlag = 0;
    bool rightFlag = 0;
    bool downFlag = 0;
    
    if (sensorArray[0] >= 25) {frontFlag = 1;} //FRONT Sensor value
    if (sensorArray[1] >= 25) {backFlag = 1;} //BACK Sensor value
    if (sensorArray[2] >= 25) {leftFlag = 1;} //LEFT Sensor value
    if (sensorArray[3] >= 25) {rightFlag = 1;} //RIGHT Sensor value
    if (sensorArray[4] >= 25) {downFlag = 1;} //DOWN Sensor value*/
    
    //turn and "face" destination
    //head straight to the destination
    
    //avoid obstacles
    
     /*if (orientation == "N" && finalDest.orientation != "N")
     {
        //rotate until facing orientation

     }*/    
 }
 
