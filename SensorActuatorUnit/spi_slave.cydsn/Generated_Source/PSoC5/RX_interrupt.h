/*******************************************************************************
* File Name: RX_interrupt.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_RX_interrupt_H)
#define CY_ISR_RX_interrupt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void RX_interrupt_Start(void);
void RX_interrupt_StartEx(cyisraddress address);
void RX_interrupt_Stop(void);

CY_ISR_PROTO(RX_interrupt_Interrupt);

void RX_interrupt_SetVector(cyisraddress address);
cyisraddress RX_interrupt_GetVector(void);

void RX_interrupt_SetPriority(uint8 priority);
uint8 RX_interrupt_GetPriority(void);

void RX_interrupt_Enable(void);
uint8 RX_interrupt_GetState(void);
void RX_interrupt_Disable(void);

void RX_interrupt_SetPending(void);
void RX_interrupt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the RX_interrupt ISR. */
#define RX_interrupt_INTC_VECTOR            ((reg32 *) RX_interrupt__INTC_VECT)

/* Address of the RX_interrupt ISR priority. */
#define RX_interrupt_INTC_PRIOR             ((reg8 *) RX_interrupt__INTC_PRIOR_REG)

/* Priority of the RX_interrupt interrupt. */
#define RX_interrupt_INTC_PRIOR_NUMBER      RX_interrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable RX_interrupt interrupt. */
#define RX_interrupt_INTC_SET_EN            ((reg32 *) RX_interrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the RX_interrupt interrupt. */
#define RX_interrupt_INTC_CLR_EN            ((reg32 *) RX_interrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the RX_interrupt interrupt state to pending. */
#define RX_interrupt_INTC_SET_PD            ((reg32 *) RX_interrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the RX_interrupt interrupt. */
#define RX_interrupt_INTC_CLR_PD            ((reg32 *) RX_interrupt__INTC_CLR_PD_REG)


#endif /* CY_ISR_RX_interrupt_H */


/* [] END OF FILE */
