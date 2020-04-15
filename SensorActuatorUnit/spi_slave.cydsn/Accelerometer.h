//Author: Jonathan Hartvigsen Juncker, Frederik Runge-Dalager
/** 
*@file Accelerometer.h
*@brief Funktions og interrupt prototyper til accelerometeret.
*
*Indeholder prototyperne til interrupt handlers som relaterer til accelerometeret
*og funktions prototyperne til Accelerometer.c
*
*@author Jonathan Hartvigsen Juncker
*@author Frederik Runge-Dalager
*@bug Ingen kendte bugs.
*/
#include "project.h"

// Prototyper for interupt handlers
CY_ISR_PROTO(bike_is_idle_handler);
CY_ISR_PROTO(bike_is_moving_handler);
CY_ISR_PROTO(bike_stopped_handler);

/**@brief Init funktion til accelerometeret.
*  Initiere interrupt rutinerne, som er forbundet med accelerometeret 
*/
void init_accelerometer();

/**@brief Stopper accelerometerets timer
*
*/
void stopAccelerometerTimer();

/**@brief Starter accelerometerets timer
*
*/
void startAccelerometerTimer();

/**@brief resetter accelerometerets timer
*
*/
void resetAccelerometerTimer();
/* [] END OF FILE */
