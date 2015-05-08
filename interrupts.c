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

#include <stdint.h>        /* Includes uint16_t definition */

#include "user.h"          /* User funct/params, such as InitApp */
#include "utils.h"
#include "p24EP512GP806.h"
//#include "p24EP512GU810.h"

//hazardous global vars for interrupts
int h = 0;
int k = 0;
int j = 0;
int lw = 0;
int commaCount = 0;
int latIndex = 0;
int longIndex = 0;
int write = 0;
char ReceiveBuff [GPS_LENGTH];
char Lat [9];
char Long [9];
char Altitude [6];
char gpsTest [10] = {0,0,0,0,0,0,0,0,0,0};

int armCount = 0; //global var to get proper ARM timing of flight controller

// Positions                             F,B,L,R,D,count
int sensorArray [SENSOR_COUNT_AMOUNT] = {0,0,0,0,0,0};
int sensorArrayFinal [SENSOR_COUNT_AMOUNT] = {30,30,30,30,30,0};
//int * sensorArray;
gpsUpdate gp;

/******************************************************************************/
/* Get/Set Routines                                                         */
/******************************************************************************/

int getSensorArrayVal(int index)
{
    return sensorArrayFinal[index]; 
}

/*void setSensorArray(int * sa)
{
    sensorArray = sa;
}*/

char getGPSBuff(int index)
{
    return ReceiveBuff[index];
}

gpsUpdate getGPS()
{
    return gp; 
}

int getArmCount(void)
{
    return armCount;
}

void setGPS(gpsUpdate g)
{
    gp = g; 
}

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/******************************************************************************
 * 
 * UART1 ISR - U1RX INTERRUPT
 * 
 ******************************************************************************/
char buf = 0;
void __attribute__((__interrupt__)) _U1RXInterrupt(void)
{
    
    /*if (h == 0)
    {
        h = 1;
        for(j = 0; j <= 100;j++)
        {
            ReceiveBuff[j] = 1;
        }
    }*/
    
    //ReceiveBuff[k] = U1RXREG;
    buf = U1RXREG;
    
    /*if (U1RXREG != ',')
    {
        gpsTest[k] = ReceiveBuff[k];
    }*/
    
    if (buf == '$')
    {
        commaCount = 0;
        latIndex = 0;
        longIndex = 0;
    }
    
    if (buf == ',')
    {
        commaCount++;
    }
    
    else if (commaCount == 2)
    {
        Lat[latIndex] = buf;
        latIndex++;
    }
    
    else if (commaCount == 3)
    {
        //LCDWrite(RET_HOME,0,0);
        //printMsgToLCD(Lat,LINE1);
        gp.eastWest = buf;
    }
    
    else if (commaCount == 4)
    {
        Long[longIndex] = buf;
        longIndex++;
    }
    
    else if (commaCount == 5)
    {
        gp.northSouth = buf;
    }
    k++;
 
    if(k == 500)
    {
        gp.latitude1 = parse(Lat, 1);
        gp.latitude2 = parse(Lat, 2);
        gp.longitude1 = parse(Long, 3);
        gp.longitude2 = parse(Long, 4);
        
        /*
        LCDWrite(LINE1,0,0);
        LCDWrite(RET_HOME,0,0);
        for (lw = 1;lw <= 8;lw++)
        {
            LCDWrite(Lat[lw],1,0);
        }
        LCDWrite(RET_HOME,0,0);
        LCDWrite(LINE2,0,0);
        for (lw = 1;lw <= 8;lw++)
        {
            LCDWrite(Long[lw],1,0);
        }
         */
        
        k = 0;                
    }
    IFS0bits.U1RXIF = 0; // Clear RX Interrupt flag
    
}

/******************************************************************************
 * 
 * UART2 ISR - U2RX INTERRUPT
 * 
 ******************************************************************************/
char cameraData [CAM_DATA_AMOUNT];
int cam = 0;
/*void __attribute__((__interrupt__)) _U2RXInterrupt(void)
{
 cameraData[cam] = U2RXREG;
 
 if (cam == 100)
 {
    //write to SD via SPI - done through SPI Interrupt
    // SPI interrupt flag = 1
    cam = 0;
 }
}*/

/******************************************************************************
 * 
 * Timer5 ISR - SENSOR TRIGGER INTERRUPT
 * 
 ******************************************************************************/
int c = 0;
int triggerDown = 0;
void __attribute__((__interrupt__, no_auto_psv)) _T5Interrupt(void)
{    
    if (c == 10 ){
        PORTBbits.RB0 = 1;//0; //Active low configuration -- assert trigger
        c = 0;
        triggerDown = 1;
        //T3CONbits.TON = 1; // Start Timer3
    }
    else{
        if (triggerDown)
        {
            T3CONbits.TON = 1; // Start Timer3
            triggerDown = 0;
        }
        //T3CONbits.TON = 1; // Start Timer3
        PORTBbits.RB0 = 0;//1; //Active low configuration
        c++;        
        
    }
    IFS1bits.T5IF = 0; //Clear Timer5 interrupt flag
}

/******************************************************************************
 * 
 * Timer3 ISR - SENSOR ECHO INTERRUPT
 * 
 ******************************************************************************/
void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void)
{    
    int i = 0;
    //interrupt counter
    sensorArray[5]++;
    
    //----- Object Detection -----
    if (PORTBbits.RB1)
    {
        sensorArray[0]++; //Front Sensor
    }
    
    //Back Sensor not used
    /*if (PORTBbits.RB2)
    {
        sensorArray[1]++; //Back Sensor
    }*/
    
    if (PORTBbits.RB3)
    {
        sensorArray[2]++; //Left Sensor
    }
    
    if (PORTBbits.RB4) //TODO: INTERRUPT NEEDS CONFIGURED?
    {
        sensorArray[3]++; //Right Sensor
    }
    
    if (PORTBbits.RB5) //TODO: INTERRUPT NEEDS CONFIGURED?
    {
        sensorArray[4]++; //Down Sensor
    }
    
    if (sensorArray[5] == 30) //100
    {
        T3CONbits.TON = 0; // Stop Timer3
        for(i = 0; i <= 5; i++)
        {
            sensorArrayFinal[i] = sensorArray[i];
        }
        for(i = 0; i <= 5; i++)
        {
            sensorArray[i] = 0;
        }
    } 
    
    IFS0bits.T3IF = 0; //Clear Timer3 interrupt flag
}

/******************************************************************************
 * 
 * Timer4 ISR - FLIGHT CONTROLLER INTERRUPT
 * 
 ******************************************************************************/
void __attribute__((__interrupt__, no_auto_psv)) _T4Interrupt(void)
{
    
    
    if (armCount == 4)
    {
        OC4R = 6000; //YAW To neutral 
        //OC3R = 4600; //THROTTLE

        //IEC1bits.T4IE = 0; // Disable Timer4 interrupt
        //T4CONbits.TON = 0; // Stop Timer4
        
    }
    
    if (armCount > 4 && armCount < 23)
    {
        OC3R += 500; //THROTTLE        
    }
    
    if (armCount >= 22) //kill throttle
    {
        OC3R = 4400; //THROTTLE
        IEC1bits.T4IE = 0; // Disable Timer4 interrupt
        T4CONbits.TON = 0; // Stop Timer4
        
    }
    
    armCount++;
    IFS1bits.T4IF = 0; //Clear Timer4 interrupt flag
}
