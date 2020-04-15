//Author: Kristian Lau Jespersen
/** 
*@file SPIprotocol.c
*@brief funktions implementeringer til SPI kommunikation
*
*Indeholder implementeringer af funktionerne fra SPIprotocol.h
*
*@author Kristian Lau Jespersen
*@bug Ingen kendte bugs.
*/
#include "SPIprotocol.h"

void extractFromBuffer(uint8_t* speed, uint8_t* distance, uint8_t* buffer)
{
    *speed=buffer[SPEED_INDEX];
    *distance=buffer[DISTANCE_INDEX];
}


uint8_t errorCheckWithOddParity(uint8_t* buffer, uint8_t lengthOfBuffer)
{
    uint8_t parityBitsReceived = buffer[ERROR_CHECK_INDEX];

    for (uint8_t i = 0; i < (lengthOfBuffer-1); i++)
    {
        uint8_t numberOfOnes=0;
        uint8_t byteToBeChecked = buffer[i];
        uint8_t checkedByteHasOddNumberOfOnes = 0;
        uint8_t parityBitReceivedFromSender = 0;

        while(byteToBeChecked>0)
        {
            if(byteToBeChecked & 0b00000001)
            {
                numberOfOnes++;
            }
            byteToBeChecked = byteToBeChecked>>1;
        }

        if (numberOfOnes & 0b00000001)
        {
            checkedByteHasOddNumberOfOnes = 1;
        }

        //Extraction of parity bit from byte of parity bits.
        if ((parityBitsReceived & (1<<(7-i))))
        {
            parityBitReceivedFromSender = 1;
        }
        
        //if checked byte has odd number of ones, the corresponding parity bit is expected to be zero.
        if (checkedByteHasOddNumberOfOnes == parityBitReceivedFromSender)
        {
            return 0;
        }
    }
    return 1;
}

void createParityBits(uint8_t* buffer, uint8_t lengthOfBuffer)
{
    for (uint8_t i = 0; i < (lengthOfBuffer-1); i++)
    {

        uint8_t numberOfOnes=0;
        uint8_t byteToBeChecked = buffer[i];
        

         while(byteToBeChecked>0)
        {
            if(byteToBeChecked & 0b00000001)
            {
                numberOfOnes++;
            }
            byteToBeChecked = byteToBeChecked>>1;
        }

        //If number of ones in checked byte isn't odd, the corresponding parity bit is set to 1.
        if (!(numberOfOnes & 0b00000001))
        {
            buffer[ERROR_CHECK_INDEX]=(buffer[ERROR_CHECK_INDEX] | (1<<(7-i)));
        }
    }
}





/* [] END OF FILE */
