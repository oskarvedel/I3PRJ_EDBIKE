/*******************************************************************************
* File Name: WheelTickPin.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_WheelTickPin_H) /* Pins WheelTickPin_H */
#define CY_PINS_WheelTickPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "WheelTickPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 WheelTickPin__PORT == 15 && ((WheelTickPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    WheelTickPin_Write(uint8 value);
void    WheelTickPin_SetDriveMode(uint8 mode);
uint8   WheelTickPin_ReadDataReg(void);
uint8   WheelTickPin_Read(void);
void    WheelTickPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   WheelTickPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the WheelTickPin_SetDriveMode() function.
     *  @{
     */
        #define WheelTickPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define WheelTickPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define WheelTickPin_DM_RES_UP          PIN_DM_RES_UP
        #define WheelTickPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define WheelTickPin_DM_OD_LO           PIN_DM_OD_LO
        #define WheelTickPin_DM_OD_HI           PIN_DM_OD_HI
        #define WheelTickPin_DM_STRONG          PIN_DM_STRONG
        #define WheelTickPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define WheelTickPin_MASK               WheelTickPin__MASK
#define WheelTickPin_SHIFT              WheelTickPin__SHIFT
#define WheelTickPin_WIDTH              1u

/* Interrupt constants */
#if defined(WheelTickPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in WheelTickPin_SetInterruptMode() function.
     *  @{
     */
        #define WheelTickPin_INTR_NONE      (uint16)(0x0000u)
        #define WheelTickPin_INTR_RISING    (uint16)(0x0001u)
        #define WheelTickPin_INTR_FALLING   (uint16)(0x0002u)
        #define WheelTickPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define WheelTickPin_INTR_MASK      (0x01u) 
#endif /* (WheelTickPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WheelTickPin_PS                     (* (reg8 *) WheelTickPin__PS)
/* Data Register */
#define WheelTickPin_DR                     (* (reg8 *) WheelTickPin__DR)
/* Port Number */
#define WheelTickPin_PRT_NUM                (* (reg8 *) WheelTickPin__PRT) 
/* Connect to Analog Globals */                                                  
#define WheelTickPin_AG                     (* (reg8 *) WheelTickPin__AG)                       
/* Analog MUX bux enable */
#define WheelTickPin_AMUX                   (* (reg8 *) WheelTickPin__AMUX) 
/* Bidirectional Enable */                                                        
#define WheelTickPin_BIE                    (* (reg8 *) WheelTickPin__BIE)
/* Bit-mask for Aliased Register Access */
#define WheelTickPin_BIT_MASK               (* (reg8 *) WheelTickPin__BIT_MASK)
/* Bypass Enable */
#define WheelTickPin_BYP                    (* (reg8 *) WheelTickPin__BYP)
/* Port wide control signals */                                                   
#define WheelTickPin_CTL                    (* (reg8 *) WheelTickPin__CTL)
/* Drive Modes */
#define WheelTickPin_DM0                    (* (reg8 *) WheelTickPin__DM0) 
#define WheelTickPin_DM1                    (* (reg8 *) WheelTickPin__DM1)
#define WheelTickPin_DM2                    (* (reg8 *) WheelTickPin__DM2) 
/* Input Buffer Disable Override */
#define WheelTickPin_INP_DIS                (* (reg8 *) WheelTickPin__INP_DIS)
/* LCD Common or Segment Drive */
#define WheelTickPin_LCD_COM_SEG            (* (reg8 *) WheelTickPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define WheelTickPin_LCD_EN                 (* (reg8 *) WheelTickPin__LCD_EN)
/* Slew Rate Control */
#define WheelTickPin_SLW                    (* (reg8 *) WheelTickPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define WheelTickPin_PRTDSI__CAPS_SEL       (* (reg8 *) WheelTickPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define WheelTickPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) WheelTickPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define WheelTickPin_PRTDSI__OE_SEL0        (* (reg8 *) WheelTickPin__PRTDSI__OE_SEL0) 
#define WheelTickPin_PRTDSI__OE_SEL1        (* (reg8 *) WheelTickPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define WheelTickPin_PRTDSI__OUT_SEL0       (* (reg8 *) WheelTickPin__PRTDSI__OUT_SEL0) 
#define WheelTickPin_PRTDSI__OUT_SEL1       (* (reg8 *) WheelTickPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define WheelTickPin_PRTDSI__SYNC_OUT       (* (reg8 *) WheelTickPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(WheelTickPin__SIO_CFG)
    #define WheelTickPin_SIO_HYST_EN        (* (reg8 *) WheelTickPin__SIO_HYST_EN)
    #define WheelTickPin_SIO_REG_HIFREQ     (* (reg8 *) WheelTickPin__SIO_REG_HIFREQ)
    #define WheelTickPin_SIO_CFG            (* (reg8 *) WheelTickPin__SIO_CFG)
    #define WheelTickPin_SIO_DIFF           (* (reg8 *) WheelTickPin__SIO_DIFF)
#endif /* (WheelTickPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(WheelTickPin__INTSTAT)
    #define WheelTickPin_INTSTAT            (* (reg8 *) WheelTickPin__INTSTAT)
    #define WheelTickPin_SNAP               (* (reg8 *) WheelTickPin__SNAP)
    
	#define WheelTickPin_0_INTTYPE_REG 		(* (reg8 *) WheelTickPin__0__INTTYPE)
#endif /* (WheelTickPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_WheelTickPin_H */


/* [] END OF FILE */
