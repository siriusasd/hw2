#include "mbed.h"
using namespace std::chrono;
 
DigitalOut led1(LED1);    // Configure LED1 pin as output
DigitalOut led2(LED2);
DigitalOut led3(LED3);

DigitalIn Up(D7); // Configure P1_14 pin as input
DigitalIn Down(D6);
DigitalIn Select(D5);
 
Timer debounce;

int main()
{
    int status=0, afterUp=0,afterDown=0,afterSelection=0;

    while(1) 
    {
        switch(status)
        {
            case 0:
                debounce.start();
                if(Up.read()==1&&Down.read()==0&&Select.read()==0&&duration_cast<milliseconds>(debounce.elapsed_time()).count() > 1000) {    //detect button
                    status=1;
                    debounce.reset();
                    break;
                } 
                else if(Up.read()==0&&Down.read()==1&&Select.read()==0&&duration_cast<milliseconds>(debounce.elapsed_time()).count() > 1000) {
                    status=2;
                    debounce.reset();
                    break;
                }
                else if(Up.read()==0&&Down.read()==0&&Select.read()==1&&duration_cast<milliseconds>(debounce.elapsed_time()).count() > 1000) {
                    status=3;
                    debounce.reset();
                    break;
                }
                else{
                    status=0;
                    break;
                }
            case 1:
                if(afterUp==0) {
                    led1=1;
                    afterUp=1;
                    status=0;
                    break;
                }
                else {
                    led1=0;
                    afterUp=0;
                    status=0;
                    break;
                }
            
            case 2:
                if(afterDown==0) {
                    led2=1;
                    afterDown=1;
                    status=0;
                    break;
                }
                else {
                    led2=0;
                    afterDown=0;
                    status=0;
                    break;
                }
            
            case 3:
                if(afterSelection==0) {
                    led3=1;
                    afterSelection=1;
                    status=0;
                    break;
                }
                else {
                    led3=0;
                    afterSelection=0;
                    status=0;
                    break;
                }
        }
        
    }
}
//if(Up.read()==1)
//{
//              //led1.write(Up.read());
//}
//        if(Down.read()==1)
//        {
//            led2.write(1);  //led2.write(Down.read());
//        }
//        if(Select.read()==1)
//        {
//            led3.write(1);  //led3.write(Select.read());
//        }