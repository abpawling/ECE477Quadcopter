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

void InitApp(void)
{
    /* Setup analog functionality and port direction */
    
    TRISB = 0b0000000000111110; // set 5 RB0 as digital output and RB1-5 as inputs
    TRISD = 0; //Trisiodhf
    
    /* Initialize peripherals */
    InitPWM();
    InitSPI();
    InitUART();
    InitTimers();
    ///
}

void InitTimers(void)
{   
    // Initialize Timer4 (FLIGHT CONTROLLER ARM TIMER)
    T4CONbits.TON = 0; // Disable Timer
    T4CONbits.TCS = 0; // Select internal instruction cycle clock
    T4CONbits.TGATE = 0; // Disable Gated Timer mode
    T4CONbits.TCKPS = 0b11; //0b00 - Select 1:1 Prescalar
    TMR4 = 0x00; // Clear timer register
    PR4 = 50000; // Load the period value
    
    // Initialize Timer3 (SENSOR ECHO TIMER)
    T3CONbits.TON = 0; // Disable Timer
    T3CONbits.TCS = 0; // Select internal instruction cycle clock
    T3CONbits.TGATE = 0; // Disable Gated Timer mode
    T3CONbits.TCKPS = 0b11; //0b00 - Select 1:1 Prescalar
    TMR3 = 0x00; // Clear timer register
    PR3 = 500; // Load the period value
    
    // Initialize Timer5 (SENSOR TRIGGER TIMER)
    T5CONbits.TON = 0; // Disable Timer
    T5CONbits.TCS = 0; // Select internal instruction cycle clock
    T5CONbits.TGATE = 0; // Disable Gated Timer mode
    T5CONbits.TCKPS = 0b01; //0b00 - Select 1:1 Prescalar
    TMR5 = 0x00; // Clear timer register
    PR5 = 10000; // Load the period value
    IEC1bits.T5IE = 1; // Enable Timer5 interrupt
    
    // Initialize Timer2 (PWM TIMER)
    T2CONbits.TON = 0; // Disable Timer
    T2CONbits.TCS = 0; // Select internal instruction cycle clock
    T2CONbits.TGATE = 0; // Disable Gated Timer mode
    T2CONbits.TCKPS = 0b00; // Select 1:1 Prescalar
    TMR2 = 0x00; // Clear timer register
    PR2 = 500; // Load the period value
    
    // Enable Timers
    T2CONbits.TON = 1; // Start Timer2
    
    T5CONbits.TON = 1; // Start Timer5
    
    IFS0bits.T3IF = 0; // Clear Timer3 Interrupt Flag
    IEC0bits.T3IE = 1; // Enable Timer3 interrupt
}

void InitPWM(void)
{
    

    // ---------- PWM1 Initialization (ROLL) ----------
    RPOR2bits.RP69R = 0b010000; //Maps Output Compare 1 to output pin RP69 (pin 53)    
    OC1CON1 = 0; // It is a good practice to clear off the control bits initially
    OC1CON2 = 0;
    OC1CON1bits.OCTSEL = 0; // This selects the peripheral clock as the clock input to the OC module
    OC1R = 4000; // ROLL This is just a typical number, user must calculate based on the waveform requirements and the system clock
    OC1RS = 8000; // Determines the Period
    OC1CON2bits.SYNCSEL = 0x1F; // This selects the synchronization source as itself
    OC1CON1bits.OCM = 6; // This selects and starts the Edge Aligned PWM mode

    // ---------- PWM2 Initialization (PITCH)----------
    RPOR3bits.RP70R = 0b010001; //Maps Output Compare 2 to output pin RP70 (pin 54)
    OC2CON1 = 0; // It is a good practice to clear off the control bits initially
    OC2CON2 = 0;
    OC2CON1bits.OCTSEL = 0; // This selects the peripheral clock as the clock input to the OC module
    OC2R = 4000; // PITCH This is just a typical number, user must calculate based on the waveform requirements and the system clock
    OC2RS = 8000; // Determines the Period
    OC2CON2bits.SYNCSEL = 0x1F; // This selects the synchronization source as itself
    OC2CON1bits.OCM = 6; // This selects and starts the Edge Aligned PWM mode
    
    // ---------- PWM3 Initialization THROTTLE ----------
    RPOR3bits.RP71R = 0b010010; //Maps Output Compare 3 to output pin RP71 (pin 55)
    OC3CON1 = 0; // It is a good practice to clear off the control bits initially
    OC3CON2 = 0;
    OC3CON1bits.OCTSEL = 0; // This selects the peripheral clock as the clock input to the OC module
    OC3R = 4000; // THROTTLE This is just a typical number, user must calculate based on the waveform requirements and the system clock
    OC3RS = 8000; // Determines the Period
    OC3CON2bits.SYNCSEL = 0x1F; // This selects the synchronization source as itself
    OC3CON1bits.OCM = 6; // This selects and starts the Edge Aligned PWM mode
    
    // ---------- PWM4 Initilization (YAW) ----------
    RPOR7bits.RP96R = 0b010011; //Maps Output Compare 4 to output pin RP96 (pin 58)
    OC4CON1 = 0; // It is a good practice to clear off the control bits initially
    OC4CON2 = 0;
    OC4CON1bits.OCTSEL = 0; // This selects the peripheral clock as the clock input to the OC module
    OC4R = 4000; // YAW This is just a typical number, user must calculate based on the waveform requirements and the system clock
    OC4RS = 8000; // Determines the Period
    OC4CON2bits.SYNCSEL = 0x1F; // This selects the synchronization source as itself
    OC4CON1bits.OCM = 6; // This selects and starts the Edge Aligned PWM mode
    
    // ---------- PWM5 Initialization ----------
    // ---------- PWM6 Initialization ----------
}

void InitSPI(void)
{
    // ---------- SPI1 Initialization (For SD Card) ----------
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
    
    // ---------- SPI2 Initialization ----------
    // ---------- SPI3 Initialization ----------
    // ---------- SPI4 Initialization ----------
}

void InitUART(void)
{
    
    // ---------- Declarations ----------
    #define FP 40000000
    #define BAUDRATE 9600
    #define BRGVAL ((FP/BAUDRATE)/16)-1

    TRISEbits.TRISE3 = 1; //input
    TRISEbits.TRISE4 = 0; //output
    
    RPINR18bits.U1RXR = 0b1010011;//Maps U1RX to RPI83
    
    RPOR5bits.RP84R = 0b000001;// Maps U1TX to RP84    
    
    // ---------- UART1 Initialization (Interfaces with GPS) ----------
    U1MODEbits.STSEL = 0; // 1-Stop bit
    U1MODEbits.PDSEL = 0; // No Parity, 8-Data bits
    U1MODEbits.ABAUD = 0; // Auto-Baud disabled
    U1MODEbits.BRGH = 0; // Standard-Speed mode
    U1BRG = BRGVAL; // Baud Rate setting for 9600
    U1STAbits.URXISEL0 = 0; // Interrupt after one RX character is transmitted
    U1STAbits.URXISEL1 = 0;
    IEC0bits.U1RXIE = 1; // Enable UART RX interrupt
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART TX

    // ---------- UART2 Initialization (Interfaces with Camera) ----------
    U2MODEbits.STSEL = 0; // 1-Stop bit
    U2MODEbits.PDSEL = 0; // No Parity, 8-Data bits
    U2MODEbits.ABAUD = 0; // Auto-Baud disabled
    U2MODEbits.BRGH = 0; // Standard-Speed mode
    U2BRG = BRGVAL; // Baud Rate setting for 9600
    U2STAbits.URXISEL0 = 0; // Interrupt after one RX character is transmitted
    U2STAbits.URXISEL1 = 0;
    IEC0bits.U1RXIE = 1; // Enable UART RX interrupt
    U2MODEbits.UARTEN = 1; // Enable UART
    U2STAbits.UTXEN = 1; // Enable UART TX
         
}