#include "utils.h"

void Arm(void);            /*Arm Flight Controller*/
bool Navigate(gpsUpdate gpsFinalDest, int* sensorArray,gpsUpdate); /*GPS Waypoint navigation function*/
gpsUpdate* addToCollisionArray(gpsUpdate); /*Initialize the that that keeps track of collisions for return flight path*/

int* getSensorArray();
gpsUpdate getGPS(void);
void setGPS(gpsUpdate);
gpsUpdate grabGPSFinal();
void orientQuad(gpsUpdate,gpsUpdate);
bool flyToFinalDest(gpsUpdate,gpsUpdate,int*);
bool survey(void);

