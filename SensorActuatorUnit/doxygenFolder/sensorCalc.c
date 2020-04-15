/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "sensorCalc.h"



double calcDistance(int WR, double wheelSize)
   {
        double dist = (WR * wheelSize * 3.14 * 2)/1000; 
        
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
    
/* [] END OF FILE */
