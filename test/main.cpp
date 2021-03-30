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

float ADCdata[150];
int counter=0,c=0;
int sample = 128;

void genWave(double freq)
{
    while(1)
    {   
        for (float i=(double)300/3.3; i > 0.0f; i -= freq) 
        { 
            aout = (double)i/100;
            counter++;      //count how many loops of for loop
            if(counter%4==0&&c<sample)
            {
                ADCdata[c++]=(double)i*3.3/100;
                printf("%f\r\n", (double)i*3.3/100);
            }
            ThisThread::sleep_for(250ms/sample);
            //wait_us(50);
        }
    }
}

int main()
{
    int enable=0,index=1;
    uLCD.printf("\nSelection:\n"); //Default Green on black text
    uLCD.printf("\n1Hz <--\n");
    uLCD.printf("\n20Hz\n");
    uLCD.printf("\n50Hz\n");
    
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
                    uLCD.printf("\n1Hz <--\n");
                    uLCD.printf("\n20Hz\n");
                    uLCD.printf("\n50Hz\n");
                    enable=0;
                    break;
                case 2:
                    uLCD.cls();
                    uLCD.printf("\nSelection:\n"); //Default Green on black text
                    uLCD.printf("\n1Hz\n");
                    uLCD.printf("\n20Hz <--\n");
                    uLCD.printf("\n50Hz\n");
                    enable=0;
                    break;
                case 3:
                    uLCD.cls();
                    uLCD.printf("\nSelection:\n"); //Default Green on black text
                    uLCD.printf("\n1Hz\n");
                    uLCD.printf("\n20Hz\n");
                    uLCD.printf("\n50Hz <--\n");
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
            genWave(0.1);
            break;
        case 2:
            genWave(1.7);
            break;
        case 3:
            genWave(4.5);
            break;
    }
    return 0;
}