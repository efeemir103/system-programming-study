#include "mbed.h"

Ticker timer_ticker;

DigitalOut led1(LED1);

void ticker_function(){
led1=!led1;
}


int main()
{
timer_ticker.attach_us(&ticker_function, 200000.0);  

while (true);
}
