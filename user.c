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
#include "user.h"            /* variables/params used by user.c */

#include "p24EP512GP806.h"
//#include "p24EP512GU810.h" //for using dev board

gpsUpdate collisions [COLLISION_COUNT];
int collisionIndex = 0;

/******************************************************************************
 * 
 * Arms Flight Controller
 * 
 ******************************************************************************/
int Arm(int ARMFLAG)
{
    ARMFLAG = 1;
    //printMsgToLCD("ARMING",LINE1);
    OC3R = 4400; //THROTTLE //pin55
    OC4R = 7600; //YAW //pin58
    return ARMFLAG;
}

/******************************************************************************
 * 
 * Checks pushbutton: press once for go, press again to kill throttle
 * 
 ******************************************************************************/
int push = 0;
int armed = 0;
int prevPush = 0;
int disarmCount = 0;
int go = 0;

int checkGo(int ARMFLAG)
//void checkGo(void)
{
    push = PORTGbits.RG9;
    prevPush = push;
    //LATBbits.LATB13 = !push; //green LED
    //LATBbits.LATB14 = !push; //green LED

    // push = 0: open, push = 1: closed
    if (push && !armed) //arm flight controller
    {
        prevPush = 1;
        armed = 1;
        go = 1;
        ARMFLAG = Arm(ARMFLAG);
        IFS0bits.T3IF = 0; //Clear Timer4 interrupt flag
        IEC1bits.T4IE = 1; // Enable Timer4 interrupt
        T4CONbits.TON = 1; // Start Timer4
    }
    
    if (armed && disarmCount < 20)
    {
        disarmCount++;
    }
    
    if (prevPush && !push) 
    {
        push = 1;
        prevPush = 0;
    }
    
    if (push) 
    {
        prevPush = 1; 
    }
    
    if (push && armed && disarmCount >= 20) //kill throttle
    {
        OC3R = 4400; //THROTTLE
        go = 0;
        ARMFLAG = 0;
    }
    return go;
    
}

int land(void)
{
    return 0;
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
 int Navigate(gpsUpdate GPSFinal, int sensorArray[], gpsUpdate currentGPS)
{
    int atDest = 0;
     
    //face GPSFinal location
    //orientQuad(currentGPS,GPSFinal);
    
    atDest = flyToFinalDest(currentGPS,GPSFinal,sensorArray);
    
    return atDest;
 }
 
 int frontEN = 1;
 int backEN = 1;
 int leftEN = 1;
 int rightEN = 1;
 int downEN = 1;
 int gCount = 0;
 int flyToFinalDest(gpsUpdate currGPS, gpsUpdate finalGPS, int sensorArray[])
 {
    gCount++; 
    int frontFlag = 0;
    int backFlag = 0;
    int leftFlag = 0;
    int rightFlag = 0;
    int downFlag = 0;
    
    //if (currGPS.latitude != finalGPS.latitude && currGPS.longitude != finalGPS.longitude) //TODO: add error tolerance
    //{
        //currGPS = getGPS();
        if (sensorArray[0] <= DETECTION_CUTOFF) {frontFlag = 1;} //FRONT Sensor value
        if (sensorArray[1] <= DETECTION_CUTOFF) {backFlag = 1;} //BACK Sensor value
        if (sensorArray[2] <= DETECTION_CUTOFF) {leftFlag = 1;} //LEFT Sensor value
        if (sensorArray[3] <= DETECTION_CUTOFF) {rightFlag = 1;} //RIGHT Sensor value
        if (sensorArray[4] <= DETECTION_CUTOFF) {downFlag = 1;} //DOWN Sensor value
        
        //check for collisions

    /*if (frontFlag)
    {
        OC3R = 4400;
    }*/
    
    //OC1R = 4000; //ROLL (pin59 on micro) (pin6 on breakout) (CH1/RC1 on Flight Controller)
    //OC2R = 4000; //PITCH (pin54 on micro) (pin3 on breakout) (CH2/RC2 on Flight Controller)
    //OC3R = 4000; //THROTTLE (pin55 on micro) (pin4 on breakout) (CH3/RC3 on Flight Controller)
    //OC4R = 4000; //YAW (pin58 on micro) (pin5 on breakout) (CH4/RC4 on Flight Controller)
    
    if (gCount >= 5000)
    {
        //LCDWrite(CLEAR,0,0);
        gCount = 0;
    }   
    
    if (frontFlag && !leftFlag)
    {
        LCDWrite(RET_HOME,0,0);
        printMsgToLCD("left   ",LINE1);
        OC1R = 5500; //ROLL
        OC2R = 6000; //PITCH
        OC4R = 6000; //YAW
    }
    else if (!frontFlag)
    {
        LCDWrite(RET_HOME,0,0);
        printMsgToLCD("forward",LINE1);
        OC1R = 6000; //ROLL
        OC2R = 5500; //PITCH
        OC4R = 6000; //YAW
    }
    else if (leftFlag && !rightFlag)
    {
        LCDWrite(RET_HOME,0,0);
        printMsgToLCD("right  ",LINE1);
        OC1R = 6500; //ROLL
        OC2R = 6000; //PITCH
        OC4R = 6000; //YAW
    }
    else if (rightFlag && !leftFlag)
    {
        LCDWrite(RET_HOME,0,0);
        printMsgToLCD("left   ",LINE1);
        OC1R = 5500; //ROLL
        OC2R = 6000; //PITCH
        OC4R = 6000; //YAW
    }
    
    
    
        /*
        //TODO: Finish
        if (frontFlag) // && currGPS.latitude < finalGPS.latitude) // && 
        {
            //printMsgToLCD("FRONT", LINE1);
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
            //printMsgToLCD("BACK", LINE1);
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
            //printMsgToLCD("LEFT", LINE1);
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
            //printMsgToLCD("RIGHT", LINE1);
            if (currGPS.latitude < finalGPS.latitude)
            {
                //go north
            }
            else
            {
                //go south
            }
        }
        
        if (downFlag)
        {
            //printMsgToLCD("DOWN", LINE2);
        }
         */
        return 0;
    //}
    //else 
    //{
    //    return 1;
    //}
    
    
 }
 
 void orientQuad(gpsUpdate currentGPS, gpsUpdate GPSFinal)
 {
     
 }
 
 gpsUpdate grabGPSFinal()
 {
     gpsUpdate final;
     
     //final.latitude = ;
     //final.longitude = ;
     //final.altitude = ;
     //final.eastWest = ;
     //final.northSouth = ;
     return final;
 }
 
 int survey(void)
 {
     return 0;
 }
 
 int checkBattery(void)
 {
     return 0;
 }

 int heartBeat(int beatCount)
 {
     if (beatCount >= 8000)
        {
            PORTBbits.RB12 = 1; //yellow heartbeat LED
            if (beatCount >= 10000)
            {
                beatCount = 0;
                //U1TXREG = 0b01010101; //for testing
            }
        }
        else
        {
            PORTBbits.RB12 = 0; //yellow heartbeat LED
        }
        beatCount++;
        return beatCount;
 }
 
 int takeoff(int downSensorValue)
 {
    //printMsgToLCD(downSensorValue,LINE2);
    //PSSC#1
    if (downSensorValue < 14) //TODO: test for cutoff value
    {        
        if (OC3R >= 7000)
        {
            OC3R = 7000;
            IEC1bits.T4IE = 0; // Disable Timer4 interrupt
            T4CONbits.TON = 0; // Stop Timer4
        }
        
        return 0;
    }
    else
    {
        OC3R = 5000;
        IEC1bits.T4IE = 0; // Disable Timer4 interrupt
        T4CONbits.TON = 0; // Stop Timer4
        return 1; //at desired altitude
    }
    //return 1;
     
 }
 
 int checkInterruptErrors(void)
 {
     // Check for receive errors 
        if(U1STAbits.FERR == 1) //||U2STAbits.FERR == 1) 
        {
            return 1;
        }
        
        // Must clear the overrun error to keep UART receiving 
        if(U1STAbits.OERR == 1)
        {
            U1STAbits.OERR = 0;
            return 1;
        }
        return 0;
 }
 
 int InitSD(void)
 {
     return 1;
 }
 
int WriteSD(char* camData)
{
    return 1;
}

int ReadSD(void)
{
    return 1;
}
 
