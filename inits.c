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

#include "inits.h"            /* variables/params used by inits.c */
#include "utils.h"

void InitApp(void)
{
    
    //Initialize Oscillator?
  
    //_PLLDIV = 38;
    //_PLLPRE = 0;
    //_PLLPOST = 0;
    
    //CLKDIVbits.FRCDIV = 1; // 8MHz
    
    
    RPOR6bits.RP87R = 0b110001;
    REFOCON = 0x8300;
    
    /* Initialize digital pins and I/O direction */
    InitAnalogFunctionality();
    InitIO();
    
    /* Initialize peripherals */
    
    InitPWM();
    InitSPI();
    InitUART();
    InitTimers();
    InitLCD();
    ///
}

void ConfigureOscillator(void)
{

#if 0

        // Disable Watch Dog Timer
        RCONbits.SWDTEN = 0;

        // When clock switch occurs switch to Prim Osc (HS, XT, EC)with PLL 
        __builtin_write_OSCCONH(0x03);  // Set OSCCONH for clock switch 
        __builtin_write_OSCCONL(0x01);  // Start clock switching 
        while(OSCCONbits.COSC != 0b011);

        // Wait for Clock switch to occur 
        // Wait for PLL to lock, if PLL is used 
        // while(OSCCONbits.LOCK != 1); 

#endif
        
}

void InitLCD(void)
{    
    LATDbits.LATD5 =  0; //Contrast
    PMD3bits.RTCCMD = 1; //High disables RTCC module on port RD8    
    
    //prep LCD
    LCDWrite(CLEAR,0,0);
    LCDWrite(RET_HOME,0,0);
    LCDWrite(CONFIG,0,0);
    LCDWrite(TWOLINE,0,0);
}

void InitAnalogFunctionality(void)
{
    //---------- Clear Analog Functionality ---------- 
    
    //GPS
    ANSELEbits.ANSE1 = 0; //clear analog functionality of RE1 //pin 61 (GPS TX / Micro RX)
    ANSELEbits.ANSE2= 0; //clear analog functionality of RE2 //pin 62 (GPS RX / Micro TX)
    
    //COMPASS
    ANSELEbits.ANSE3 = 0; //clear analog functionality of RE3 //pin 63 
    ANSELEbits.ANSE4= 0; //clear analog functionality of RE4 //pin 64 
    
    //SENSORS
    ANSELBbits.ANSB5 = 0; //clear analog functionality of RB5 //pin 11 //TODO clear interrupt functionality
    ANSELBbits.ANSB4 = 0; //clear analog functionality of RB4 //pin 12 //TODO clear interrupt functionality
    ANSELBbits.ANSB3 = 0; //clear analog functionality of RB3 //pin 13
    ANSELBbits.ANSB2 = 0; //clear analog functionality of RB2 //pin 14
    ANSELBbits.ANSB1 = 0; //clear analog functionality of RB1 //pin 15
    //pin 16 (Trigger) ? 
    
    //FLIGHT CONTROLLER
    //no analog functionality on pins
    
    //SDCARD
    ANSELEbits.ANSE5 = 0; //clear analog functionality of RE5 //pin 1 
    ANSELEbits.ANSE6 = 0; //clear analog functionality of RE6 //pin 2 
    ANSELEbits.ANSE7 = 0; //clear analog functionality of RE7 //pin 3 
    ANSELGbits.ANSG6 = 0; //clear analog functionality of RG6 //pin 4 
    ANSELGbits.ANSG7 = 0; //clear analog functionality of RG7 //pin 5
    
    //CAMERA
    ANSELBbits.ANSB15 = 0; //clear analog functionality of RB15 //pin 30
    // pin 31 should already be digital and not need configured
    
    //BATTERY MONITOR 
    //already digital pins
    
    //PUSHBUTTON
    ANSELGbits.ANSG9 = 0; //clear analog functionality of RG9 //pin 8
    
    //LEDS
    ANSELBbits.ANSB12 = 0; //clear analog functionality of RB12 //pin 27 //heartbeat
    ANSELBbits.ANSB13 = 0; //clear analog functionality of RB13 //pin 28
    ANSELBbits.ANSB14 = 0; //clear analog functionality of RB14 //pin 29
    //TODO: pin 32 is already digital?
    //ANSELFbits.ANSF5 = 0;
    
    //LCD SCREEN
    //R/W = D4
    //RS = C14
    //E = C13
    //Contrast = D5
    //[DB7:DB0] = {D9,D8,D10,D1,D11,D2,D0,D3}
    
    ANSELCbits.ANSC13 = 0;//clear analog functionality of RC13 //pin 47
    ANSELCbits.ANSC14 = 0; //clear analog functionality of RC14 //pin 48
    IEC0bits.INT0IE = 0; //disables external interrupt of RD0 (pin 46)
    CNENDbits.CNIED0 = 0; //disable input detection interrupt
    CNENDbits.CNIED1 = 0; //disable input detection interrupt
    CNENDbits.CNIED2 = 0; //disable input detection interrupt
    CNENDbits.CNIED3 = 0; //disable input detection interrupt
    CNENDbits.CNIED4 = 0; //disable input detection interrupt
    CNENDbits.CNIED5 = 0; //disable input detection interrupt
    CNENDbits.CNIED6 = 0; //disable input detection interrupt
    CNENDbits.CNIED7 = 0; //disable input detection interrupt
    CNENDbits.CNIED8 = 0; //disable input detection interrupt
    CNENDbits.CNIED9 = 0; //disable input detection interrupt
    CNENDbits.CNIED10 = 0; //disable input detection interrupt
    CNENDbits.CNIED11 = 0; //disable input detection interrupt
   
    ODCDbits.ODCD0 = 0; //not open drain
    ODCDbits.ODCD1 = 0; //not open drain
    ODCDbits.ODCD2 = 0; //not open drain
    ODCDbits.ODCD3 = 0; //not open drain
    ODCDbits.ODCD4 = 0; //not open drain
    ODCDbits.ODCD5 = 0; //not open drain
    ODCDbits.ODCD8 = 0; //not open drain
    ODCDbits.ODCD9 = 0; //not open drain
    ODCDbits.ODCD10 = 0; //not open drain
    ODCDbits.ODCD11 = 0; //not open drain    
    
    ANSELBbits.ANSB6 = 0; //clear analog functionality of RB6 //pin 17
    ANSELBbits.ANSB7 = 0; //clear analog functionality of RB7 //pin 28
    
}

void InitIO(void)
{
    //---------- Set Port Direction ----------
    // 1 = input
    // 0 = output
    
    //GPS
    //TRISE = 0b0000000000001010; //set RE1, RE3 as inputs
    TRISEbits.TRISE1 = 1; //set RE1 as input // pin 61 (GPS TX / Micro RX)
    TRISEbits.TRISE2 = 0; //set RE2 as output // pin 62 (GPS RX / Micro TX)
    
    //COMPASS
    TRISEbits.TRISE3 = 1; //set RE3 as input // pin 63 (SDA)
    TRISEbits.TRISE4 = 0; //set RE4 as output // pin 64 (SCL)
    
    //SENSORS
    //TRISB = 0b0000000000111110; // set RB0 as digital output and RB1-5 as inputs
    TRISBbits.TRISB0 = 0; //set RB0 as output // pin 16
    TRISBbits.TRISB1 = 1; //set RB1 as input // pin 15
    TRISBbits.TRISB2 = 1; //set RB2 as input // pin 14
    TRISBbits.TRISB3 = 1; //set RB3 as input // pin 13
    TRISBbits.TRISB4 = 1; //set RB4 as input // pin 12
    TRISBbits.TRISB5 = 1; //set RB5 as input // pin 11
    
    //FLIGHT CONTROLLER
    //TRISD = 0xFFFF; // all outputs
    TRISEbits.TRISE0 = 0; //set RE0 as output // pin 60 (MODE) TODO: check label -- mode?
    TRISDbits.TRISD6 = 0; //set RD6 as output // pin 54 (PITCH)
    TRISDbits.TRISD7 = 0; //set RD7 as output // pin 55 (THROTTLE)
    TRISFbits.TRISF0 = 0; //set RF0 as output // pin 58 (YAW)
    TRISFbits.TRISF1 = 0; //set RF1 as output // pin 59 (ROLL)
    
    //SDCARD
    TRISEbits.TRISE7 = 1; //set RE7 as input //pin 3 (MISO)
    //TRISGbits.TRISG6 = 0; //set RG6 as output //pin 4 (SCK) TODO: check input or output
    //TRISGbits.TRISG7 = 0; //set RG7 as output //pin 5 (SS)  TODO: check input or output
    //TRISGbits.TRISG8 = 0; //set RG8 as output //pin 6 (MOSI)
    
    //CAMERA
    TRISBbits.TRISB15 = 1; //set RB15 as input //pin 30 (Camera TX / Micro RX)
    TRISFbits.TRISF4 = 0; //set RF4 as output //pin 31 (Camera RX / Micro TX)
    
    //BATTERY MONITOR
    TRISFbits.TRISF2 = 1; //set RF2 as input //pin 34 (SMBD) //TODO: check
    TRISFbits.TRISF3 = 0; //set RF3 as output //pin 33 (SMBC)
    
    //PUSHBUTTON
    //TRISGbits.TRISG9 = 1; //set RG9 as input //pin 8
    TRISG= 0x3C0;
    
    //LEDS
    TRISBbits.TRISB12 = 0; //set RB12 as output //pin 27 (yellow))
    TRISBbits.TRISB13 = 0; //set RB13 as output //pin 28
    TRISBbits.TRISB14 = 0; //set RB14 as output //pin 29
    TRISFbits.TRISF5 = 0; //set RF5 as output //pin 32
    
    //LCD SCREEN
    //R/W = D4
    //RS = C14
    //E = C13
    //Contrast = D5
    //[DB7:DB0] = {D9,D8,D10,D1,D11,D2,D0,D3}
    TRISDbits.TRISD5 = 0; //set RD5 as output //pin 53 (LCD pin 3 / Contrast Adjust)
    TRISDbits.TRISD4 = 0; //set RD4 as output //pin 52 (LCD: pin 5 / R/W)
    TRISDbits.TRISD3 = 0; //set RD3 as output //pin 51 (LCD: pin 7 / DB0)
    TRISDbits.TRISD2 = 0; //set RD2 as output //pin 50 (LCD: pin 9 / DB2)
    TRISDbits.TRISD1 = 0; //set RD1 as output //pin 49 (LCD: pin 11 / DB4)

    TRISCbits.TRISC14 = 0; //set RC14 as output //pin 48 (LCD: pin 4 / RS)
    TRISCbits.TRISC13 = 0; //set RC13 as output //pin 47 (LCD: pin 6 / E)
    TRISDbits.TRISD0 = 0; //set RD0 as output //pin 46 (LCD: pin 8 / DB1)
    TRISDbits.TRISD11 = 0; //set RD11 as output //pin 45 (LCD: pin 10 / DB3)
    TRISDbits.TRISD10 = 0; //set RD10 as output //pin 44 (LCD: pin 12 / DB5)
    TRISDbits.TRISD9 = 0; //set RD9 as output //pin 43 (LCD: pin 14 / DB7)
    TRISDbits.TRISD8 = 0; //set RD8 as output //pin 42 (LCD: pin 13 / DB6)
    
    
}

void InitTimers(void)
{   
    T1CONbits.TCS = 0; //Use internal clock for Timer1
    
    // Initialize Timer2 (PWM TIMER)
    T2CONbits.TON = 0; // Disable Timer
    T2CONbits.TCS = 0; // Select internal instruction cycle clock
    T2CONbits.TGATE = 0; // Disable Gated Timer mode
    T2CONbits.TCKPS = 0b00; // Select 1:1 Prescalar
    TMR2 = 0x00; // Clear timer register
    PR2 = 500; // Load the period value
    
    // Initialize Timer3 (SENSOR ECHO TIMER)
    T3CONbits.TON = 0; // Disable Timer
    T3CONbits.TCS = 0; // Select internal instruction cycle clock
    T3CONbits.TGATE = 0; // Disable Gated Timer mode
    T3CONbits.TCKPS = 0b01; //0b00 - Select 1:1 Prescalar //01
    TMR3 = 0x00; // Clear timer register
    PR3 = 100; // Load the period value //50
    
    // Initialize Timer4 (FLIGHT CONTROLLER ARM TIMER)
    T4CONbits.TON = 0; // Disable Timer
    T4CONbits.TCS = 0; // Select internal instruction cycle clock
    T4CONbits.TGATE = 0; // Disable Gated Timer mode
    T4CONbits.TCKPS = 0b11; //0b00 - Select 1:1 Prescalar
    TMR4 = 0x00; // Clear timer register
    PR4 = 30000; // Load the period value
    
    // Initialize Timer5 (SENSOR TRIGGER TIMER)
    T5CONbits.TON = 0; // Disable Timer
    T5CONbits.TCS = 0; // Select internal instruction cycle clock
    T5CONbits.TGATE = 0; // Disable Gated Timer mode
    T5CONbits.TCKPS = 0b01;//0b01; //0b00 - Select 1:1 Prescalar
    TMR5 = 0x00; // Clear timer register
    PR5 = 10000; //1000 // Load the period value
    IEC1bits.T5IE = 1; // Enable Timer5 interrupt
    
    // Enable Timers
    T2CONbits.TON = 1; // Start Timer2
    
    T5CONbits.TON = 1; // Start Timer5
    
    IFS0bits.T3IF = 0; // Clear Timer3 Interrupt Flag
    IEC0bits.T3IE = 1; // Enable Timer3 interrupt
}

void InitPWM(void)
{
    
    //PWMs: 6000 = neutral
    
    // ---------- PWM1 Initialization (ROLL) ----------
    RPOR7bits.RP97R = 0b010000; //Maps Output Compare 1 to output pin RP97 (pin 59)    
    OC1CON1 = 0;
    OC1CON2 = 0;
    OC1CON1bits.OCTSEL = 0; // This selects the peripheral clock as the clock input to the OC module
    OC1R = 6000; // ROLL
    OC1RS = 8000; // Determines the Period
    OC1CON2bits.SYNCSEL = 0x1F; // This selects the synchronization source as itself
    OC1CON1bits.OCM = 6; // This selects and starts the Edge Aligned PWM mode

    // ---------- PWM2 Initialization (PITCH) ----------
    RPOR3bits.RP70R = 0b010001; //Maps Output Compare 2 to output pin RP70 (pin 54)
    OC2CON1 = 0; 
    OC2CON2 = 0;
    OC2CON1bits.OCTSEL = 0; // This selects the peripheral clock as the clock input to the OC module
    OC2R = 6000; // PITCH
    OC2RS = 8000; // Determines the Period
    OC2CON2bits.SYNCSEL = 0x1F; // This selects the synchronization source as itself
    OC2CON1bits.OCM = 6; // This selects and starts the Edge Aligned PWM mode
    
    // ---------- PWM3 Initialization (THROTTLE) ----------
    RPOR3bits.RP71R = 0b010010; //Maps Output Compare 3 to output pin RP71 (pin 55)
    OC3CON1 = 0; 
    OC3CON2 = 0;
    OC3CON1bits.OCTSEL = 0; // This selects the peripheral clock as the clock input to the OC module
    OC3R = 4400; // THROTTLE
    OC3RS = 8000; // Determines the Period
    OC3CON2bits.SYNCSEL = 0x1F; // This selects the synchronization source as itself
    OC3CON1bits.OCM = 6; // This selects and starts the Edge Aligned PWM mode
    
    // ---------- PWM4 Initialization (YAW) ----------
    RPOR7bits.RP96R = 0b010011; //Maps Output Compare 4 to output pin RP96 (pin 58)
    OC4CON1 = 0; 
    OC4CON2 = 0;
    OC4CON1bits.OCTSEL = 0; // This selects the peripheral clock as the clock input to the OC module
    OC4R = 6000; // YAW 
    OC4RS = 8000; // Determines the Period
    OC4CON2bits.SYNCSEL = 0x1F; // This selects the synchronization source as itself
    OC4CON1bits.OCM = 6; // This selects and starts the Edge Aligned PWM mode
    
}

void InitSPI(void)
{
    // ---------- SPI1 Initialization Master Mode (SD CARD) ----------
    IFS0bits.SPI1IF = 0; // Clear the Interrupt flag
    IEC0bits.SPI1IE = 0; // Disable the interrupt
    // SPI1CON1 Register Settings
    SPI1CON1bits.DISSCK = 0; // Internal serial clock is enabled
    SPI1CON1bits.DISSDO = 0; // SDOx pin is controlled by the module
    SPI1CON1bits.MODE16 = 1; // Communication is word-wide (16 bits)
    SPI1CON1bits.MSTEN = 1; // Master mode enabled
    SPI1CON1bits.SMP = 0; // Input data is sampled at the middle of data output time
    SPI1CON1bits.CKE = 0; // Serial output data changes on transition from
    // Idle clock state to active clock state
    SPI1CON1bits.CKP = 0; // Idle state for clock is a low level;
    // active state is a high level
    SPI1STATbits.SPIEN = 1; // Enable SPI module
    // Interrupt Controller Settings
    IFS0bits.SPI1IF = 0; // Clear the Interrupt flag
    IEC0bits.SPI1IE = 1; // Enable the interrupt
    
    // Force First Word After Enabling SPI
    DMA0REQbits.FORCE=1;
    while (DMA0REQbits.FORCE == 1);
    IEC2bits.SPI2IE = 1; // Enable the interrupt
    
    // DMA0: TX
    /*unsigned int TxBufferA[16] __attribute__((space(xmemory)));
    unsigned int TxBufferB[16] __attribute__((space(xmemory)));
    IFS0bits.DMA0IF = 0;
    IEC0bits.DMA0IE = 1;
    //DMACS0 = 0; //TODO: what is this?
    DMA0CON = 0x2002;
    DMA0STAL = (unsigned int)&TxBufferA;
    DMA0STAH = (unsigned int)&TxBufferB;
    DMA0PAD = (volatile unsigned int) &SPI1BUF;
    DMA0CNT = 15;
    DMA0REQ = 0x000A;
    DMA0CONbits.CHEN = 1;*/
    
}

void InitUART(void)
{   
       
    // ---------- UART1 Initialization (Interfaces with GPS) ----------    
    RPINR18bits.U1RXR = 0b1010001; //Maps U1RX to RPI81 (pin 61)
    RPOR5bits.RP82R = 0b000001; // Maps U1TX to RP82  (pin 62)
    
    U1MODEbits.STSEL = 0; // 1-Stop bit
    U1MODEbits.PDSEL = 0; // No Parity, 8-Data bits
    U1MODEbits.ABAUD = 0; // Auto-Baud disabled
    U1MODEbits.BRGH = 0; // Standard-Speed mode
    U1BRG = 25; //BRGVAL1; // Baud Rate setting
    U1STAbits.URXISEL0 = 0; // Interrupt after one RX character is Received
    U1STAbits.URXISEL1 = 0;

    U1MODEbits.URXINV = 0; // Idle state is 1
    U1MODEbits.UARTEN = 1; // Enable UART
   
    U1STAbits.UTXEN = 1; // Enable UART TX
    IEC0bits.U1RXIE = 1; // Enable UART RX interrupt
    IFS0bits.U1RXIF = 0; //Reset interrupt flag

    // ---------- UART2 Initialization (Interfaces with Camera) ----------

    RPINR19bits.U2RXR = 0b0101111; //Maps U2RX to RPI47 (pin 30)
    RPOR9bits.RP100R = 0b1100100; // Maps U2TX to RP100  (pin 31)
    
    U2MODEbits.STSEL = 0; // 1-Stop bit
    U2MODEbits.PDSEL = 0; // No Parity, 8-Data bits
    U2MODEbits.ABAUD = 0; // Auto-Baud disabled
    U2MODEbits.BRGH = 0; // Standard-Speed mode
    U2BRG = 25;//BRGVAL2; // Baud Rate setting
    U2STAbits.URXISEL0 = 0; // Interrupt after one RX character is transmitted
    U2STAbits.URXISEL1 = 0;
    U2MODEbits.UARTEN = 1; // Enable UART
    U2STAbits.UTXEN = 1; // Enable UART TX
    //IEC0bits.U1RXIE = 1; // Enable UART RX interrupt
         
}