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

void genWave(int freq)
{
    double count=(double)freq/100;
    while(1)
    {   
        led2=1;
        for (float i = 1.0f; i > 0.0f; i -= count) 
        { 
            aout = i;
            ThisThread::sleep_for(1ms);
        }
    }
}

int main()
{
    int enable=0,index=1;
    uLCD.printf("\nSelection:\n"); //Default Green on black text
    uLCD.printf("\n10Hz <--\n");
    uLCD.printf("\n20Hz\n");
    uLCD.printf("\n30Hz\n");
    
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
                    uLCD.printf("\n10Hz <--\n");
                    uLCD.printf("\n20Hz\n");
                    uLCD.printf("\n30Hz\n");
                    enable=0;
                    break;
                case 2:
                    uLCD.cls();
                    uLCD.printf("\nSelection:\n"); //Default Green on black text
                    uLCD.printf("\n10Hz\n");
                    uLCD.printf("\n20Hz <--\n");
                    uLCD.printf("\n30Hz\n");
                    enable=0;
                    break;
                case 3:
                    uLCD.cls();
                    uLCD.printf("\nSelection:\n"); //Default Green on black text
                    uLCD.printf("\n10Hz\n");
                    uLCD.printf("\n20Hz\n");
                    uLCD.printf("\n30Hz <--\n");
                    enable=0;
                    break;
            }
        }
        else {
            continue;
        }
    }
    genWave(index);
    return 0;
}