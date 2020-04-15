/*******************************************************************************
* File Name: Counter_clock2.h
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

#if !defined(CY_CLOCK_Counter_clock2_H)
#define CY_CLOCK_Counter_clock2_H

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

void Counter_clock2_Start(void) ;
void Counter_clock2_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Counter_clock2_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Counter_clock2_StandbyPower(uint8 state) ;
void Counter_clock2_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Counter_clock2_GetDividerRegister(void) ;
void Counter_clock2_SetModeRegister(uint8 modeBitMask) ;
void Counter_clock2_ClearModeRegister(uint8 modeBitMask) ;
uint8 Counter_clock2_GetModeRegister(void) ;
void Counter_clock2_SetSourceRegister(uint8 clkSource) ;
uint8 Counter_clock2_GetSourceRegister(void) ;
#if defined(Counter_clock2__CFG3)
void Counter_clock2_SetPhaseRegister(uint8 clkPhase) ;
uint8 Counter_clock2_GetPhaseRegister(void) ;
#endif /* defined(Counter_clock2__CFG3) */

#define Counter_clock2_Enable()                       Counter_clock2_Start()
#define Counter_clock2_Disable()                      Counter_clock2_Stop()
#define Counter_clock2_SetDivider(clkDivider)         Counter_clock2_SetDividerRegister(clkDivider, 1u)
#define Counter_clock2_SetDividerValue(clkDivider)    Counter_clock2_SetDividerRegister((clkDivider) - 1u, 1u)
#define Counter_clock2_SetMode(clkMode)               Counter_clock2_SetModeRegister(clkMode)
#define Counter_clock2_SetSource(clkSource)           Counter_clock2_SetSourceRegister(clkSource)
#if defined(Counter_clock2__CFG3)
#define Counter_clock2_SetPhase(clkPhase)             Counter_clock2_SetPhaseRegister(clkPhase)
#define Counter_clock2_SetPhaseValue(clkPhase)        Counter_clock2_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Counter_clock2__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Counter_clock2_CLKEN              (* (reg8 *) Counter_clock2__PM_ACT_CFG)
#define Counter_clock2_CLKEN_PTR          ((reg8 *) Counter_clock2__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Counter_clock2_CLKSTBY            (* (reg8 *) Counter_clock2__PM_STBY_CFG)
#define Counter_clock2_CLKSTBY_PTR        ((reg8 *) Counter_clock2__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Counter_clock2_DIV_LSB            (* (reg8 *) Counter_clock2__CFG0)
#define Counter_clock2_DIV_LSB_PTR        ((reg8 *) Counter_clock2__CFG0)
#define Counter_clock2_DIV_PTR            ((reg16 *) Counter_clock2__CFG0)

/* Clock MSB divider configuration register. */
#define Counter_clock2_DIV_MSB            (* (reg8 *) Counter_clock2__CFG1)
#define Counter_clock2_DIV_MSB_PTR        ((reg8 *) Counter_clock2__CFG1)

/* Mode and source configuration register */
#define Counter_clock2_MOD_SRC            (* (reg8 *) Counter_clock2__CFG2)
#define Counter_clock2_MOD_SRC_PTR        ((reg8 *) Counter_clock2__CFG2)

#if defined(Counter_clock2__CFG3)
/* Analog clock phase configuration register */
#define Counter_clock2_PHASE              (* (reg8 *) Counter_clock2__CFG3)
#define Counter_clock2_PHASE_PTR          ((reg8 *) Counter_clock2__CFG3)
#endif /* defined(Counter_clock2__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Counter_clock2_CLKEN_MASK         Counter_clock2__PM_ACT_MSK
#define Counter_clock2_CLKSTBY_MASK       Counter_clock2__PM_STBY_MSK

/* CFG2 field masks */
#define Counter_clock2_SRC_SEL_MSK        Counter_clock2__CFG2_SRC_SEL_MASK
#define Counter_clock2_MODE_MASK          (~(Counter_clock2_SRC_SEL_MSK))

#if defined(Counter_clock2__CFG3)
/* CFG3 phase mask */
#define Counter_clock2_PHASE_MASK         Counter_clock2__CFG3_PHASE_DLY_MASK
#endif /* defined(Counter_clock2__CFG3) */

#endif /* CY_CLOCK_Counter_clock2_H */


/* [] END OF FILE */
