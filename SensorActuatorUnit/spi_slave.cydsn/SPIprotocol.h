//Author: Kristian Lau Jespersen
/** 
*@file SPIprotocol.h
*@brief Funktions prototyper til håndtering af SPI-protokol
*
*Indeholder funktions prototyperne til SPIprotocol.c
*
*@author Kristian Lau Jespersen
*@bug Ingen kendte bugs.
*/
#pragma once
#include "project.h"
#include "EDBikeProtocol.h"

/*========================SPI SPECIFIC FUNCTIONALITY==========================*/
/****************************function prototypes*******************************/

/**@brief Funktion til at uddrage information fra en buffer
*Henter speed og distance fra rx bufferen.
*
*@param speed
*
*@param distance
*
*@param buffer
*/
void extractFromBuffer(uint8_t* speed, uint8_t* distance, uint8_t* buffer);

/**@brief Funktion til check af paritets bit.
*Checker tx/rx buffere for paritets bit
*
*@param buffer
*
*@param lengthOfBuffer
*
*@return 1 eller 0 alt efter om der er en parity error.
*/
uint8_t errorCheckWithOddParity(uint8_t* buffer, uint8_t lengthOfBuffer);

/**@brief Funktion til kreering af paritets bits 
*Laver paritet bits til en tx/rx buffer.
*
*@param buffer
*
*@param lengthOfBuffer
*
*/
void createParityBits(uint8_t* buffer, uint8_t lengthOfBuffer);


/************************Enums for indexing SPI buffers************************/
enum data_transmission_indexes
{
    MESSAGE_TYPE_ID_INDEX   = 0,
    SPEED_INDEX             = 1,
    DISTANCE_INDEX          = 2,
    ERROR_CHECK_INDEX       = 3
};

enum event_transmission_indexes
{
    //MESSAGE_TYPE_ID_INDEX = 0,
    FIRST_EVENT_INDEX       = 1,
    SECOND_EVENT_INDEX      = 2,
    //ERROR_CHECK_INDEX     = 3
};

enum SPItransmissionIdentifiers
{
    LIVE_DATA_TRANSMISSION          = 100,  //ASCII d
    EVENT_TRANSMISSION_TO_MASTER    = 101,  //ASCII e
    EVENT_TRANSMISSION_FROM_MASTER  = 69    //ASCII E 
};



/* [] END OF FILE */
