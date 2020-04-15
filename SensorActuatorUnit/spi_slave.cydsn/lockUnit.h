//Author: Jonathan Hartvigsen Juncker, Mortada Ismail
/** 
*@file lockUnit.h
*@brief Funktions og interrupt prototyper til låsen
*
*Indeholder prototyperne til interrupt handlers som relaterer til låsen
*og funktions prototyperne til lockUnit.c
*
*@author Jonathan Hartvigsen Juncker
*@author Mortada Ismail
*@bug Ingen kendte bugs.
*/

#include <stdio.h>
#include "project.h"

extern enum bikeState STATE;

CY_ISR_PROTO(isr_bikelock);

/**@brief Init funktion til låsen.
*Initiere interrupt rutinerne, som er forbundet med låsen. 
*/
void initLockUnit();

/**@brief Unlock funktion til låsen.
*Låser låsen op og tænder for motor timeren.
*/
void unlockBike();

/**@brief lock funktion til låsen.
*Låser låsen og tænder for motor timeren.
*/
void lockBike();

/**@brief Stop funktion til motor timeren.
*Stopper motor timeren.
*/
void stopLockTimer();


/* [] END OF FILE */
