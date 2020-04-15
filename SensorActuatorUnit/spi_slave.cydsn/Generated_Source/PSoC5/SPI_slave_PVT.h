/*******************************************************************************
* File Name: .h
* Version 2.70
*
* Description:
*  This private header file contains internal definitions for the SPIS
*  component. Do not use these definitions directly in your application.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIS_PVT_SPI_slave_H)
#define CY_SPIS_PVT_SPI_slave_H

#include "SPI_slave.h"


/**********************************
*   Functions with external linkage
**********************************/


/**********************************
*   Variables with external linkage
**********************************/
extern volatile uint8 SPI_slave_swStatusTx;
extern volatile uint8 SPI_slave_swStatusRx;

#if (SPI_slave_RX_SOFTWARE_BUF_ENABLED)

    extern volatile uint8 SPI_slave_rxBuffer[SPI_slave_RX_BUFFER_SIZE];
    extern volatile uint8 SPI_slave_rxBufferRead;
    extern volatile uint8 SPI_slave_rxBufferWrite;
    extern volatile uint8 SPI_slave_rxBufferFull;

#endif /* SPI_slave_RX_SOFTWARE_BUF_ENABLED */

#if (SPI_slave_TX_SOFTWARE_BUF_ENABLED)

    extern volatile uint8 SPI_slave_txBuffer[SPI_slave_TX_BUFFER_SIZE];
    extern volatile uint8 SPI_slave_txBufferRead;
    extern volatile uint8 SPI_slave_txBufferWrite;
    extern volatile uint8 SPI_slave_txBufferFull;

#endif /* SPI_slave_TX_SOFTWARE_BUF_ENABLED */

#endif /* CY_SPIS_PVT_SPI_slave_H */


/* [] END OF FILE */
