//Author: Jonathan Hartvigsen Juncker
/** 
*@file wheelSensor.h
*@brief Indeholder Funktions implementeringer til wheel revolution sensor
*
*Indeholder implementeringer af funktionerne fra wheelSensor.h
*
*@author Jonathan Hartvigsen Juncker
*@bug Ingen kendte bugs.
*/
#include "wheelSensor.h"

void initWheelSensor()
{
    isr_wheel_tick_StartEx(isr_wheel_tick_Handler);
    
    WheelTickTimer_Start();
    
    Timer_Isr_BikeIsStopping_StartEx(Timer_Isr_BikeIsStopping_handler);
    
}

double calcDistance(int wheelRevolutions, double wheelCirc)
   {
        double dist = wheelRevolutions * wheelCirc; 
        
        return dist;
   } 
    
double calcSpeed(double time_ms, double dist)
    {
        double time_temp = time_ms/3600000;
        double  speed = dist/time_temp;
    
        return speed;    
    }    

double WheelRadiusToMetres(uint8 userInputInCentimeters)
    {
        double wheelRadiusInMeters = (double)userInputInCentimeters/100;
    
        return wheelRadiusInMeters;
    }

double calcWheelCirc(double radius)
    {
        double wheelCirc = (radius * 3.14 * 2)/1000;
    
        return wheelCirc;
    }

    void setSpeedToZero(uint8* speed)
    {
        *speed = 0;
    }

    void resetSpeedTimer()
    {
        WheelTickTimer_WriteCounter(3000);
    }
    
    
/* [] END OF FILE */
