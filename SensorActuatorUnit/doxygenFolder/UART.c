//Author: Kristian Lau Jespersen, Jonathan Hartvigsen Juncker
/** 
*@file UART.c
*@brief funktions implementeringer til UART
*
*Indeholder implementeringer af funktionerne fra UART.h
*
*@author Kristian Lau Jespersen
*@author Jonathan Hartvigsen Juncker
*@bug Ingen kendte bugs.
*/
#include "UART.h"


void initUART()
{
    UART_1_Start();    //runs enable() and init() of the API 
    UART_rx_interrupt_StartEx(UART_rx_interrupt_handler);
    UART_1_PutString("UART ready");
}

/* [] END OF FILE */
