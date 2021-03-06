/* 
 * File:   utils.h
 * Author: Zach Schaffter
 *
 * Created on April 18, 2015, 1:15 PM
 */

//---------- Macros ----------

//LCD
#define CLEAR 0x001
#define RET_HOME 0x002
#define CONFIG 0b0000001111 //Display ON, cursor ON, blink ON
#define SHIFTRIGHT 0b00010100
#define SHIFTLEFT 0b00010000
#define SCROLLLEFT 0b00011000
#define SCROLLRIGHT 0b00011100
#define TWOLINE 0b00111000
#define LINE1 0b10000000
#define LINE2 0b11000000
#define CLEAR 0x001
#define HOVER 6800

//SYSTEM
#define SYS_FREQ        8000000L
#define FCY             SYS_FREQ/2

//OTHER
#define DETECTION_CUTOFF 20
#define COLLISION_COUNT 20
#define SENSOR_COUNT_AMOUNT 6
#define GPS_LENGTH 100
#define CAM_DATA_AMOUNT 100

//---------- Functions ----------

//LCD
void printMsgToLCD(char *,char); //Usage: arg1= message, arg2= line#
void LCDWrite(char,int,int); //Usage: arg1 = character, arg2 = rs, arg3 = rw
void wait(void);

//PARSE GPS DATA
long parse(char*,int);

//OSC
void ConfigureOscillator(void); /* Handles clock switching/osc initialization */

#ifndef UTILS_H
#define	UTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

    //GPS STRUCTURE: created from parsed GPS data
    struct GPS
    {
        int latitude1;
        int latitude2;
        int longitude1;
        int longitude2;
        long altitude;
        char eastWest;
        char northSouth;
    };

    typedef struct GPS gpsUpdate;



#ifdef	__cplusplus
}
#endif

#endif

