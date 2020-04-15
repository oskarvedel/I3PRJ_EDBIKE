/*******************************************************************************
* File Name: WheelTickTimer_PM.c
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

#include "WheelTickTimer.h"

static WheelTickTimer_backupStruct WheelTickTimer_backup;


/*******************************************************************************
* Function Name: WheelTickTimer_SaveConfig
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
*  WheelTickTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void WheelTickTimer_SaveConfig(void) 
{
    #if (!WheelTickTimer_UsingFixedFunction)
        WheelTickTimer_backup.TimerUdb = WheelTickTimer_ReadCounter();
        WheelTickTimer_backup.InterruptMaskValue = WheelTickTimer_STATUS_MASK;
        #if (WheelTickTimer_UsingHWCaptureCounter)
            WheelTickTimer_backup.TimerCaptureCounter = WheelTickTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!WheelTickTimer_UDB_CONTROL_REG_REMOVED)
            WheelTickTimer_backup.TimerControlRegister = WheelTickTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: WheelTickTimer_RestoreConfig
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
*  WheelTickTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void WheelTickTimer_RestoreConfig(void) 
{   
    #if (!WheelTickTimer_UsingFixedFunction)

        WheelTickTimer_WriteCounter(WheelTickTimer_backup.TimerUdb);
        WheelTickTimer_STATUS_MASK =WheelTickTimer_backup.InterruptMaskValue;
        #if (WheelTickTimer_UsingHWCaptureCounter)
            WheelTickTimer_SetCaptureCount(WheelTickTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!WheelTickTimer_UDB_CONTROL_REG_REMOVED)
            WheelTickTimer_WriteControlRegister(WheelTickTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: WheelTickTimer_Sleep
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
*  WheelTickTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void WheelTickTimer_Sleep(void) 
{
    #if(!WheelTickTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(WheelTickTimer_CTRL_ENABLE == (WheelTickTimer_CONTROL & WheelTickTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            WheelTickTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            WheelTickTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    WheelTickTimer_Stop();
    WheelTickTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: WheelTickTimer_Wakeup
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
*  WheelTickTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void WheelTickTimer_Wakeup(void) 
{
    WheelTickTimer_RestoreConfig();
    #if(!WheelTickTimer_UDB_CONTROL_REG_REMOVED)
        if(WheelTickTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                WheelTickTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
