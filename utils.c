#include "utils.h"
#include "p24EP512GP806.h"
//#include "p24EP512GU810.h"
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
void LCDWrite(char out, int rs, int rw) 
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
   //LCDWrite(CLEAR,0,0);
   //LCDWrite(line,0,0);
   
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

long parse(char* val, int tag)
{
    // tag == 1 : lat
    int temp;
    
    if (tag == 1) //latitude1
    {
        temp = ((val[0] - 48) * 1000) + ((val[1] - 48) * 100) + ((val[2] - 48) * 10) + ((val[3] - 48) * 1);
        //temp = ((val[0] - 48) * 10000000) + ((val[1] - 48) * 1000000) + ((val[2] - 48) * 100000) + ((val[3] - 48) * 10000) + ((val[5] - 48) * 1000) + ((val[6] - 48) * 100) + ((val[7] - 48) * 10) + ((val[8] - 48) * 1);
        return temp;
    }
    else if (tag == 2)
    {
        temp = ((val[5] - 48) * 1000) + ((val[6] - 48) * 100) + ((val[7] - 48) * 10) + ((val[8] - 48) * 1);
        return temp;
    }
    else if (tag == 3)
    {
        temp = ((val[0] - 48) * 10000) + ((val[1] - 48) * 1000) + ((val[2] - 48) * 100) + ((val[3] - 48) * 10) + ((val[4] - 48) * 1);
        return temp;
    }
    else if (tag == 4)
    {
        temp = ((val[6] - 48) * 100) + ((val[7] - 48) * 10) + ((val[8] - 48) * 1);
        return temp;
    }
    return temp;
}
 

