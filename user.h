

void Arm(void);            /*Arm Flight Controller*/
bool Navigate(int finalDest, int* sensorArray); /*GPS Waypoint navigation function*/
//waypoint * InitCollisionList(int coord); /*Initialize the list that keeps track of collisions for return flight path*/

int* getSensorArray();

