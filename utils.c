#include "utils.h"
#include "p24EP512GP806.h"
//#include "p24EP512GU810.h"
#include <stdbool.h>
#include <string.h>
/* ----- USAGE ----- 
    *      R/W = D4
    *      RS = C14
    *      E = C13
    *      Contrast = D5
    *      [DB7:DB0] = {D9,D8,D10,D1,D11,D2,D0,D3} 
    */

/* to write data: rs = 1, rw = 0
 * to write instruction: rs = 0, rw = 0
 */
void LCDWrite(char out, bool rs, bool rw) 
{   
    LATCbits.LATC14 = rs; //RS high
    LATDbits.LATD4 = rw; //R/W low
    
    wait();
    
    LATCbits.LATC13 = 1; //E high
    
    LATDbits.LATD3 =  out & 0b00000001; //0
    LATDbits.LATD0 =  (out >> 1) & 0b00000001; //1
    LATDbits.LATD2 =  (out >> 2) & 0b00000001; //2
    LATDbits.LATD11 = (out >> 3) & 0b00000001; //3
    LATDbits.LATD1 =  (out >> 4) & 0b00000001; //4
    LATDbits.LATD10 = (out >> 5) & 0b00000001; //5
    LATDbits.LATD8 =  (out >> 6) & 0b00000001; //6
    LATDbits.LATD9 =  (out >> 7) & 0b00000001; //7
    
    wait();
    
    LATCbits.LATC13 = 0; //E low
    
}

void printMsgToLCD(char * msg, char line)
{
   int i = 0;
   LCDWrite(line,0,0);
   while (msg[i] != '\0')
   {
     LCDWrite(msg[i],1,0);
     i++;
   }
}

void wait(void)
{
    int i;
    for (i = 0; i <= 4800; i++) {}
}

double parse(char* val, char* tag)
{
    
    if (strcmp(tag,"lat") || strcmp(tag,"long")) //latitude or longitude
    {
        return (val[0] * 100000) + (val[1] * 10000) + (val[2] * 1000) + (val[3] * 100) + (val[4] * 10) + (val[5]) + (val[6]/10) + (val[7]/100) + (val[8]/1000) + (val[9]/10000);
    }
    else if (strcmp(tag,"alt")) //altitude
    {
        return (val[0] * 100) + (val[1] * 10) + (val[2]) + (val[3]/10) + (val[4]/100);
    }
    else
    {
        return 0;
    }
}
 

