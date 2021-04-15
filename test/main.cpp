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

float ADCdata[200];

int sample = 200;

Thread thread;
void print_thread()
{
   for(int i=0; i<sample; i++)
   {
       printf("%f\r\n", ADCdata[i]);
   }
}

void genWave(float freq)
{
    int counter=0, c=0, en=0;
    while(1)
    {   
        for (float i=100.0f; i > 0.0f; i -= freq)
        { 
            aout = (float)i/110.0f;
            counter++;      //count how many loops of for loop
            if(counter%5==0&&c<200)
            {
                ADCdata[c++]=(float)i*3.3/100;
                //printf("%f\r\n", (float)i*3.3/10);
            }
            ThisThread::sleep_for(200ms/sample);
            //wait_us(time);
        }
        if(en==0&&c==sample)
        {
            en=1;
            thread.start(print_thread);
        } 
    }
}

int main()
{
    int enable=0,index=1;
    uLCD.printf("\nSelection:\n"); //Default Green on black text
    uLCD.printf("\n1Hz <--\n");
    uLCD.printf("\n40Hz\n");
    uLCD.printf("\n50Hz\n");
    uLCD.printf("\n100Hz\n");

    while(1) 
    {
        if(Up.read()==1&&Down.read()==0&&Select.read()==0) 
        {    
            enable=1;   
            if(index>1)
                index--;
            else
                index=4;
        } 
        else if(Up.read()==0&&Down.read()==1&&Select.read()==0) 
        {
            enable=1;   //<-----
            if(index<4)
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
                    uLCD.printf("\n40Hz\n");
                    uLCD.printf("\n50Hz\n");
                    uLCD.printf("\n100Hz\n");
                    enable=0;
                    break;
                case 2:
                    uLCD.cls();
                    uLCD.printf("\nSelection:\n"); //Default Green on black text
                    uLCD.printf("\n1Hz\n");
                    uLCD.printf("\n40Hz <--\n");
                    uLCD.printf("\n50Hz\n");
                    uLCD.printf("\n100Hz\n");
                    enable=0;
                    break;
                case 3:
                    uLCD.cls();
                    uLCD.printf("\nSelection:\n"); //Default Green on black text
                    uLCD.printf("\n1Hz\n");
                    uLCD.printf("\n40Hz\n");
                    uLCD.printf("\n50Hz <--\n");
                    uLCD.printf("\n100Hz\n");
                    enable=0;
                    break;
                case 4:
                    uLCD.cls();
                    uLCD.printf("\nSelection:\n"); //Default Green on black text
                    uLCD.printf("\n1Hz\n");
                    uLCD.printf("\n40Hz\n");
                    uLCD.printf("\n50Hz\n");
                    uLCD.printf("\n100Hz <--\n");
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
            uLCD.printf("\n\n1Hz is selected!!\n");
            genWave(0.1);
            break;
        case 2:
            uLCD.printf("\n\n40Hz is selected!!\n");
            genWave(4);
            break;
        case 3:
            uLCD.printf("\n\n50Hz is selected!!\n");
            genWave(5);
            break;
        case 4:
            uLCD.printf("\n\n100Hz is selected!\n");
            genWave(8);
            break;
    }
    return 0;
}