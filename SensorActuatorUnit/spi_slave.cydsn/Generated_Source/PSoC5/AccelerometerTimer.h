/*******************************************************************************
* File Name: AccelerometerTimer.h
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

#if !defined(CY_TIMER_AccelerometerTimer_H)
#define CY_TIMER_AccelerometerTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 AccelerometerTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define AccelerometerTimer_Resolution                 24u
#define AccelerometerTimer_UsingFixedFunction         0u
#define AccelerometerTimer_UsingHWCaptureCounter      0u
#define AccelerometerTimer_SoftwareCaptureMode        0u
#define AccelerometerTimer_SoftwareTriggerMode        0u
#define AccelerometerTimer_UsingHWEnable              0u
#define AccelerometerTimer_EnableTriggerMode          0u
#define AccelerometerTimer_InterruptOnCaptureCount    0u
#define AccelerometerTimer_RunModeUsed                0u
#define AccelerometerTimer_ControlRegRemoved          0u

#if defined(AccelerometerTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define AccelerometerTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (AccelerometerTimer_UsingFixedFunction)
    #define AccelerometerTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define AccelerometerTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End AccelerometerTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!AccelerometerTimer_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (AccelerometerTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!AccelerometerTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}AccelerometerTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    AccelerometerTimer_Start(void) ;
void    AccelerometerTimer_Stop(void) ;

void    AccelerometerTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   AccelerometerTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define AccelerometerTimer_GetInterruptSource() AccelerometerTimer_ReadStatusRegister()

#if(!AccelerometerTimer_UDB_CONTROL_REG_REMOVED)
    uint8   AccelerometerTimer_ReadControlRegister(void) ;
    void    AccelerometerTimer_WriteControlRegister(uint8 control) ;
#endif /* (!AccelerometerTimer_UDB_CONTROL_REG_REMOVED) */

uint32  AccelerometerTimer_ReadPeriod(void) ;
void    AccelerometerTimer_WritePeriod(uint32 period) ;
uint32  AccelerometerTimer_ReadCounter(void) ;
void    AccelerometerTimer_WriteCounter(uint32 counter) ;
uint32  AccelerometerTimer_ReadCapture(void) ;
void    AccelerometerTimer_SoftwareCapture(void) ;

#if(!AccelerometerTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (AccelerometerTimer_SoftwareCaptureMode)
        void    AccelerometerTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!AccelerometerTimer_UsingFixedFunction) */

    #if (AccelerometerTimer_SoftwareTriggerMode)
        void    AccelerometerTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (AccelerometerTimer_SoftwareTriggerMode) */

    #if (AccelerometerTimer_EnableTriggerMode)
        void    AccelerometerTimer_EnableTrigger(void) ;
        void    AccelerometerTimer_DisableTrigger(void) ;
    #endif /* (AccelerometerTimer_EnableTriggerMode) */


    #if(AccelerometerTimer_InterruptOnCaptureCount)
        void    AccelerometerTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (AccelerometerTimer_InterruptOnCaptureCount) */

    #if (AccelerometerTimer_UsingHWCaptureCounter)
        void    AccelerometerTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   AccelerometerTimer_ReadCaptureCount(void) ;
    #endif /* (AccelerometerTimer_UsingHWCaptureCounter) */

    void AccelerometerTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void AccelerometerTimer_Init(void)          ;
void AccelerometerTimer_Enable(void)        ;
void AccelerometerTimer_SaveConfig(void)    ;
void AccelerometerTimer_RestoreConfig(void) ;
void AccelerometerTimer_Sleep(void)         ;
void AccelerometerTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define AccelerometerTimer__B_TIMER__CM_NONE 0
#define AccelerometerTimer__B_TIMER__CM_RISINGEDGE 1
#define AccelerometerTimer__B_TIMER__CM_FALLINGEDGE 2
#define AccelerometerTimer__B_TIMER__CM_EITHEREDGE 3
#define AccelerometerTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define AccelerometerTimer__B_TIMER__TM_NONE 0x00u
#define AccelerometerTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define AccelerometerTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define AccelerometerTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define AccelerometerTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define AccelerometerTimer_INIT_PERIOD             299999u
#define AccelerometerTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << AccelerometerTimer_CTRL_CAP_MODE_SHIFT))
#define AccelerometerTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << AccelerometerTimer_CTRL_TRIG_MODE_SHIFT))
#if (AccelerometerTimer_UsingFixedFunction)
    #define AccelerometerTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << AccelerometerTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << AccelerometerTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define AccelerometerTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << AccelerometerTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << AccelerometerTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << AccelerometerTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (AccelerometerTimer_UsingFixedFunction) */
#define AccelerometerTimer_INIT_CAPTURE_COUNT      (2u)
#define AccelerometerTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << AccelerometerTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (AccelerometerTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define AccelerometerTimer_STATUS         (*(reg8 *) AccelerometerTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define AccelerometerTimer_STATUS_MASK    (*(reg8 *) AccelerometerTimer_TimerHW__SR0 )
    #define AccelerometerTimer_CONTROL        (*(reg8 *) AccelerometerTimer_TimerHW__CFG0)
    #define AccelerometerTimer_CONTROL2       (*(reg8 *) AccelerometerTimer_TimerHW__CFG1)
    #define AccelerometerTimer_CONTROL2_PTR   ( (reg8 *) AccelerometerTimer_TimerHW__CFG1)
    #define AccelerometerTimer_RT1            (*(reg8 *) AccelerometerTimer_TimerHW__RT1)
    #define AccelerometerTimer_RT1_PTR        ( (reg8 *) AccelerometerTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define AccelerometerTimer_CONTROL3       (*(reg8 *) AccelerometerTimer_TimerHW__CFG2)
        #define AccelerometerTimer_CONTROL3_PTR   ( (reg8 *) AccelerometerTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define AccelerometerTimer_GLOBAL_ENABLE  (*(reg8 *) AccelerometerTimer_TimerHW__PM_ACT_CFG)
    #define AccelerometerTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) AccelerometerTimer_TimerHW__PM_STBY_CFG)

    #define AccelerometerTimer_CAPTURE_LSB         (* (reg16 *) AccelerometerTimer_TimerHW__CAP0 )
    #define AccelerometerTimer_CAPTURE_LSB_PTR       ((reg16 *) AccelerometerTimer_TimerHW__CAP0 )
    #define AccelerometerTimer_PERIOD_LSB          (* (reg16 *) AccelerometerTimer_TimerHW__PER0 )
    #define AccelerometerTimer_PERIOD_LSB_PTR        ((reg16 *) AccelerometerTimer_TimerHW__PER0 )
    #define AccelerometerTimer_COUNTER_LSB         (* (reg16 *) AccelerometerTimer_TimerHW__CNT_CMP0 )
    #define AccelerometerTimer_COUNTER_LSB_PTR       ((reg16 *) AccelerometerTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define AccelerometerTimer_BLOCK_EN_MASK                     AccelerometerTimer_TimerHW__PM_ACT_MSK
    #define AccelerometerTimer_BLOCK_STBY_EN_MASK                AccelerometerTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define AccelerometerTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define AccelerometerTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define AccelerometerTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define AccelerometerTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define AccelerometerTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define AccelerometerTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << AccelerometerTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define AccelerometerTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define AccelerometerTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << AccelerometerTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define AccelerometerTimer_CTRL_MODE_SHIFT                 0x01u
        #define AccelerometerTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << AccelerometerTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define AccelerometerTimer_CTRL_RCOD_SHIFT        0x02u
        #define AccelerometerTimer_CTRL_ENBL_SHIFT        0x00u
        #define AccelerometerTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define AccelerometerTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << AccelerometerTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define AccelerometerTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << AccelerometerTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define AccelerometerTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << AccelerometerTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define AccelerometerTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << AccelerometerTimer_CTRL_RCOD_SHIFT))
        #define AccelerometerTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << AccelerometerTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define AccelerometerTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define AccelerometerTimer_RT1_MASK                        ((uint8)((uint8)0x03u << AccelerometerTimer_RT1_SHIFT))
    #define AccelerometerTimer_SYNC                            ((uint8)((uint8)0x03u << AccelerometerTimer_RT1_SHIFT))
    #define AccelerometerTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define AccelerometerTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << AccelerometerTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define AccelerometerTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << AccelerometerTimer_SYNCDSI_SHIFT))

    #define AccelerometerTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << AccelerometerTimer_CTRL_MODE_SHIFT))
    #define AccelerometerTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << AccelerometerTimer_CTRL_MODE_SHIFT))
    #define AccelerometerTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << AccelerometerTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define AccelerometerTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define AccelerometerTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define AccelerometerTimer_STATUS_TC_INT_MASK_SHIFT        (AccelerometerTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define AccelerometerTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (AccelerometerTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define AccelerometerTimer_STATUS_TC                       ((uint8)((uint8)0x01u << AccelerometerTimer_STATUS_TC_SHIFT))
    #define AccelerometerTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << AccelerometerTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define AccelerometerTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << AccelerometerTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define AccelerometerTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << AccelerometerTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define AccelerometerTimer_STATUS              (* (reg8 *) AccelerometerTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define AccelerometerTimer_STATUS_MASK         (* (reg8 *) AccelerometerTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define AccelerometerTimer_STATUS_AUX_CTRL     (* (reg8 *) AccelerometerTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define AccelerometerTimer_CONTROL             (* (reg8 *) AccelerometerTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(AccelerometerTimer_Resolution <= 8u) /* 8-bit Timer */
        #define AccelerometerTimer_CAPTURE_LSB         (* (reg8 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define AccelerometerTimer_CAPTURE_LSB_PTR       ((reg8 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define AccelerometerTimer_PERIOD_LSB          (* (reg8 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define AccelerometerTimer_PERIOD_LSB_PTR        ((reg8 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define AccelerometerTimer_COUNTER_LSB         (* (reg8 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #define AccelerometerTimer_COUNTER_LSB_PTR       ((reg8 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
    #elif(AccelerometerTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define AccelerometerTimer_CAPTURE_LSB         (* (reg16 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define AccelerometerTimer_CAPTURE_LSB_PTR       ((reg16 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define AccelerometerTimer_PERIOD_LSB          (* (reg16 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define AccelerometerTimer_PERIOD_LSB_PTR        ((reg16 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define AccelerometerTimer_COUNTER_LSB         (* (reg16 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
            #define AccelerometerTimer_COUNTER_LSB_PTR       ((reg16 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define AccelerometerTimer_CAPTURE_LSB         (* (reg16 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__16BIT_F0_REG )
            #define AccelerometerTimer_CAPTURE_LSB_PTR       ((reg16 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__16BIT_F0_REG )
            #define AccelerometerTimer_PERIOD_LSB          (* (reg16 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__16BIT_D0_REG )
            #define AccelerometerTimer_PERIOD_LSB_PTR        ((reg16 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__16BIT_D0_REG )
            #define AccelerometerTimer_COUNTER_LSB         (* (reg16 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__16BIT_A0_REG )
            #define AccelerometerTimer_COUNTER_LSB_PTR       ((reg16 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(AccelerometerTimer_Resolution <= 24u)/* 24-bit Timer */
        #define AccelerometerTimer_CAPTURE_LSB         (* (reg32 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define AccelerometerTimer_CAPTURE_LSB_PTR       ((reg32 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define AccelerometerTimer_PERIOD_LSB          (* (reg32 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define AccelerometerTimer_PERIOD_LSB_PTR        ((reg32 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define AccelerometerTimer_COUNTER_LSB         (* (reg32 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #define AccelerometerTimer_COUNTER_LSB_PTR       ((reg32 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define AccelerometerTimer_CAPTURE_LSB         (* (reg32 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define AccelerometerTimer_CAPTURE_LSB_PTR       ((reg32 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define AccelerometerTimer_PERIOD_LSB          (* (reg32 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define AccelerometerTimer_PERIOD_LSB_PTR        ((reg32 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define AccelerometerTimer_COUNTER_LSB         (* (reg32 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
            #define AccelerometerTimer_COUNTER_LSB_PTR       ((reg32 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define AccelerometerTimer_CAPTURE_LSB         (* (reg32 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__32BIT_F0_REG )
            #define AccelerometerTimer_CAPTURE_LSB_PTR       ((reg32 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__32BIT_F0_REG )
            #define AccelerometerTimer_PERIOD_LSB          (* (reg32 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__32BIT_D0_REG )
            #define AccelerometerTimer_PERIOD_LSB_PTR        ((reg32 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__32BIT_D0_REG )
            #define AccelerometerTimer_COUNTER_LSB         (* (reg32 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__32BIT_A0_REG )
            #define AccelerometerTimer_COUNTER_LSB_PTR       ((reg32 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define AccelerometerTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) AccelerometerTimer_TimerUDB_sT24_timerdp_u0__A0_REG )
    
    #if (AccelerometerTimer_UsingHWCaptureCounter)
        #define AccelerometerTimer_CAP_COUNT              (*(reg8 *) AccelerometerTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define AccelerometerTimer_CAP_COUNT_PTR          ( (reg8 *) AccelerometerTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define AccelerometerTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) AccelerometerTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define AccelerometerTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) AccelerometerTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (AccelerometerTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define AccelerometerTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define AccelerometerTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define AccelerometerTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define AccelerometerTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define AccelerometerTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define AccelerometerTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << AccelerometerTimer_CTRL_INTCNT_SHIFT))
    #define AccelerometerTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << AccelerometerTimer_CTRL_TRIG_MODE_SHIFT))
    #define AccelerometerTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << AccelerometerTimer_CTRL_TRIG_EN_SHIFT))
    #define AccelerometerTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << AccelerometerTimer_CTRL_CAP_MODE_SHIFT))
    #define AccelerometerTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << AccelerometerTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define AccelerometerTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define AccelerometerTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define AccelerometerTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define AccelerometerTimer_STATUS_TC_INT_MASK_SHIFT       AccelerometerTimer_STATUS_TC_SHIFT
    #define AccelerometerTimer_STATUS_CAPTURE_INT_MASK_SHIFT  AccelerometerTimer_STATUS_CAPTURE_SHIFT
    #define AccelerometerTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define AccelerometerTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define AccelerometerTimer_STATUS_FIFOFULL_INT_MASK_SHIFT AccelerometerTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define AccelerometerTimer_STATUS_TC                      ((uint8)((uint8)0x01u << AccelerometerTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define AccelerometerTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << AccelerometerTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define AccelerometerTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << AccelerometerTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define AccelerometerTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << AccelerometerTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define AccelerometerTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << AccelerometerTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define AccelerometerTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << AccelerometerTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define AccelerometerTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << AccelerometerTimer_STATUS_FIFOFULL_SHIFT))

    #define AccelerometerTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define AccelerometerTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define AccelerometerTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define AccelerometerTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define AccelerometerTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define AccelerometerTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_AccelerometerTimer_H */


/* [] END OF FILE */
