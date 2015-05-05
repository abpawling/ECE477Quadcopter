#include "utils.h"


int heartBeat(int); /*Blinks heartbeat LED*/
int Arm(); /*Arm Flight Controller*/
int checkGo(); /*Arms flight controller and kills throttle */
int checkInterruptErrors(void);
int takeoff(int); /*Sets quadcopter to desired altitude*/
int land(void); /*Lands quadcopter*/
int checkBattery(void); /*Monitors battery and returns various levels*/

//NAV
int Navigate(gpsUpdate gpsFinalDest, int sensorArray[],gpsUpdate); /*Top-Level GPS Waypoint navigation function*/
void orientQuad(gpsUpdate,gpsUpdate); /*Orients quadcopter to face the survey location*/
int flyToFinalDest(gpsUpdate,gpsUpdate,int[]); /*Navigates to surey location*/
gpsUpdate* addToCollisionArray(gpsUpdate); /*Add collisions to array - keeps track of collisions for return flight path*/

//SURVEY
int survey(void); /*Takes photos at surevey location*/

//SD
int InitSD(void);
gpsUpdate grabGPSFinal(); /*Retrieves GPS data from SD card*/
int WriteSD(char*);
int ReadSD(void);

//GET/SET
int getSensorArrayVal(int);
gpsUpdate getGPS(void); /*Used to update GPS data*/
char getGPSBuff(int);
void setGPS(gpsUpdate); /*Used to update GPS data*/
int getArmCount(void);
//void setSensorArray(int * sa);

