//Author: Kristian Lau Jespersen
/** 
*@file SPI.c
*@brief funktions implementeringer til SPI kommunikation
*
*Indeholder implementeringer af funktionerne fra SPI.h
*
*@author Kristian Lau Jespersen
*@bug Ingen kendte bugs.
*/
#include "SPI.h"

extern uint8 txCloneBuffer[(maxMessageLength*6)];


void initSPI()
{
    
    SPI_slave_Start();
    //interrupt pin is assigned the ISR function in parameter (see topDesign).
    slave_rx_interrupt_StartEx(slave_rx_interrupt_handler); 
    SPI_slave_ClearFIFO();
}

void terminateSPI()
{
    SPI_slave_Stop();
}

void receiveSPI(uint8* rxBuffer)
{
    size_t i=0;
    while (SPI_slave_GetRxBufferSize()!=0)
    {
        rxBuffer[i]=(uint8)SPI_slave_ReadRxData();
        i++;
    }
    
    SPI_slave_ClearRxBuffer();    
}

void loadToSpecificTxBufferIndex(uint8* txBuffer, uint8 index, uint8 data)
{
    //SPI_slave_ClearTxBuffer();
    txBuffer[index]=data;
}

void transferIsReady(uint8* txBuffer)
{
    
    
    SPI_slave_ClearTxBuffer();
    SPI_slave_ClearFIFO();
    
    //SPI_slave_PutArray(txBuffer,maxMessageLength);
   
    
    uint8 txBufferIndex=0;
    for (uint32_t i = 0; i < (maxMessageLength*6); i++)
    {
        txCloneBuffer[i]=txBuffer[txBufferIndex];
        txBufferIndex++;
        if (txBufferIndex>3)
        {
            txBufferIndex=0;
        }
    }
    
    SPI_slave_PutArray(txCloneBuffer,(maxMessageLength*6)); //Bytes to be returned to master on next transfer.
    
}

/* [] END OF FILE */