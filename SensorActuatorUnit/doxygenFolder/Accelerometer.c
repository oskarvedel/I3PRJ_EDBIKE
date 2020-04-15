//Author: Jonathan Hartvigsen Juncker, Frederik Runge-Dalager
/** 
*@file Accelerometer.h
*@brief Funktions implementering til accelerometeret. 
*
*Indeholder implementeringer af funktionerne fra accelerometer.h
*
*@author Jonathan Hartvigsen Juncker
*@author Frederik Runge-Dalager
*@bug Ingen kendte bugs.
*/
#include "Accelerometer.h"

void init_accelerometer()
{
    isr_bike_is_idle_StartEx(bike_is_idle_handler);
    isr_bike_is_moving_StartEx(bike_is_moving_handler);
    isr_bike_stopped_StartEx(bike_stopped_handler);   
}

void stopAccelerometerTimer()
{
    //AccelerometerTimer_Stop();
    AccelerometerTimer_Sleep();
}

void startAccelerometerTimer()
{
    AccelerometerTimer_Start();
}

void resetAccelerometerTimer()
{
    AccelerometerTimer_WriteCounter(300000);
}

/* [] END OF FILE */
