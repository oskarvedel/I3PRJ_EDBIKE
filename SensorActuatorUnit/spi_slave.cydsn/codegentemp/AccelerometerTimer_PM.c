/*******************************************************************************
* File Name: AccelerometerTimer_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "AccelerometerTimer.h"

static AccelerometerTimer_backupStruct AccelerometerTimer_backup;


/*******************************************************************************
* Function Name: AccelerometerTimer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  AccelerometerTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void AccelerometerTimer_SaveConfig(void) 
{
    #if (!AccelerometerTimer_UsingFixedFunction)
        AccelerometerTimer_backup.TimerUdb = AccelerometerTimer_ReadCounter();
        AccelerometerTimer_backup.InterruptMaskValue = AccelerometerTimer_STATUS_MASK;
        #if (AccelerometerTimer_UsingHWCaptureCounter)
            AccelerometerTimer_backup.TimerCaptureCounter = AccelerometerTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!AccelerometerTimer_UDB_CONTROL_REG_REMOVED)
            AccelerometerTimer_backup.TimerControlRegister = AccelerometerTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: AccelerometerTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  AccelerometerTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void AccelerometerTimer_RestoreConfig(void) 
{   
    #if (!AccelerometerTimer_UsingFixedFunction)

        AccelerometerTimer_WriteCounter(AccelerometerTimer_backup.TimerUdb);
        AccelerometerTimer_STATUS_MASK =AccelerometerTimer_backup.InterruptMaskValue;
        #if (AccelerometerTimer_UsingHWCaptureCounter)
            AccelerometerTimer_SetCaptureCount(AccelerometerTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!AccelerometerTimer_UDB_CONTROL_REG_REMOVED)
            AccelerometerTimer_WriteControlRegister(AccelerometerTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: AccelerometerTimer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  AccelerometerTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void AccelerometerTimer_Sleep(void) 
{
    #if(!AccelerometerTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(AccelerometerTimer_CTRL_ENABLE == (AccelerometerTimer_CONTROL & AccelerometerTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            AccelerometerTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            AccelerometerTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    AccelerometerTimer_Stop();
    AccelerometerTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: AccelerometerTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  AccelerometerTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void AccelerometerTimer_Wakeup(void) 
{
    AccelerometerTimer_RestoreConfig();
    #if(!AccelerometerTimer_UDB_CONTROL_REG_REMOVED)
        if(AccelerometerTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                AccelerometerTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
