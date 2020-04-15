/*******************************************************************************
* File Name: Counter_clock1.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Counter_clock1_H)
#define CY_CLOCK_Counter_clock1_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void Counter_clock1_Start(void) ;
void Counter_clock1_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Counter_clock1_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Counter_clock1_StandbyPower(uint8 state) ;
void Counter_clock1_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Counter_clock1_GetDividerRegister(void) ;
void Counter_clock1_SetModeRegister(uint8 modeBitMask) ;
void Counter_clock1_ClearModeRegister(uint8 modeBitMask) ;
uint8 Counter_clock1_GetModeRegister(void) ;
void Counter_clock1_SetSourceRegister(uint8 clkSource) ;
uint8 Counter_clock1_GetSourceRegister(void) ;
#if defined(Counter_clock1__CFG3)
void Counter_clock1_SetPhaseRegister(uint8 clkPhase) ;
uint8 Counter_clock1_GetPhaseRegister(void) ;
#endif /* defined(Counter_clock1__CFG3) */

#define Counter_clock1_Enable()                       Counter_clock1_Start()
#define Counter_clock1_Disable()                      Counter_clock1_Stop()
#define Counter_clock1_SetDivider(clkDivider)         Counter_clock1_SetDividerRegister(clkDivider, 1u)
#define Counter_clock1_SetDividerValue(clkDivider)    Counter_clock1_SetDividerRegister((clkDivider) - 1u, 1u)
#define Counter_clock1_SetMode(clkMode)               Counter_clock1_SetModeRegister(clkMode)
#define Counter_clock1_SetSource(clkSource)           Counter_clock1_SetSourceRegister(clkSource)
#if defined(Counter_clock1__CFG3)
#define Counter_clock1_SetPhase(clkPhase)             Counter_clock1_SetPhaseRegister(clkPhase)
#define Counter_clock1_SetPhaseValue(clkPhase)        Counter_clock1_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Counter_clock1__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Counter_clock1_CLKEN              (* (reg8 *) Counter_clock1__PM_ACT_CFG)
#define Counter_clock1_CLKEN_PTR          ((reg8 *) Counter_clock1__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Counter_clock1_CLKSTBY            (* (reg8 *) Counter_clock1__PM_STBY_CFG)
#define Counter_clock1_CLKSTBY_PTR        ((reg8 *) Counter_clock1__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Counter_clock1_DIV_LSB            (* (reg8 *) Counter_clock1__CFG0)
#define Counter_clock1_DIV_LSB_PTR        ((reg8 *) Counter_clock1__CFG0)
#define Counter_clock1_DIV_PTR            ((reg16 *) Counter_clock1__CFG0)

/* Clock MSB divider configuration register. */
#define Counter_clock1_DIV_MSB            (* (reg8 *) Counter_clock1__CFG1)
#define Counter_clock1_DIV_MSB_PTR        ((reg8 *) Counter_clock1__CFG1)

/* Mode and source configuration register */
#define Counter_clock1_MOD_SRC            (* (reg8 *) Counter_clock1__CFG2)
#define Counter_clock1_MOD_SRC_PTR        ((reg8 *) Counter_clock1__CFG2)

#if defined(Counter_clock1__CFG3)
/* Analog clock phase configuration register */
#define Counter_clock1_PHASE              (* (reg8 *) Counter_clock1__CFG3)
#define Counter_clock1_PHASE_PTR          ((reg8 *) Counter_clock1__CFG3)
#endif /* defined(Counter_clock1__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Counter_clock1_CLKEN_MASK         Counter_clock1__PM_ACT_MSK
#define Counter_clock1_CLKSTBY_MASK       Counter_clock1__PM_STBY_MSK

/* CFG2 field masks */
#define Counter_clock1_SRC_SEL_MSK        Counter_clock1__CFG2_SRC_SEL_MASK
#define Counter_clock1_MODE_MASK          (~(Counter_clock1_SRC_SEL_MSK))

#if defined(Counter_clock1__CFG3)
/* CFG3 phase mask */
#define Counter_clock1_PHASE_MASK         Counter_clock1__CFG3_PHASE_DLY_MASK
#endif /* defined(Counter_clock1__CFG3) */

#endif /* CY_CLOCK_Counter_clock1_H */


/* [] END OF FILE */
