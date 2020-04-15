/*******************************************************************************
* File Name: MotorLockTimer_PM.c
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

#include "MotorLockTimer.h"

static MotorLockTimer_backupStruct MotorLockTimer_backup;


/*******************************************************************************
* Function Name: MotorLockTimer_SaveConfig
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
*  MotorLockTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void MotorLockTimer_SaveConfig(void) 
{
    #if (!MotorLockTimer_UsingFixedFunction)
        MotorLockTimer_backup.TimerUdb = MotorLockTimer_ReadCounter();
        MotorLockTimer_backup.InterruptMaskValue = MotorLockTimer_STATUS_MASK;
        #if (MotorLockTimer_UsingHWCaptureCounter)
            MotorLockTimer_backup.TimerCaptureCounter = MotorLockTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!MotorLockTimer_UDB_CONTROL_REG_REMOVED)
            MotorLockTimer_backup.TimerControlRegister = MotorLockTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: MotorLockTimer_RestoreConfig
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
*  MotorLockTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MotorLockTimer_RestoreConfig(void) 
{   
    #if (!MotorLockTimer_UsingFixedFunction)

        MotorLockTimer_WriteCounter(MotorLockTimer_backup.TimerUdb);
        MotorLockTimer_STATUS_MASK =MotorLockTimer_backup.InterruptMaskValue;
        #if (MotorLockTimer_UsingHWCaptureCounter)
            MotorLockTimer_SetCaptureCount(MotorLockTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!MotorLockTimer_UDB_CONTROL_REG_REMOVED)
            MotorLockTimer_WriteControlRegister(MotorLockTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: MotorLockTimer_Sleep
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
*  MotorLockTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void MotorLockTimer_Sleep(void) 
{
    #if(!MotorLockTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(MotorLockTimer_CTRL_ENABLE == (MotorLockTimer_CONTROL & MotorLockTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            MotorLockTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            MotorLockTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    MotorLockTimer_Stop();
    MotorLockTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: MotorLockTimer_Wakeup
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
*  MotorLockTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MotorLockTimer_Wakeup(void) 
{
    MotorLockTimer_RestoreConfig();
    #if(!MotorLockTimer_UDB_CONTROL_REG_REMOVED)
        if(MotorLockTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                MotorLockTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
