/*******************************************************************************
* File Name: Accelerometer_Counter_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Accelerometer_Counter.h"

static Accelerometer_Counter_backupStruct Accelerometer_Counter_backup;


/*******************************************************************************
* Function Name: Accelerometer_Counter_SaveConfig
********************************************************************************
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
*  Accelerometer_Counter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Accelerometer_Counter_SaveConfig(void) 
{
    #if (!Accelerometer_Counter_UsingFixedFunction)

        Accelerometer_Counter_backup.CounterUdb = Accelerometer_Counter_ReadCounter();

        #if(!Accelerometer_Counter_ControlRegRemoved)
            Accelerometer_Counter_backup.CounterControlRegister = Accelerometer_Counter_ReadControlRegister();
        #endif /* (!Accelerometer_Counter_ControlRegRemoved) */

    #endif /* (!Accelerometer_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Accelerometer_Counter_RestoreConfig
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
*  Accelerometer_Counter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Accelerometer_Counter_RestoreConfig(void) 
{      
    #if (!Accelerometer_Counter_UsingFixedFunction)

       Accelerometer_Counter_WriteCounter(Accelerometer_Counter_backup.CounterUdb);

        #if(!Accelerometer_Counter_ControlRegRemoved)
            Accelerometer_Counter_WriteControlRegister(Accelerometer_Counter_backup.CounterControlRegister);
        #endif /* (!Accelerometer_Counter_ControlRegRemoved) */

    #endif /* (!Accelerometer_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Accelerometer_Counter_Sleep
********************************************************************************
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
*  Accelerometer_Counter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Accelerometer_Counter_Sleep(void) 
{
    #if(!Accelerometer_Counter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Accelerometer_Counter_CTRL_ENABLE == (Accelerometer_Counter_CONTROL & Accelerometer_Counter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Accelerometer_Counter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Accelerometer_Counter_backup.CounterEnableState = 0u;
        }
    #else
        Accelerometer_Counter_backup.CounterEnableState = 1u;
        if(Accelerometer_Counter_backup.CounterEnableState != 0u)
        {
            Accelerometer_Counter_backup.CounterEnableState = 0u;
        }
    #endif /* (!Accelerometer_Counter_ControlRegRemoved) */
    
    Accelerometer_Counter_Stop();
    Accelerometer_Counter_SaveConfig();
}


/*******************************************************************************
* Function Name: Accelerometer_Counter_Wakeup
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
*  Accelerometer_Counter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Accelerometer_Counter_Wakeup(void) 
{
    Accelerometer_Counter_RestoreConfig();
    #if(!Accelerometer_Counter_ControlRegRemoved)
        if(Accelerometer_Counter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Accelerometer_Counter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Accelerometer_Counter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
