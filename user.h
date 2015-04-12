/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */


void Arm(void);            /*Arm Flight Controller*/
bool Navigate(int finalDest, int* sensorArray); /*GPS Waypoint navigation function*/
//waypoint * InitCollisionList(int coord); /*Initialize the list that keeps track of collisions for return flight path*/


int* getSensorArray();

