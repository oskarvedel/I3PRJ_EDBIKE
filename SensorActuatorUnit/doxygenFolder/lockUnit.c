//Author: Jonathan Hartvigsen Juncker, Mortada Ismail
/** 
*@file lockUnit.c
*@brief funktions implementeringer til låsen
*
*Indeholder implementeringer af funktionerne fra lockUnit.h
*
*@author Jonathan Hartvigsen Juncker
*@author Mortada Ismail
*@bug Ingen kendte bugs.
*/
#include "lockUnit.h"
#include "EDBikeProtocol.h"


void initLockUnit()
{
    isr_bikelock_StartEx(isr_bikelock);
}

void unlockBike()
{
   
     //UART_1_PutString("\r\nMotor Laases op\n");
     MotorLockTimer_Start();
     In_1_Write(0);
     In_2_Write(1);
     EA_Write(1); 

 
}

void lockBike()
{ 

        //UART_1_PutString("\r\nMotor Laases\n");
        MotorLockTimer_Start();
        In_1_Write(1);
        In_2_Write(0);
        EA_Write(1);
}

void stopLockTimer()
{
  MotorLockTimer_Stop();
}

/* [] END OF FILE */
