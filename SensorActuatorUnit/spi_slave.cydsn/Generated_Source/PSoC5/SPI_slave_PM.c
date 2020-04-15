/*******************************************************************************
* File Name: SPI_slave_PM.c
* Version 2.70
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPI_slave_PVT.h"

static SPI_slave_BACKUP_STRUCT SPI_slave_backup = 
{
    SPI_slave_DISABLED,
    SPI_slave_BITCTR_INIT,
};


/*******************************************************************************
* Function Name: SPI_slave_SaveConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SPI_slave_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPI_slave_RestoreConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SPI_slave_RestoreConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPI_slave_Sleep
********************************************************************************
*
* Summary:
*  Prepare SPI Slave Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPI_slave_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPI_slave_Sleep(void) 
{
    /* Save components enable state */
    if ((SPI_slave_TX_STATUS_ACTL_REG & SPI_slave_INT_ENABLE) != 0u)
    {
        SPI_slave_backup.enableState = 1u;
    }
    else /* Components block is disabled */
    {
        SPI_slave_backup.enableState = 0u;
    }

    SPI_slave_Stop();

}


/*******************************************************************************
* Function Name: SPI_slave_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPI_slave_backup - used when non-retention registers are restored.
*  SPI_slave_txBufferWrite - modified every function call - resets to
*  zero.
*  SPI_slave_txBufferRead - modified every function call - resets to
*  zero.
*  SPI_slave_rxBufferWrite - modified every function call - resets to
*  zero.
*  SPI_slave_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPI_slave_Wakeup(void) 
{
    #if (SPI_slave_TX_SOFTWARE_BUF_ENABLED)
        SPI_slave_txBufferFull = 0u;
        SPI_slave_txBufferRead = 0u;
        SPI_slave_txBufferWrite = 0u;
    #endif /* SPI_slave_TX_SOFTWARE_BUF_ENABLED */

    #if (SPI_slave_RX_SOFTWARE_BUF_ENABLED)
        SPI_slave_rxBufferFull = 0u;
        SPI_slave_rxBufferRead = 0u;
        SPI_slave_rxBufferWrite = 0u;
    #endif /* SPI_slave_RX_SOFTWARE_BUF_ENABLED */

    SPI_slave_ClearFIFO();

    /* Restore components block enable state */
    if (SPI_slave_backup.enableState != 0u)
    {
         /* Components block was enabled */
         SPI_slave_Enable();
    } /* Do nothing if components block was disabled */
}


/* [] END OF FILE */
