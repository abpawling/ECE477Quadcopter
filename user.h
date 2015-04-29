#include "utils.h"

//STARTUP
int heartBeat(int); /*Blinks heartbeat LED*/
gpsUpdate grabGPSFinal(); /*Retrieves GPS data from SD card*/
void Arm(void); /*Arm Flight Controller*/

//NAV
bool Navigate(gpsUpdate gpsFinalDest, int* sensorArray,gpsUpdate); /*Top-Level GPS Waypoint navigation function*/
void orientQuad(gpsUpdate,gpsUpdate); /*Orients quadcopter to face the survey location*/
bool flyToFinalDest(gpsUpdate,gpsUpdate,int*); /*Navigates to surey location*/
gpsUpdate* addToCollisionArray(gpsUpdate); /*Add collisions to array - keeps track of collisions for return flight path*/

//SURVEY
bool survey(void); /*Takes photos at surevey location*/

//GET/SET
int* getSensorArray(); /*Used to update sensor data*/
gpsUpdate getGPS(void); /*Used to update GPS data*/
void setGPS(gpsUpdate); /*Used to update GPS data*/

