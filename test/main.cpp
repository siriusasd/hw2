#include "mbed.h"
#include "uLCD_4DGL.h"

AnalogOut aout(PA_5);
 
DigitalOut led1(LED1);    // Configure LED1 pin as output
DigitalOut led2(LED2);
DigitalOut led3(LED3);

DigitalIn Up(D7); // Configure P1_14 pin as input
DigitalIn Down(D6);
DigitalIn Select(D5);
 
uLCD_4DGL uLCD(D1, D0, D2);

void genWave(double freq)
{
    while(1)
    {   
        for (float i = (double)3/3.3; i > 0.0f; i -= freq) 
        { 
            aout = i;
            wait_us(50);
        }
    }
}

int main()
{
    int enable=0,index=1;
    uLCD.printf("\nSelection:\n"); //Default Green on black text
    uLCD.printf("\n250Hz <--\n");
    uLCD.printf("\n500Hz\n");
    uLCD.printf("\n1000Hz\n");
    
    while(1) 
    {
        if(Up.read()==1&&Down.read()==0&&Select.read()==0) 
        {    
            enable=1;   
            if(index>1)
                index--;
            else
                index=3;
        } 
        else if(Up.read()==0&&Down.read()==1&&Select.read()==0) 
        {
            enable=1;   //<-----
            if(index<3)
                index++;
            else
                index=1;

        }
        else if(Up.read()==0&&Down.read()==0&&Select.read()==1) {
            //function
            break;
        }
        else {
            continue;
        }

        if(enable==1)
        {
            switch(index)
            {
                case 1:
                    uLCD.cls();
                    uLCD.printf("\nSelection:\n"); //Default Green on black text
                    uLCD.printf("\n250Hz <--\n");
                    uLCD.printf("\n500Hz\n");
                    uLCD.printf("\n1000Hz\n");
                    enable=0;
                    break;
                case 2:
                    uLCD.cls();
                    uLCD.printf("\nSelection:\n"); //Default Green on black text
                    uLCD.printf("\n250Hz\n");
                    uLCD.printf("\n500Hz <--\n");
                    uLCD.printf("\n1000Hz\n");
                    enable=0;
                    break;
                case 3:
                    uLCD.cls();
                    uLCD.printf("\nSelection:\n"); //Default Green on black text
                    uLCD.printf("\n250Hz\n");
                    uLCD.printf("\n500Hz\n");
                    uLCD.printf("\n1000Hz <--\n");
                    enable=0;
                    break;
            }
        }
        else {
            continue;
        }
    }
    switch(index)
    {
        case 1:
            genWave(0.015);
            break;
        case 2:
            genWave(0.03);
            break;
        case 3:
            genWave(0.06);
            break;
    }
    return 0;
}