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

//#include "p24EP512GP806.h"
#include "p24EP512GU810.h"
/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

void Arm()
{
    OC1R = 7000; //ROLL
    OC3R = 7000; // THROTTLE
}

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

 bool Navigate(int finalDest)
{
    //declarations
     //char orientation;

     
     /*if (orientation == "N" && finalDest.orientation != "N")
     {
        //rotate until facing orientation

     }*/

    //generate linked list for traversal
    /*for (i = 0;i <= 5;i++)
    {
        current = (waypoint* )malloc(sizeof(waypoint));
        current->coordinate = i//data + 4;
        current->next = head;
        head = current;
    }

    current = head;*/
    
 }
