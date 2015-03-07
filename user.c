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
#include <stdbool.h>         /* For true/false definition */
#include <stdlib.h>


#include "user.h"            /* variables/params used by user.c */
#include "LinkedList.h"
//#include "p24EP512GP806.h"
#include "p24EP512GU810.h"

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */
//#include "p24EP512GP806.h"
#include "p24EP512GU810.h"
/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

/* TODO Initialize User Ports/Peripherals/Project here */

void InitApp(void)
{
    /* Setup analog functionality and port direction */

    /* Initialize peripherals */
    InitPWM();
    InitSPI();
    InitUART();
    ///
}

void InitPWM(void)
{
    TRISD = 0; //Trisiodhf

    // ---------- PWM1 Initilization ----------
    
    OC1CON1 = 0; // It is a good practice to clear off the control bits initially
    OC1CON2 = 0;
    OC1CON1bits.OCTSEL = 0; // This selects the peripheral clock as the clock input to the OC module
    OC1R = 1000; // This is just a typical number, user must calculate based on the waveform requirements and the system clock
    OC1RS = 2000; // Determines the Period
    OC1CON2bits.SYNCSEL = 0x1F; // This selects the synchronization source as itself
    OC1CON1bits.OCM = 6; // This selects and starts the Edge Aligned PWM mode

    // Initialize Timer2
    T2CONbits.TON = 0; // Disable Timer
    T2CONbits.TCS = 0; // Select internal instruction cycle clock
    T2CONbits.TGATE = 0; // Disable Gated Timer mode
    T2CONbits.TCKPS = 0b00; // Select 1:1 Prescaler
    TMR2 = 0x00; // Clear timer register
    PR2 = 500; // Load the period value'

    // Enable Timer
    T2CONbits.TON = 1; // Start Timer

    RPOR5bits.RP84R = 0b010000; //Maps Output Compare 1 to output pin RP84 (pin 100)

    // ---------- PWM2 Initilization ----------
    // ---------- PWM3 Initilization ----------
    // ---------- PWM4 Initilization ----------
    // ---------- PWM5 Initilization ----------
    // ---------- PWM6 Initilization ----------
}

void InitSPI(void)
{
    // ---------- SPI1 Initilization ----------
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
    
    // ---------- SPI2 Initilization ----------
    // ---------- SPI3 Initilization ----------
    // ---------- SPI4 Initilization ----------
}

void InitUART(void)
{
    // ---------- Declarations ----------
    #define FP 40000000
    #define BAUDRATE 9600
    #define BRGVAL ((FP/BAUDRATE)/16)-1
    //unsigned int i;

    // ---------- UART1 Initilization (Interfaces with camera) ----------
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

    // ---------- UART2 Initilization (Interfaces with GPS) ----------
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

waypoint * InitCollisionList(int coord)
{
    /*
    //declarations
    waypoint *head = NULL;
    waypoint *current;
    int i;

    #define COLLISION_COUNT 20
    static waypoint collisions [COLLISION_COUNT];

    //get current GPS waypoint
    //data = getCurrPos();

     */
    
}

 bool Navigate(int finalDest)
{
    //declarations
     //char orientation;

     
     /*if (orientation == "N" && finalDest.orientation != "N")
     {
        //rotate until facing orientation

     }*/

    //generate linked list for traversal
    /*for (i = 0;i <= 5;i++)
    {
        current = (waypoint* )malloc(sizeof(waypoint));
        current->coordinate = i//data + 4;
        current->next = head;
        head = current;
    }

    current = head;*/
    
 }
