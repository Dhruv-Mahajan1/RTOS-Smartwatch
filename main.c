#include "stm32f429xx.h"
void delay(int dd);

int main(void)
{
    RCC->AHB1ENR|=0x40;
    GPIOG->MODER |=0x14000000;
    GPIOG->ODR=0x6000;
    while(1)
    {
        GPIOG->ODR=0x6000;
        delay(1200);
        GPIOG->ODR=0x0000;
        delay(1200);
    }
}

void delay (int dd)
{
    int i;
    for (;dd>0;dd--)
    {
        for(i=0;i<3000;i++);
    }
}