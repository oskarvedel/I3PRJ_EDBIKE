/*******************************************************************************
* File Name: MotorLockTimer.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_MotorLockTimer_H)
#define CY_TIMER_MotorLockTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 MotorLockTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define MotorLockTimer_Resolution                 16u
#define MotorLockTimer_UsingFixedFunction         0u
#define MotorLockTimer_UsingHWCaptureCounter      0u
#define MotorLockTimer_SoftwareCaptureMode        0u
#define MotorLockTimer_SoftwareTriggerMode        0u
#define MotorLockTimer_UsingHWEnable              0u
#define MotorLockTimer_EnableTriggerMode          0u
#define MotorLockTimer_InterruptOnCaptureCount    0u
#define MotorLockTimer_RunModeUsed                0u
#define MotorLockTimer_ControlRegRemoved          0u

#if defined(MotorLockTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define MotorLockTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (MotorLockTimer_UsingFixedFunction)
    #define MotorLockTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define MotorLockTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End MotorLockTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!MotorLockTimer_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (MotorLockTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!MotorLockTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}MotorLockTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    MotorLockTimer_Start(void) ;
void    MotorLockTimer_Stop(void) ;

void    MotorLockTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   MotorLockTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define MotorLockTimer_GetInterruptSource() MotorLockTimer_ReadStatusRegister()

#if(!MotorLockTimer_UDB_CONTROL_REG_REMOVED)
    uint8   MotorLockTimer_ReadControlRegister(void) ;
    void    MotorLockTimer_WriteControlRegister(uint8 control) ;
#endif /* (!MotorLockTimer_UDB_CONTROL_REG_REMOVED) */

uint16  MotorLockTimer_ReadPeriod(void) ;
void    MotorLockTimer_WritePeriod(uint16 period) ;
uint16  MotorLockTimer_ReadCounter(void) ;
void    MotorLockTimer_WriteCounter(uint16 counter) ;
uint16  MotorLockTimer_ReadCapture(void) ;
void    MotorLockTimer_SoftwareCapture(void) ;

#if(!MotorLockTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (MotorLockTimer_SoftwareCaptureMode)
        void    MotorLockTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!MotorLockTimer_UsingFixedFunction) */

    #if (MotorLockTimer_SoftwareTriggerMode)
        void    MotorLockTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (MotorLockTimer_SoftwareTriggerMode) */

    #if (MotorLockTimer_EnableTriggerMode)
        void    MotorLockTimer_EnableTrigger(void) ;
        void    MotorLockTimer_DisableTrigger(void) ;
    #endif /* (MotorLockTimer_EnableTriggerMode) */


    #if(MotorLockTimer_InterruptOnCaptureCount)
        void    MotorLockTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (MotorLockTimer_InterruptOnCaptureCount) */

    #if (MotorLockTimer_UsingHWCaptureCounter)
        void    MotorLockTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   MotorLockTimer_ReadCaptureCount(void) ;
    #endif /* (MotorLockTimer_UsingHWCaptureCounter) */

    void MotorLockTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void MotorLockTimer_Init(void)          ;
void MotorLockTimer_Enable(void)        ;
void MotorLockTimer_SaveConfig(void)    ;
void MotorLockTimer_RestoreConfig(void) ;
void MotorLockTimer_Sleep(void)         ;
void MotorLockTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define MotorLockTimer__B_TIMER__CM_NONE 0
#define MotorLockTimer__B_TIMER__CM_RISINGEDGE 1
#define MotorLockTimer__B_TIMER__CM_FALLINGEDGE 2
#define MotorLockTimer__B_TIMER__CM_EITHEREDGE 3
#define MotorLockTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define MotorLockTimer__B_TIMER__TM_NONE 0x00u
#define MotorLockTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define MotorLockTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define MotorLockTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define MotorLockTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define MotorLockTimer_INIT_PERIOD             1799u
#define MotorLockTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << MotorLockTimer_CTRL_CAP_MODE_SHIFT))
#define MotorLockTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << MotorLockTimer_CTRL_TRIG_MODE_SHIFT))
#if (MotorLockTimer_UsingFixedFunction)
    #define MotorLockTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << MotorLockTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << MotorLockTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define MotorLockTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << MotorLockTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << MotorLockTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << MotorLockTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (MotorLockTimer_UsingFixedFunction) */
#define MotorLockTimer_INIT_CAPTURE_COUNT      (2u)
#define MotorLockTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << MotorLockTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (MotorLockTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define MotorLockTimer_STATUS         (*(reg8 *) MotorLockTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define MotorLockTimer_STATUS_MASK    (*(reg8 *) MotorLockTimer_TimerHW__SR0 )
    #define MotorLockTimer_CONTROL        (*(reg8 *) MotorLockTimer_TimerHW__CFG0)
    #define MotorLockTimer_CONTROL2       (*(reg8 *) MotorLockTimer_TimerHW__CFG1)
    #define MotorLockTimer_CONTROL2_PTR   ( (reg8 *) MotorLockTimer_TimerHW__CFG1)
    #define MotorLockTimer_RT1            (*(reg8 *) MotorLockTimer_TimerHW__RT1)
    #define MotorLockTimer_RT1_PTR        ( (reg8 *) MotorLockTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define MotorLockTimer_CONTROL3       (*(reg8 *) MotorLockTimer_TimerHW__CFG2)
        #define MotorLockTimer_CONTROL3_PTR   ( (reg8 *) MotorLockTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define MotorLockTimer_GLOBAL_ENABLE  (*(reg8 *) MotorLockTimer_TimerHW__PM_ACT_CFG)
    #define MotorLockTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) MotorLockTimer_TimerHW__PM_STBY_CFG)

    #define MotorLockTimer_CAPTURE_LSB         (* (reg16 *) MotorLockTimer_TimerHW__CAP0 )
    #define MotorLockTimer_CAPTURE_LSB_PTR       ((reg16 *) MotorLockTimer_TimerHW__CAP0 )
    #define MotorLockTimer_PERIOD_LSB          (* (reg16 *) MotorLockTimer_TimerHW__PER0 )
    #define MotorLockTimer_PERIOD_LSB_PTR        ((reg16 *) MotorLockTimer_TimerHW__PER0 )
    #define MotorLockTimer_COUNTER_LSB         (* (reg16 *) MotorLockTimer_TimerHW__CNT_CMP0 )
    #define MotorLockTimer_COUNTER_LSB_PTR       ((reg16 *) MotorLockTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define MotorLockTimer_BLOCK_EN_MASK                     MotorLockTimer_TimerHW__PM_ACT_MSK
    #define MotorLockTimer_BLOCK_STBY_EN_MASK                MotorLockTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define MotorLockTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define MotorLockTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define MotorLockTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define MotorLockTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define MotorLockTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define MotorLockTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << MotorLockTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define MotorLockTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define MotorLockTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << MotorLockTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define MotorLockTimer_CTRL_MODE_SHIFT                 0x01u
        #define MotorLockTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << MotorLockTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define MotorLockTimer_CTRL_RCOD_SHIFT        0x02u
        #define MotorLockTimer_CTRL_ENBL_SHIFT        0x00u
        #define MotorLockTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define MotorLockTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << MotorLockTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define MotorLockTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << MotorLockTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define MotorLockTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << MotorLockTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define MotorLockTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << MotorLockTimer_CTRL_RCOD_SHIFT))
        #define MotorLockTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << MotorLockTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define MotorLockTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define MotorLockTimer_RT1_MASK                        ((uint8)((uint8)0x03u << MotorLockTimer_RT1_SHIFT))
    #define MotorLockTimer_SYNC                            ((uint8)((uint8)0x03u << MotorLockTimer_RT1_SHIFT))
    #define MotorLockTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define MotorLockTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << MotorLockTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define MotorLockTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << MotorLockTimer_SYNCDSI_SHIFT))

    #define MotorLockTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << MotorLockTimer_CTRL_MODE_SHIFT))
    #define MotorLockTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << MotorLockTimer_CTRL_MODE_SHIFT))
    #define MotorLockTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << MotorLockTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define MotorLockTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define MotorLockTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define MotorLockTimer_STATUS_TC_INT_MASK_SHIFT        (MotorLockTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define MotorLockTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (MotorLockTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define MotorLockTimer_STATUS_TC                       ((uint8)((uint8)0x01u << MotorLockTimer_STATUS_TC_SHIFT))
    #define MotorLockTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << MotorLockTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define MotorLockTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << MotorLockTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define MotorLockTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << MotorLockTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define MotorLockTimer_STATUS              (* (reg8 *) MotorLockTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define MotorLockTimer_STATUS_MASK         (* (reg8 *) MotorLockTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define MotorLockTimer_STATUS_AUX_CTRL     (* (reg8 *) MotorLockTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define MotorLockTimer_CONTROL             (* (reg8 *) MotorLockTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(MotorLockTimer_Resolution <= 8u) /* 8-bit Timer */
        #define MotorLockTimer_CAPTURE_LSB         (* (reg8 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define MotorLockTimer_CAPTURE_LSB_PTR       ((reg8 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define MotorLockTimer_PERIOD_LSB          (* (reg8 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define MotorLockTimer_PERIOD_LSB_PTR        ((reg8 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define MotorLockTimer_COUNTER_LSB         (* (reg8 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define MotorLockTimer_COUNTER_LSB_PTR       ((reg8 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(MotorLockTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define MotorLockTimer_CAPTURE_LSB         (* (reg16 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define MotorLockTimer_CAPTURE_LSB_PTR       ((reg16 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define MotorLockTimer_PERIOD_LSB          (* (reg16 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define MotorLockTimer_PERIOD_LSB_PTR        ((reg16 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define MotorLockTimer_COUNTER_LSB         (* (reg16 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define MotorLockTimer_COUNTER_LSB_PTR       ((reg16 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define MotorLockTimer_CAPTURE_LSB         (* (reg16 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define MotorLockTimer_CAPTURE_LSB_PTR       ((reg16 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define MotorLockTimer_PERIOD_LSB          (* (reg16 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define MotorLockTimer_PERIOD_LSB_PTR        ((reg16 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define MotorLockTimer_COUNTER_LSB         (* (reg16 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define MotorLockTimer_COUNTER_LSB_PTR       ((reg16 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(MotorLockTimer_Resolution <= 24u)/* 24-bit Timer */
        #define MotorLockTimer_CAPTURE_LSB         (* (reg32 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define MotorLockTimer_CAPTURE_LSB_PTR       ((reg32 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define MotorLockTimer_PERIOD_LSB          (* (reg32 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define MotorLockTimer_PERIOD_LSB_PTR        ((reg32 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define MotorLockTimer_COUNTER_LSB         (* (reg32 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define MotorLockTimer_COUNTER_LSB_PTR       ((reg32 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define MotorLockTimer_CAPTURE_LSB         (* (reg32 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define MotorLockTimer_CAPTURE_LSB_PTR       ((reg32 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define MotorLockTimer_PERIOD_LSB          (* (reg32 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define MotorLockTimer_PERIOD_LSB_PTR        ((reg32 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define MotorLockTimer_COUNTER_LSB         (* (reg32 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define MotorLockTimer_COUNTER_LSB_PTR       ((reg32 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define MotorLockTimer_CAPTURE_LSB         (* (reg32 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define MotorLockTimer_CAPTURE_LSB_PTR       ((reg32 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define MotorLockTimer_PERIOD_LSB          (* (reg32 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define MotorLockTimer_PERIOD_LSB_PTR        ((reg32 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define MotorLockTimer_COUNTER_LSB         (* (reg32 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define MotorLockTimer_COUNTER_LSB_PTR       ((reg32 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define MotorLockTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) MotorLockTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (MotorLockTimer_UsingHWCaptureCounter)
        #define MotorLockTimer_CAP_COUNT              (*(reg8 *) MotorLockTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define MotorLockTimer_CAP_COUNT_PTR          ( (reg8 *) MotorLockTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define MotorLockTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) MotorLockTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define MotorLockTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) MotorLockTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (MotorLockTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define MotorLockTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define MotorLockTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define MotorLockTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define MotorLockTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define MotorLockTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define MotorLockTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << MotorLockTimer_CTRL_INTCNT_SHIFT))
    #define MotorLockTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << MotorLockTimer_CTRL_TRIG_MODE_SHIFT))
    #define MotorLockTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << MotorLockTimer_CTRL_TRIG_EN_SHIFT))
    #define MotorLockTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << MotorLockTimer_CTRL_CAP_MODE_SHIFT))
    #define MotorLockTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << MotorLockTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define MotorLockTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define MotorLockTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define MotorLockTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define MotorLockTimer_STATUS_TC_INT_MASK_SHIFT       MotorLockTimer_STATUS_TC_SHIFT
    #define MotorLockTimer_STATUS_CAPTURE_INT_MASK_SHIFT  MotorLockTimer_STATUS_CAPTURE_SHIFT
    #define MotorLockTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define MotorLockTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define MotorLockTimer_STATUS_FIFOFULL_INT_MASK_SHIFT MotorLockTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define MotorLockTimer_STATUS_TC                      ((uint8)((uint8)0x01u << MotorLockTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define MotorLockTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << MotorLockTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define MotorLockTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << MotorLockTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define MotorLockTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << MotorLockTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define MotorLockTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << MotorLockTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define MotorLockTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << MotorLockTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define MotorLockTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << MotorLockTimer_STATUS_FIFOFULL_SHIFT))

    #define MotorLockTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define MotorLockTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define MotorLockTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define MotorLockTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define MotorLockTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define MotorLockTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_MotorLockTimer_H */


/* [] END OF FILE */
