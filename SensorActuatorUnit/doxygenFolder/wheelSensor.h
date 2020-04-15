//Author: Jonathan Hartvigsen Juncker
/** 
*@file wheelSensor.h
*@brief Funktions og interrupt prototyper til Wheel revolution sensor
*
*Indeholder prototyperne til interrupt handlers som relaterer til SPI
*og funktions prototyperne til wheelSensor.c
*
*@author Jonathan Hartvigsen Juncker
*@bug Ingen kendte bugs.
*/
#include <project.h>
#include <math.h> 
#include <stdio.h>
#include <stdlib.h>

CY_ISR_PROTO(isr_wheel_tick_Handler);
CY_ISR_PROTO(Timer_Isr_BikeIsStopping_handler);

/**@brief Init funktion til WheelSensor
*Initierer wheelSensor ved at ved hjælp af wheelTickTimer_Start() API funktionen, og initierering interrupt handlers.
*/
void initWheelSensor();

/**@brief Funktion til ændring af radius i cm til radius i m
*Når funktionen modtager en radius i cm ændre den det til m, så radiussen kan bruges
*til udregning af hjulets omkreds.
*
*@param radius radius i cm.
*
*@return radius radius i m.
*/
double WheelRadiusToMetres(uint8);    

/**@brief Funktion til udregning af hjulets omkreds
*Når funktionen modtager en radius i m. udregner den hjulets omkreds i km, så det kan bruges
*til udregning af hastighed og distance kørt.
*
*@param radius radius i m.
*
*@return hjulets omkreds returnerer hjulets omkreds i km. 
*/
double calcWheelCirc(double);

/**@brief Funktion til udregning af distance kørt.
*Funktionen calcDistance(), indeholder funktionaliteten til distanceberegninger. 
*Til dette anvendes parameteren wheelCircumference. calcDistance() multiplicerer antal omdrejninger detekteret med omkredsen af hjulet,
*opbevaret i variablen wheelCircumference. calcDistance() returnerer distanceværdien i enheden km 
*
*@param Wheelticks Antallet af omdrejninger som hjulet har lavet.
*
*@param wheelCircumference Hjulets omkreds i km.
*
*@return Distance Antal km cyklen har kørt
*/
double calcDistance(int, double);

/**@brief Funktion til udregning af hastighed.
*Til beregning af hastigheden tages der udgangspunkt i hjulets omkreds samt tiden siden sidste gang,
*der blev foretaget en omdrejning af hjulet
*
*@param Time Tiden siden sidste hjul omdrejning
*
*@param wheelCircumference hjulets omkreds i km.
*
*@return Speed returnerer en Hhastighed i km/t
*/
double calcSpeed(double counter_value, double circumference);

/**@brief Funktion til at sætte hastigheden til 0.
*Sætter hastigheden til 0, efter 3 sekunder ved hjælp af en timer.
*
*@param uint8* speed
*
*@return Speed returnerer en hastighed på 0 km/t
*/
void setSpeedToZero(uint8*);

/**@brief Funktion til reset af WheelTickTimer
*Skriver til timerens counter, for at reset den.
*
*/
void resetSpeedTimer();
    
/* [] END OF FILE */
