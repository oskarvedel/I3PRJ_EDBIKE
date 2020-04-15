//Author: Kristian Lau Jespersen
/** 
*@file SPI.h
*@brief Funktions og interrupt prototyper til SPI kommunikation
*
*Indeholder prototyperne til interrupt handlers som relaterer til SPI
*og funktions prototyperne til SPI.c
*
*@author Kristian Lau Jespersen
*@bug Ingen kendte bugs.
*/
#include "project.h"
#include <stdio.h>

#define maxMessageLength 4

CY_ISR_PROTO(slave_rx_interrupt_handler); 
CY_ISR_PROTO(slave_tx_buffer_empty_handler);


/***********************Prototypes************************/
/**@brief Init funktion til låsen.
*Initiere interrupt rutinerne som er forbundet med SPI, og tømmer FIFO'en og starter SPI komponenten. 
*/
void initSPI();

/**@brief Stop funktion til SPI komponenten.
*Slukker SPI Komponenten 
*/
void terminateSPI();

/**@brief Funktion til modtagelse af information fra SPI-Master.
*Læser fra rx bufferen. 
*
*@param rxBuffer bufferen hvori informationen som SPI masteren har sendt ligger.
*
*/
void receiveSPI(uint8* rxBuffer);

/**@brief Funktion til indlæsning af information til tx SPI-masteren
*Indlæser information til tx bufferen.
*
*@Param txBuffer bufferen hvor informationen som SPI slaven skal sende til SPI Masteren bliver lagt.
*
*@param index de index informationen skal indsættes i.
*
*
*@param data
*
*/
void loadToSpecificTxBufferIndex(uint8* txBuffer, uint8 index, uint8 data);

/**@brief Funktion der sørger for at lægge data klar i SPI-enhedens FIFO-kø
*Når transferIsReady() kaldes med variablen txBuffer som parameter, laves 5 kopier af indholdet i txBuffer,
*hvilke placeres i den 6 gange så lange buffer txCloneBuffer.
*
*@param txBuffer bufferen hvor informationen som SPI slaven skal sende til SPI Masteren bliver lagt.
*
*/
void transferIsReady(uint8* txBuffer);

/* [] END OF FILE */
