//Author: Kristian Lau Jespersen, Jonathan Hartvigsen Juncker
/** 
*@file SPI.h
*@brief Funktions og interrupt prototyper til SPI kommunikation
*
*Indeholder funktions prototyperne til SPI.c
*
*@author Kristian Lau Jespersen
*@author Jonathan Hartvigsen Juncker
*@bug Ingen kendte bugs.
*/
#include "project.h"
CY_ISR_PROTO(UART_rx_interrupt_handler);   

/**@brief Init funktion til UART
*Initierer UART ved at ved hjælp af UART_Start() API funktionen, og initierering interrupt handlers.
*/
void initUART();

/* [] END OF FILE */
