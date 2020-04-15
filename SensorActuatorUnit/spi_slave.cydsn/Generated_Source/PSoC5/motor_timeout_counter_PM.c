/*******************************************************************************
* File Name: motor_timeout_counter_PM.c  
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

#include "motor_timeout_counter.h"

static motor_timeout_counter_backupStruct motor_timeout_counter_backup;


/*******************************************************************************
* Function Name: motor_timeout_counter_SaveConfig
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
*  motor_timeout_counter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void motor_timeout_counter_SaveConfig(void) 
{
    #if (!motor_timeout_counter_UsingFixedFunction)

        motor_timeout_counter_backup.CounterUdb = motor_timeout_counter_ReadCounter();

        #if(!motor_timeout_counter_ControlRegRemoved)
            motor_timeout_counter_backup.CounterControlRegister = motor_timeout_counter_ReadControlRegister();
        #endif /* (!motor_timeout_counter_ControlRegRemoved) */

    #endif /* (!motor_timeout_counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: motor_timeout_counter_RestoreConfig
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
*  motor_timeout_counter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void motor_timeout_counter_RestoreConfig(void) 
{      
    #if (!motor_timeout_counter_UsingFixedFunction)

       motor_timeout_counter_WriteCounter(motor_timeout_counter_backup.CounterUdb);

        #if(!motor_timeout_counter_ControlRegRemoved)
            motor_timeout_counter_WriteControlRegister(motor_timeout_counter_backup.CounterControlRegister);
        #endif /* (!motor_timeout_counter_ControlRegRemoved) */

    #endif /* (!motor_timeout_counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: motor_timeout_counter_Sleep
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
*  motor_timeout_counter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void motor_timeout_counter_Sleep(void) 
{
    #if(!motor_timeout_counter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(motor_timeout_counter_CTRL_ENABLE == (motor_timeout_counter_CONTROL & motor_timeout_counter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            motor_timeout_counter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            motor_timeout_counter_backup.CounterEnableState = 0u;
        }
    #else
        motor_timeout_counter_backup.CounterEnableState = 1u;
        if(motor_timeout_counter_backup.CounterEnableState != 0u)
        {
            motor_timeout_counter_backup.CounterEnableState = 0u;
        }
    #endif /* (!motor_timeout_counter_ControlRegRemoved) */
    
    motor_timeout_counter_Stop();
    motor_timeout_counter_SaveConfig();
}


/*******************************************************************************
* Function Name: motor_timeout_counter_Wakeup
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
*  motor_timeout_counter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void motor_timeout_counter_Wakeup(void) 
{
    motor_timeout_counter_RestoreConfig();
    #if(!motor_timeout_counter_ControlRegRemoved)
        if(motor_timeout_counter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            motor_timeout_counter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!motor_timeout_counter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
