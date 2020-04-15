/*******************************************************************************
* File Name: SPI_slave.c
* Version 2.70
*
* Description:
*  This file provides all API functionality of the SPI Slave component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPI_slave_PVT.h"

#if (SPI_slave_TX_SOFTWARE_BUF_ENABLED)

    volatile uint8 SPI_slave_txBuffer[SPI_slave_TX_BUFFER_SIZE];
    volatile uint8 SPI_slave_txBufferRead;
    volatile uint8 SPI_slave_txBufferWrite;
    volatile uint8 SPI_slave_txBufferFull;

#endif /* SPI_slave_TX_SOFTWARE_BUF_ENABLED*/

#if (SPI_slave_RX_SOFTWARE_BUF_ENABLED)

    volatile uint8 SPI_slave_rxBuffer[SPI_slave_RX_BUFFER_SIZE];
    volatile uint8 SPI_slave_rxBufferRead;
    volatile uint8 SPI_slave_rxBufferWrite;
    volatile uint8 SPI_slave_rxBufferFull;

#endif /* SPI_slave_RX_SOFTWARE_BUF_ENABLED */

uint8 SPI_slave_initVar = 0u;

volatile uint8 SPI_slave_swStatusTx;
volatile uint8 SPI_slave_swStatusRx;


/*******************************************************************************
* Function Name: SPI_slave_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default SPIS configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  When this function is called it initializes all of the necessary parameters
*  for execution. i.e. setting the initial interrupt mask, configuring the
*  interrupt service routine, configuring the bit-counter parameters and
*  clearing the FIFO and Status Register.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPI_slave_Init(void) 
{
    /*Initialize the Bit counter */
    SPI_slave_COUNTER_PERIOD_REG = SPI_slave_BITCTR_INIT;

    /* ISR initialization */
    #if(SPI_slave_INTERNAL_TX_INT_ENABLED)

        CyIntDisable(SPI_slave_TX_ISR_NUMBER);

        /* Set the ISR to point to the SPI_slave_isr Interrupt. */
        (void)CyIntSetVector(SPI_slave_TX_ISR_NUMBER, &SPI_slave_TX_ISR);

        /* Set the priority. */
        CyIntSetPriority(SPI_slave_TX_ISR_NUMBER, SPI_slave_TX_ISR_PRIORITY);

    #endif /* SPI_slave_INTERNAL_TX_INT_ENABLED */

    #if(SPI_slave_INTERNAL_RX_INT_ENABLED)

        CyIntDisable(SPI_slave_RX_ISR_NUMBER);

        /* Set the ISR to point to the SPI_slave_isr Interrupt. */
        (void)CyIntSetVector(SPI_slave_RX_ISR_NUMBER, &SPI_slave_RX_ISR);

        /* Set the priority. */
        CyIntSetPriority(SPI_slave_RX_ISR_NUMBER, SPI_slave_RX_ISR_PRIORITY);

    #endif /* SPI_slave_INTERNAL_RX_INT_ENABLED */

    /* Clear any stray data from the RX and TX FIFO */
    SPI_slave_ClearFIFO();

    #if(SPI_slave_RX_SOFTWARE_BUF_ENABLED)
        SPI_slave_rxBufferFull = 0u;
        SPI_slave_rxBufferRead = 0u;
        SPI_slave_rxBufferWrite = 0u;
    #endif /* SPI_slave_RX_SOFTWARE_BUF_ENABLED */

    #if(SPI_slave_TX_SOFTWARE_BUF_ENABLED)
        SPI_slave_txBufferFull = 0u;
        SPI_slave_txBufferRead = 0u;
        SPI_slave_txBufferWrite = 0u;
    #endif /* SPI_slave_TX_SOFTWARE_BUF_ENABLED */

    (void) SPI_slave_ReadTxStatus(); /* Clear any pending status bits */
    (void) SPI_slave_ReadRxStatus(); /* Clear any pending status bits */


    /* Configure the Initial interrupt mask */
    #if (SPI_slave_TX_SOFTWARE_BUF_ENABLED)
        SPI_slave_TX_STATUS_MASK_REG  = (SPI_slave_TX_INIT_INTERRUPTS_MASK &
                                                (uint8)~SPI_slave_STS_TX_FIFO_NOT_FULL);
    #else /* SPI_slave_TX_SOFTWARE_BUF_ENABLED */
        SPI_slave_TX_STATUS_MASK_REG  = SPI_slave_TX_INIT_INTERRUPTS_MASK;
    #endif /* SPI_slave_TX_SOFTWARE_BUF_ENABLED */

    SPI_slave_RX_STATUS_MASK_REG  = SPI_slave_RX_INIT_INTERRUPTS_MASK;
}


/*******************************************************************************
* Function Name: SPI_slave_Enable
********************************************************************************
*
* Summary:
*  Enable SPIS component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SPI_slave_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    SPI_slave_COUNTER_CONTROL_REG |= SPI_slave_CNTR_ENABLE;
    SPI_slave_TX_STATUS_ACTL_REG |= SPI_slave_INT_ENABLE;
    SPI_slave_RX_STATUS_ACTL_REG |= SPI_slave_INT_ENABLE;

    CyExitCriticalSection(enableInterrupts);

    #if(SPI_slave_INTERNAL_TX_INT_ENABLED)
        CyIntEnable(SPI_slave_TX_ISR_NUMBER);
    #endif /* SPI_slave_INTERNAL_TX_INT_ENABLED */

    #if(SPI_slave_INTERNAL_RX_INT_ENABLED)
        CyIntEnable(SPI_slave_RX_ISR_NUMBER);
    #endif /* SPI_slave_INTERNAL_RX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: SPI_slave_Start
********************************************************************************
*
* Summary:
*  Initialize and Enable the SPI Slave component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  SPI_slave_initVar - used to check initial configuration, modified on
*  first function call.
*
* Theory:
*  Enable the clock input to enable operation.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPI_slave_Start(void) 
{
    if(SPI_slave_initVar == 0u)
    {
        SPI_slave_Init();
        SPI_slave_initVar = 1u;
    }

    SPI_slave_Enable();
}


/*******************************************************************************
* Function Name: SPI_slave_Stop
********************************************************************************
*
* Summary:
*  Disable the SPI Slave component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal interrupt if one is used.
*
*******************************************************************************/
void SPI_slave_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    SPI_slave_TX_STATUS_ACTL_REG &= (uint8)~SPI_slave_INT_ENABLE;
    SPI_slave_RX_STATUS_ACTL_REG &= (uint8)~SPI_slave_INT_ENABLE;

    CyExitCriticalSection(enableInterrupts);

    #if(SPI_slave_INTERNAL_TX_INT_ENABLED)
        CyIntDisable(SPI_slave_TX_ISR_NUMBER);
    #endif /* SPI_slave_INTERNAL_TX_INT_ENABLED */

    #if(SPI_slave_INTERNAL_RX_INT_ENABLED)
        CyIntDisable(SPI_slave_RX_ISR_NUMBER);
    #endif /* SPI_slave_INTERNAL_RX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: SPI_slave_EnableTxInt
********************************************************************************
*
* Summary:
*  Enable internal Tx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal Tx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void SPI_slave_EnableTxInt(void) 
{
    #if(SPI_slave_INTERNAL_TX_INT_ENABLED)
        CyIntEnable(SPI_slave_TX_ISR_NUMBER);
    #endif /* SPI_slave_INTERNAL_TX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: SPI_slave_EnableRxInt
********************************************************************************
*
* Summary:
*  Enable internal Rx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal Rx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void SPI_slave_EnableRxInt(void) 
{
    #if(SPI_slave_INTERNAL_RX_INT_ENABLED)
        CyIntEnable(SPI_slave_RX_ISR_NUMBER);
    #endif /* SPI_slave_INTERNAL_RX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: SPI_slave_DisableTxInt
********************************************************************************
*
* Summary:
*  Disable internal Tx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal Tx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void SPI_slave_DisableTxInt(void) 
{
    #if(SPI_slave_INTERNAL_TX_INT_ENABLED)
        CyIntDisable(SPI_slave_TX_ISR_NUMBER);
    #endif /* SPI_slave_INTERNAL_TX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: SPI_slave_DisableRxInt
********************************************************************************
*
* Summary:
*  Disable internal Rx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal Rx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void SPI_slave_DisableRxInt(void) 
{
    #if(SPI_slave_INTERNAL_RX_INT_ENABLED)
        CyIntDisable(SPI_slave_RX_ISR_NUMBER);
    #endif /* SPI_slave_INTERNAL_RX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: SPI_slave_SetTxInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void SPI_slave_SetTxInterruptMode(uint8 intSrc) 
{
    SPI_slave_TX_STATUS_MASK_REG  = intSrc;
}


/*******************************************************************************
* Function Name: SPI_slave_SetRxInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void SPI_slave_SetRxInterruptMode(uint8 intSrc) 
{
    SPI_slave_RX_STATUS_MASK_REG  = intSrc;
}


/*******************************************************************************
* Function Name: SPI_slave_ReadTxStatus
********************************************************************************
*
* Summary:
*  Read the Tx status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the Tx status register.
*
* Global variables:
*  SPI_slave_swStatusTx - used to store in software status register,
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the Tx status register for error
*  detection and flow control.
*
* Side Effects:
*  Clear Tx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 SPI_slave_ReadTxStatus(void) 
{
    uint8 tmpStatus;

    #if (SPI_slave_TX_SOFTWARE_BUF_ENABLED)

        SPI_slave_DisableTxInt();

        tmpStatus = SPI_slave_GET_STATUS_TX(SPI_slave_swStatusTx);

        SPI_slave_swStatusTx = 0u;

        /* Enable Interrupts */
        SPI_slave_EnableTxInt();

    #else /* !SPI_slave_TX_SOFTWARE_BUF_ENABLED */

        tmpStatus = SPI_slave_TX_STATUS_REG;

    #endif /* SPI_slave_TX_SOFTWARE_BUF_ENABLED */

    return(tmpStatus);
}


/*******************************************************************************
* Function Name: SPI_slave_ReadRxStatus
********************************************************************************
*
* Summary:
*  Read the Rx status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the Rx status register.
*
* Global variables:
*  SPI_slave_swStatusRx - used to store in software Rx status register,
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the Rx status register for error
*  detection and flow control.
*
* Side Effects:
*  Clear Rx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 SPI_slave_ReadRxStatus(void) 
{
    uint8 tmpStatus;

    #if (SPI_slave_RX_SOFTWARE_BUF_ENABLED)

        SPI_slave_DisableRxInt();

        tmpStatus = SPI_slave_GET_STATUS_RX(SPI_slave_swStatusRx);

        SPI_slave_swStatusRx = 0u;

        /* Enable Interrupts */
        SPI_slave_EnableRxInt();

    #else /* !SPI_slave_RX_SOFTWARE_BUF_ENABLED */

        tmpStatus = SPI_slave_RX_STATUS_REG;

    #endif /* SPI_slave_RX_SOFTWARE_BUF_ENABLED */

    return(tmpStatus);
}


/*******************************************************************************
* Function Name: SPI_slave_WriteTxData
********************************************************************************
*
* Summary:
*  Write a byte of data to be sent across the SPI.
*
* Parameters:
*  txDataByte: The data value to send across the SPI.
*
* Return:
*  None.
*
* Global variables:
*  SPI_slave_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer, modified every function
*  call if TX Software Buffer is used.
*  SPI_slave_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer.
*  SPI_slave_txBuffer[SPI_slave_TX_BUFFER_SIZE] - used to store
*  data to sending, modified every function call if TX Software Buffer is used.
*
* Theory:
*  Allows the user to transmit any byte of data in a single transfer.
*
* Side Effects:
*  If this function is called again before the previous byte is finished then
*  the next byte will be appended to the transfer with no time between
*  the byte transfers. Clear Tx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPI_slave_WriteTxData(uint8 txData) 
{
    #if(SPI_slave_TX_SOFTWARE_BUF_ENABLED)

        uint8 tempStatus;
        uint8 tmpTxBufferRead;

        /* Block if buffer is full, so we don't overwrite. */
        do
        {
            tmpTxBufferRead = SPI_slave_txBufferRead;
            if (0u == tmpTxBufferRead)
            {
                tmpTxBufferRead = SPI_slave_TX_BUFFER_SIZE - 1u;
            }
            else
            {
                tmpTxBufferRead--;
            }

        }
        while(tmpTxBufferRead == SPI_slave_txBufferWrite);

        /* Disable Interrupt to protect variables that could change on interrupt. */
        SPI_slave_DisableTxInt();

        tempStatus = SPI_slave_GET_STATUS_TX(SPI_slave_swStatusTx);
        SPI_slave_swStatusTx = tempStatus;

        if((SPI_slave_txBufferRead == SPI_slave_txBufferWrite) &&
            (0u != (SPI_slave_swStatusTx & SPI_slave_STS_TX_FIFO_NOT_FULL)))
        {
            /* Put data element into the TX FIFO */
            CY_SET_REG8(SPI_slave_TXDATA_PTR, txData);
        }
        else
        {
            /* Put data element into the software buffer */
            SPI_slave_txBufferWrite++;
            if(SPI_slave_txBufferWrite >= SPI_slave_TX_BUFFER_SIZE)
            {
                SPI_slave_txBufferWrite = 0u;
            }

            if(SPI_slave_txBufferWrite == SPI_slave_txBufferRead)
            {
                SPI_slave_txBufferRead++;
                if(SPI_slave_txBufferRead >= SPI_slave_RX_BUFFER_SIZE)
                {
                    SPI_slave_txBufferRead = 0u;
                }
                SPI_slave_txBufferFull = 1u;
            }

            SPI_slave_txBuffer[SPI_slave_txBufferWrite] = txData;

            SPI_slave_TX_STATUS_MASK_REG |= SPI_slave_STS_TX_FIFO_NOT_FULL;
        }

        /* Enable Interrupt. */
        SPI_slave_EnableTxInt();

    #else /* !SPI_slave_TX_SOFTWARE_BUF_ENABLED */
        /* Wait until TX FIFO has a place */
        while(0u == (SPI_slave_TX_STATUS_REG & SPI_slave_STS_TX_FIFO_NOT_FULL))
        {
        }

        /* Put data element into the TX FIFO */
        CY_SET_REG8(SPI_slave_TXDATA_PTR, txData);
        
    #endif /* SPI_slave_TX_SOFTWARE_BUF_ENABLED */
}

#if(SPI_slave_MODE_USE_ZERO != 0u)

    /*******************************************************************************
    * Function Name: SPI_slave_WriteTxDataZero
    ********************************************************************************
    *
    * Summary:
    *  Write a byte zero of data to be sent across the SPI. This must be used in
    *  Mode 00 and 01 if the FIFO is empty and data is not being sent.
    *
    * Parameters:
    *  txDataByte: The data value to send across the SPI.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer. Clear
    *  status register of the component.
    *
    *******************************************************************************/
    void SPI_slave_WriteTxDataZero(uint8 txDataByte)
                                        
    {
        CY_SET_REG8(SPI_slave_TXDATA_ZERO_PTR, txDataByte);
    }

#endif /* (SPI_slave_MODE_USE_ZERO != 0u) */


/*******************************************************************************
* Function Name: SPI_slave_ReadRxData
********************************************************************************
*
* Summary:
*  Read the next byte of data received across the SPI.
*
* Parameters:
*  None.
*
* Return:
*  The next byte of data read from the FIFO.
*
* Global variables:
*  SPI_slave_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer.
*  SPI_slave_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified every function
*  call if RX Software Buffer is used.
*  SPI_slave_rxBuffer[SPI_slave_RX_BUFFER_SIZE] - used to store
*  received data.
*
* Theory:
*  Allows the user to read a byte of data received.
*
* Side Effects:
*  Will return invalid data if the FIFO is empty.  User should poll for FIFO
*  empty status before calling Read function.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 SPI_slave_ReadRxData(void) 
{
    uint8 rxData;

    #if(SPI_slave_RX_SOFTWARE_BUF_ENABLED)

        /* Disable Interrupt to protect variables that could change on interrupt. */
        SPI_slave_DisableRxInt();

        if(SPI_slave_rxBufferRead != SPI_slave_rxBufferWrite)
        {
            if(SPI_slave_rxBufferFull == 0u)
            {
                SPI_slave_rxBufferRead++;
                if(SPI_slave_rxBufferRead >= SPI_slave_RX_BUFFER_SIZE)
                {
                    SPI_slave_rxBufferRead = 0u;
                }
            }
            else
            {
                SPI_slave_rxBufferFull = 0u;
            }
        }

        rxData = SPI_slave_rxBuffer[SPI_slave_rxBufferRead];

        /* Enable Interrupt. */
        SPI_slave_EnableRxInt();

    #else /* !SPI_slave_RX_SOFTWARE_BUF_ENABLED */

        rxData = CY_GET_REG8(SPI_slave_RXDATA_PTR);

    #endif /* SPI_slave_RX_SOFTWARE_BUF_ENABLED */

    return (rxData);

}


/*******************************************************************************
* Function Name: SPI_slave_GetRxBufferSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes/words of data currently held in the RX buffer.
*  If RX Software Buffer not used then function return 0 if FIFO empty or 1 if
*  FIFO not empty. In another case function return size of RX Software Buffer.
*
* Parameters:
*  None.
*
* Return:
*  Integer count of the number of bytes/words in the RX buffer.
*
* Global variables:
*  SPI_slave_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer.
*  SPI_slave_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer.
*
* Theory:
*  Allows the user to find out how full the RX Buffer is.
*
*******************************************************************************/
uint8 SPI_slave_GetRxBufferSize(void) 
{
    uint8 size;

    #if(SPI_slave_RX_SOFTWARE_BUF_ENABLED)

        /* Disable Interrupt to protect variables that could change on interrupt. */
        SPI_slave_DisableRxInt();

        if(SPI_slave_rxBufferRead == SPI_slave_rxBufferWrite)
        {
            size = 0u; /* No data in RX buffer */
        }
        else if(SPI_slave_rxBufferRead < SPI_slave_rxBufferWrite)
        {
            size = (SPI_slave_rxBufferWrite - SPI_slave_rxBufferRead);
        }
        else
        {
            size = (SPI_slave_RX_BUFFER_SIZE - SPI_slave_rxBufferRead) + SPI_slave_rxBufferWrite;
        }

        /* Enable interrupt. */
        SPI_slave_EnableRxInt();

    #else /* !SPI_slave_RX_SOFTWARE_BUF_ENABLED*/

        /* We can only know if there is data in the fifo. */
        size = ((SPI_slave_RX_STATUS_REG & SPI_slave_STS_RX_FIFO_NOT_EMPTY) != 0u) ? 1u : 0u;

    #endif /* SPI_slave_RX_SOFTWARE_BUF_ENABLED */

    return (size);
}


/*******************************************************************************
* Function Name: SPI_slave_GetTxBufferSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes/words of data currently held in the TX buffer.
*  If TX Software Buffer not used then function return 0 - if FIFO empty, 1 - if
*  FIFO not full, 4 - if FIFO full. In another case function return size of TX
*  Software Buffer.
*
* Parameters:
*  None.
*
* Return:
*  Integer count of the number of bytes/words in the TX buffer.
*
* Global variables:
*  SPI_slave_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  SPI_slave_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer.
*
* Theory:
*  Allows the user to find out how full the TX Buffer is.
*
* Side Effects:
*  Clear status register of the component.
*
*******************************************************************************/
uint8  SPI_slave_GetTxBufferSize(void) 
{
    uint8 size;

    #if(SPI_slave_TX_SOFTWARE_BUF_ENABLED)

        /* Disable Interrupt to protect variables that could change on interrupt. */
        SPI_slave_DisableTxInt();

        if(SPI_slave_txBufferRead == SPI_slave_txBufferWrite)
        {
            size = 0u;
        }
        else if(SPI_slave_txBufferRead < SPI_slave_txBufferWrite)
        {
            size = (SPI_slave_txBufferWrite - SPI_slave_txBufferRead);
        }
        else
        {
            size = (SPI_slave_TX_BUFFER_SIZE - SPI_slave_txBufferRead) + SPI_slave_txBufferWrite;
        }

        /* Enable Interrupt. */
        SPI_slave_EnableTxInt();

    #else /* !SPI_slave_TX_SOFTWARE_BUF_ENABLED */

        size = SPI_slave_TX_STATUS_REG;

        /* Is the fifo is full. */
        if((size & SPI_slave_STS_TX_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else if((size & SPI_slave_STS_TX_FIFO_NOT_FULL) != 0u)
        {
            size = 1u;
        }
        else
        {
            size = 4u;
        }

    #endif /* SPI_slave_TX_SOFTWARE_BUF_ENABLED */

    return (size);
}


/*******************************************************************************
* Function Name: SPI_slave_ClearRxBuffer
********************************************************************************
*
* Summary:
*  Clear the RX RAM buffer by setting the read and write pointers both to zero.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  SPI_slave_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer, modified every function
*  call - resets to zero.
*  SPI_slave_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified every function call -
*  resets to zero.
*
* Theory:
*  Setting the pointers to zero makes the system believe there is no data to
*  read and writing will resume at address 0 overwriting any data that may have
*  remained in the RAM.
*
* Side Effects:
*  Any received data not read from the RAM buffer will be lost when overwritten.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPI_slave_ClearRxBuffer(void) 
{
    /* Clear Hardware RX FIFO */
    while((SPI_slave_RX_STATUS_REG & SPI_slave_STS_RX_FIFO_NOT_EMPTY) != 0u)
    {
        CY_GET_REG8(SPI_slave_RXDATA_PTR);
    }

    #if(SPI_slave_RX_SOFTWARE_BUF_ENABLED)

        /* Disable interrupt to protect variables that could change on interrupt. */
        SPI_slave_DisableRxInt();

        SPI_slave_rxBufferRead  = 0u;
        SPI_slave_rxBufferWrite = 0u;
		SPI_slave_rxBufferFull  = 0u;
        /* Enable interrupt. */
        SPI_slave_EnableRxInt();

    #endif /* SPI_slave_RX_SOFTWARE_BUF_ENABLED */
}


/*******************************************************************************
* Function Name: SPI_slave_ClearTxBuffer
********************************************************************************
*
* Summary:
*  Clear the TX RAM buffer by setting the read and write pointers both to zero.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  SPI_slave_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer, modified every function
*  call - resets to zero.
*  SPI_slave_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified every function call -
*  resets to zero.
*
* Theory:
*  Setting the pointers to zero makes the system believe there is no data to
*  read and writing will resume at address 0 overwriting any data that may have
*  remained in the RAM.
*
* Side Effects:
*  Any data not yet transmitted from the RAM buffer will be lost when
*  overwritten.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPI_slave_ClearTxBuffer(void) 
{
    uint8 enableInterrupts;

    /* Clear Hardware TX FIFO */
    enableInterrupts = CyEnterCriticalSection();

    #if(SPI_slave_DATA_WIDTH <= 8u)

        /* Clear TX FIFO */
        SPI_slave_TX_AUX_CONTROL_DP0_REG |= (uint8)SPI_slave_FIFO_CLR;
        SPI_slave_TX_AUX_CONTROL_DP0_REG &= (uint8)~SPI_slave_FIFO_CLR;

    #else

        /* Clear TX FIFO */
        SPI_slave_TX_AUX_CONTROL_DP0_REG |= (uint8)SPI_slave_FIFO_CLR;
        SPI_slave_TX_AUX_CONTROL_DP0_REG &= (uint8)~SPI_slave_FIFO_CLR;
        SPI_slave_TX_AUX_CONTROL_DP1_REG |= (uint8)SPI_slave_FIFO_CLR;
        SPI_slave_TX_AUX_CONTROL_DP1_REG &= (uint8)~SPI_slave_FIFO_CLR;

    #endif /* SPI_slave_DATA_WIDTH > 8u */

    CyExitCriticalSection(enableInterrupts);

    #if(SPI_slave_TX_SOFTWARE_BUF_ENABLED)

        /* Disable Interrupt to protect variables that could change on interrupt. */
        SPI_slave_DisableTxInt();

        SPI_slave_txBufferRead  = 0u;
        SPI_slave_txBufferWrite = 0u;
		SPI_slave_txBufferFull  = 0u;
		
        /* If Buffer is empty then disable TX FIFO status interrupt */
        SPI_slave_TX_STATUS_MASK_REG &= (uint8)~SPI_slave_STS_TX_FIFO_NOT_FULL;

        /* Enable Interrupt. */
        SPI_slave_EnableTxInt();

    #endif /* SPI_slave_TX_SOFTWARE_BUF_ENABLED */
}


#if (SPI_slave_BIDIRECTIONAL_MODE != 0u)

    /*******************************************************************************
    * Function Name: SPI_slave_TxEnable
    ********************************************************************************
    *
    * Summary:
    *  If the SPI Slave is configured to use a single bi-directional pin then this
    *  will set the bi-directional pin to transmit.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void SPI_slave_TxEnable(void) 
    {
            SPI_slave_CONTROL_REG |= SPI_slave_CTRL_TX_SIGNAL_EN;
    }


    /*******************************************************************************
    * Function Name: SPI_slave_TxDisable
    ********************************************************************************
    *
    * Summary:
    *  If the SPI Slave is configured to use a single bi-directional pin then this
    *  will set the bi-directional pin to receive.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void SPI_slave_TxDisable(void) 
    {
            SPI_slave_CONTROL_REG &= (uint8)~SPI_slave_CTRL_TX_SIGNAL_EN;
    }

#endif /* SPI_slave_BIDIRECTIONAL_MODE != 0u */


/*******************************************************************************
* Function Name: SPI_slave_PutArray
********************************************************************************
*
* Summary:
*  Write available data from RAM/ROM to the TX buffer while space is available
*  in the TX buffer. Keep trying until all data is passed to the TX buffer. If
*  used Mode 00 or 01 before PutArray() function should be called
*  WriteTxDataZero() function.
*
* Parameters:
*  *buffer: Pointer to the location in RAM containing the data to send
*  byteCount: The number of bytes to move to the transmit buffer.
*
* Return:
*  None.
*
* Side Effects:
*  Will stay in this routine until all data has been sent.  May get locked in
*  this loop if data is not being initiated by the master if there is not
*  enough room in the TX FIFO.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPI_slave_PutArray(const uint8 buffer[], uint8 byteCount)
                                                                    
{
    uint8 bufIndex;
    bufIndex = 0u;

    while(byteCount > 0u)
    {
        SPI_slave_WriteTxData(buffer[bufIndex]);
        bufIndex++;
        byteCount--;
    }
}


/*******************************************************************************
* Function Name: SPI_slave_ClearFIFO
********************************************************************************
*
* Summary:
*  Clear the RX and TX FIFO's of all data for a fresh start.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  Clear status register of the component.
*
*******************************************************************************/
void SPI_slave_ClearFIFO(void) 
{
    uint8 enableInterrupts;

    while((SPI_slave_RX_STATUS_REG & SPI_slave_STS_RX_FIFO_NOT_EMPTY) != 0u)
    {
        CY_GET_REG8(SPI_slave_RXDATA_PTR);
    }

    enableInterrupts = CyEnterCriticalSection();

    #if(SPI_slave_DATA_WIDTH <= 8u)

        /* Clear TX FIFO */
        SPI_slave_TX_AUX_CONTROL_DP0_REG |= (uint8)SPI_slave_FIFO_CLR;
        SPI_slave_TX_AUX_CONTROL_DP0_REG &= (uint8)~SPI_slave_FIFO_CLR;

    #else

        /* Clear TX FIFO */
        SPI_slave_TX_AUX_CONTROL_DP0_REG |= (uint8)SPI_slave_FIFO_CLR;
        SPI_slave_TX_AUX_CONTROL_DP0_REG &= (uint8)~SPI_slave_FIFO_CLR;
        SPI_slave_TX_AUX_CONTROL_DP1_REG |= (uint8)SPI_slave_FIFO_CLR;
        SPI_slave_TX_AUX_CONTROL_DP1_REG &= (uint8)~SPI_slave_FIFO_CLR;

    #endif /* SPI_slave_DATA_WIDTH <= 8u */

    CyExitCriticalSection(enableInterrupts);
}


/* Following functions are for version Compatibility, they are obsolete.
*  Please do not use it in new projects.
*/


/*******************************************************************************
* Function Name: SPI_slave_EnableInt
********************************************************************************
*
* Summary:
*  Enable internal interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void SPI_slave_EnableInt(void) 
{
    #if(SPI_slave_INTERNAL_TX_INT_ENABLED)
        CyIntEnable(SPI_slave_TX_ISR_NUMBER);
    #endif /* SPI_slave_INTERNAL_TX_INT_ENABLED */

    #if(SPI_slave_INTERNAL_RX_INT_ENABLED)
        CyIntEnable(SPI_slave_RX_ISR_NUMBER);
    #endif /* SPI_slave_INTERNAL_RX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: SPI_slave_DisableInt
********************************************************************************
*
* Summary:
*  Disable internal interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void SPI_slave_DisableInt(void) 
{
    #if(SPI_slave_INTERNAL_TX_INT_ENABLED)
        CyIntDisable(SPI_slave_TX_ISR_NUMBER);
    #endif /* SPI_slave_INTERNAL_TX_INT_ENABLED */

    #if(SPI_slave_INTERNAL_RX_INT_ENABLED)
        CyIntDisable(SPI_slave_RX_ISR_NUMBER);
    #endif /* SPI_slave_INTERNAL_RX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: SPI_slave_SetInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void SPI_slave_SetInterruptMode(uint8 intSrc) 
{
    SPI_slave_TX_STATUS_MASK_REG  = intSrc;
    SPI_slave_RX_STATUS_MASK_REG  = intSrc;
}


/*******************************************************************************
* Function Name: SPI_slave_ReadStatus
********************************************************************************
*
* Summary:
*  Read the status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the status register.
*
* Global variables:
*  SPI_slave_swStatus - used to store in software status register,
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the status register for error detection
*  and flow control.
*
* Side Effects:
*  Clear status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 SPI_slave_ReadStatus(void) 
{
    uint8 tmpStatus;

    #if ((SPI_slave_TX_SOFTWARE_BUF_ENABLED) || (SPI_slave_RX_SOFTWARE_BUF_ENABLED))

        SPI_slave_DisableInt();

        tmpStatus = SPI_slave_GET_STATUS_TX(SPI_slave_swStatusTx) |
              (SPI_slave_GET_STATUS_RX(SPI_slave_swStatusRx) & (uint8)~SPI_slave_STS_RX_FIFO_FULL);

        SPI_slave_swStatusTx = 0u;
        SPI_slave_swStatusRx = 0u;

        /* Enable Interrupts */
        SPI_slave_EnableInt();

    #else /* !((SPI_slave_TX_SOFTWARE_BUF_ENABLED) || (SPI_slave_RX_SOFTWARE_BUF_ENABLED)) */

        tmpStatus = SPI_slave_TX_STATUS_REG | (SPI_slave_RX_STATUS_REG &
                                                      (uint8)~SPI_slave_STS_RX_FIFO_FULL);

    #endif /* (SPI_slave_TX_SOFTWARE_BUF_ENABLED) || (SPI_slave_RX_SOFTWARE_BUF_ENABLED) */

    return(tmpStatus);
}


/* [] END OF FILE */
