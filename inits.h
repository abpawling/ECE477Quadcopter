/* 
 * File:   inits.h
 * Author: root
 *
 * Created on March 31, 2015, 9:34 PM
 */

void InitApp(void);        /* I/O and Peripheral Initialization */
void InitUART(void);       /*UART*/
void InitSPI(void);        /*SPI*/
void InitPWM(void);        /*PWM*/
void InitTimers(void);     /*Timers*/
void InitAnalogFunctionality(void); /*Set functionality for analog/digital pins*/
void InitIO(void); /*Set direction of pins*/

