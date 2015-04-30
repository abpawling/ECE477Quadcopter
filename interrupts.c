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
#include <stdbool.h>

#include "user.h"          /* User funct/params, such as InitApp */
#include "utils.h"
#include "p24EP512GP806.h"
#include <string.h>
//#include "p24EP512GU810.h"                                                          */

int armCount = 0; //global var to get proper ARM timing of flight controller

// Positions                       F,B,L,R,D,count
int sensorArray [SENSOR_COUNT_AMOUNT] = {0,0,0,0,0,0};
gpsUpdate gp;

/******************************************************************************/
/* Get/Set Routines                                                         */
/******************************************************************************/

int * getSensorArray()
{
    return sensorArray; 
}

gpsUpdate getGPS()
{
    return gp; 
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
int h,k,j,commaCount,latIndex,longIndex,write = 0; //hazardous global vars for interrupts
char ReceiveBuff [GPS_LENGTH];
char Lat [9];
char Long [9];
char Altitude [6];

void __attribute__((__interrupt__)) _U1RXInterrupt(void)
{
    
    if (h == 0)
    {
        h = 1;
        for(j = 0; j <= 100;j++)
        {
            ReceiveBuff[j] = 1;
        }
    }
    
    ReceiveBuff[k] = U1RXREG;
    k++;
    
    if (ReceiveBuff[k] == ',')
    {
        commaCount++;
    }
    
    if (commaCount == 2)
    {
        Lat[latIndex] = ReceiveBuff[k];
        latIndex++;
    }
    
    if (commaCount == 3)
    {
        gp.eastWest = ReceiveBuff[k];
    }
    
    if (commaCount == 4)
    {
        Long[longIndex] = ReceiveBuff[k];
        longIndex++;
    }
    
    if (commaCount == 5)
    {
        gp.northSouth = ReceiveBuff[k];
    }
    
    //getting data formatted    
    gp.latitude = parse(Lat, "lat");
    gp.longitude = parse(Long, "long");
    gp.altitude = parse(Altitude, "alt");
    
    setGPS(gp);
    
    if(k == 100)
    {
        //LCDWrite(CLEAR,0,0);
        /*for (write = 0;write <= 7;write++)
        {
            LCDWrite(ReceiveBuff[write],1,0);
        }
        LCDWrite(LINE2,0,0);
        for (write = 8;write <= 15;write++)
        {
            LCDWrite(ReceiveBuff[write],1,0);
        }*/
        
        //printMsgToLCD(ReceiveBuff,LINE1); //add shift and this should work
        
        k = 0;                
    }
    
    
    //U1TXREG = 'a'; // Transmit one character
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
bool triggerDown = 0;
void __attribute__((__interrupt__, no_auto_psv)) _T5Interrupt(void)
{    
    if (c == 10 ){
        PORTBbits.RB0 = 1;//0; //Active low configuration -- assert trigger
        c = 0;
        triggerDown = 1;
        //T3CONbits.TON = 1; // Start Timer3
        //sensorArray[0] = 0;
        //sensorArray[1] = 0;
        //sensorArray[2] = 0;
        //sensorArray[3] = 0;
        //sensorArray[4] = 0;
        //sensorArray[5] = 0;
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
    //interrupt counter
    sensorArray[5]++;
    
    //LCDWrite(CLEAR,0,0);
    /*LCDWrite("A",1,0);
    LCDWrite("B",1,0);
    LCDWrite("C",1,0);*/
    //printMsgToLCD(sensorArray[0],LINE1);
    //printMsgToLCD("HERE",LINE1);
    //----- Object Detection -----
    if (PORTBbits.RB1)
    {
        sensorArray[0]++; //Front Sensor
    }
    
    /*if (PORTBbits.RB2)
    {
        sensorArray[1]++; //Back Sensor
    }*/
    
    if (PORTBbits.RB3) //NOT INVERTED
    {
        sensorArray[2]++; //Left Sensor
    }
    
    if (PORTBbits.RB4) //TODO: INTERRUPT NEEDS CONFIGURED
    {
        sensorArray[3]++; //Right Sensor
    }
    
    if (PORTBbits.RB5) //TODO: INTERRUPT NEEDS CONFIGURED
    {
        sensorArray[4]++; //Down Sensor
    }
    
    if (sensorArray[5] == 100) //30
    {
        T3CONbits.TON = 0; // Stop Timer3
        sensorArray[5] = 0;
        sensorArray[0] = 0; //reset count
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
        OC3R = 4800; //THROTTLE

        //IEC1bits.T4IE = 0; // Disable Timer4 interrupt
        //T4CONbits.TON = 0; // Stop Timer4
        
    }
    
    if (armCount == 10) //kill throttle
    {
        OC3R = 4400; //THROTTLE

        IEC1bits.T4IE = 0; // Disable Timer4 interrupt
        T4CONbits.TON = 0; // Stop Timer4
        
    }
    armCount++;
    IFS1bits.T4IF = 0; //Clear Timer4 interrupt flag
}

/******************************************************************************
 * 
 * DMA0 ISR - SPI Transmission
 * 
 ******************************************************************************/
/*void __attribute__((__interrupt__)) _DMA0Interrupt(void)
{
    static unsigned int BufferCount = 0; // Keep record of the buffer that contains TX data
    if(BufferCount == 0)
    {
        //TxData(BufferA); // Transmit SPI data in DMA RAM Primary buffer TODO: ??
        
    }
    else
    {
        //TxData(BufferB); // Transmit SPI data in DMA RAM Secondary buffer TODO: ??
        
    }
        BufferCount ^= 1;
        IFS0bits.DMA0IF = 0; // Clear the DMA0 Interrupt flag
}
  */