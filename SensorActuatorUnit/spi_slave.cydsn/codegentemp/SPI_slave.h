/*******************************************************************************
* File Name: SPI_slave.h
* Version 2.70
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the SPI Slave Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIS_SPI_slave_H)
#define CY_SPIS_SPI_slave_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define SPI_slave_DATA_WIDTH                  (8u)
#define SPI_slave_INTERNAL_TX_INT_ENABLED     (1u)
#define SPI_slave_INTERNAL_RX_INT_ENABLED     (0u)
#define SPI_slave_MODE_USE_ZERO               (0u)
#define SPI_slave_BIDIRECTIONAL_MODE          (0u)
#define SPI_slave_MODE                        (2u)

#define SPI_slave_FIFO_SIZE                  (4u)
/* Internal interrupt handling */
#define SPI_slave_TX_BUFFER_SIZE             (24u)
#define SPI_slave_RX_BUFFER_SIZE             (4u)
#define SPI_slave_INTERNAL_TX_INT_ENABLED    (1u)
#define SPI_slave_INTERNAL_RX_INT_ENABLED    (0u)

#define SPI_slave_TX_SOFTWARE_BUF_ENABLED    ((0u != SPI_slave_INTERNAL_TX_INT_ENABLED) && \
                                                     (SPI_slave_TX_BUFFER_SIZE > SPI_slave_FIFO_SIZE))

#define SPI_slave_RX_SOFTWARE_BUF_ENABLED    ((0u != SPI_slave_INTERNAL_RX_INT_ENABLED) && \
                                                     (SPI_slave_RX_BUFFER_SIZE > SPI_slave_FIFO_SIZE))


/***************************************
*        Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
    uint8 cntrPeriod;
} SPI_slave_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  SPI_slave_Init(void) ;
void  SPI_slave_Enable(void) ;
void  SPI_slave_Start(void) ;
void  SPI_slave_Stop(void) ;
void  SPI_slave_EnableTxInt(void) ;
void  SPI_slave_EnableRxInt(void) ;
void  SPI_slave_DisableTxInt(void) ;
void  SPI_slave_DisableRxInt(void) ;
void  SPI_slave_SetTxInterruptMode(uint8 intSrc) ;
void  SPI_slave_SetRxInterruptMode(uint8 intSrc) ;
uint8 SPI_slave_ReadTxStatus(void) ;
uint8 SPI_slave_ReadRxStatus(void) ;
void  SPI_slave_WriteTxData(uint8 txData);

#if(SPI_slave_MODE_USE_ZERO != 0u)
    void  SPI_slave_WriteTxDataZero(uint8 txDataByte) \
                                              ;
#endif /* (SPI_slave_MODE_USE_ZERO != 0u) */

uint8 SPI_slave_ReadRxData(void) ;
uint8 SPI_slave_GetRxBufferSize(void) ;
uint8 SPI_slave_GetTxBufferSize(void) ;
void  SPI_slave_ClearRxBuffer(void) ;
void  SPI_slave_ClearTxBuffer(void) ;

#if (SPI_slave_BIDIRECTIONAL_MODE != 0u)
    void  SPI_slave_TxEnable(void) ;
    void  SPI_slave_TxDisable(void) ;
#endif /* SPI_slave_BIDIRECTIONAL_MODE != 0u */

void  SPI_slave_PutArray(const uint8 buffer[], uint8 byteCount) ;
void  SPI_slave_ClearFIFO(void) ;
void  SPI_slave_Sleep(void) ;
void  SPI_slave_Wakeup(void) ;
void  SPI_slave_SaveConfig(void) ;
void  SPI_slave_RestoreConfig(void) ;

/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPI_slave) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    SPI_slave_CyBtldrCommStart(void) CYSMALL ;
    void    SPI_slave_CyBtldrCommStop(void) CYSMALL ;
    void    SPI_slave_CyBtldrCommReset(void) CYSMALL ;
    cystatus SPI_slave_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus SPI_slave_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPI_slave)
        #define CyBtldrCommStart    SPI_slave_CyBtldrCommStart
        #define CyBtldrCommStop     SPI_slave_CyBtldrCommStop
        #define CyBtldrCommReset    SPI_slave_CyBtldrCommReset
        #define CyBtldrCommWrite    SPI_slave_CyBtldrCommWrite
        #define CyBtldrCommRead     SPI_slave_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPI_slave) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define SPI_slave_BYTE2BYTE_TIME_OUT (1u)

#endif /* (CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPI_slave) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */


CY_ISR_PROTO(SPI_slave_TX_ISR);
CY_ISR_PROTO(SPI_slave_RX_ISR);

/* Macros for getting software status of SPIS Statusi Register */
#define SPI_slave_GET_STATUS_TX(swTxSts) ( (uint8)(SPI_slave_TX_STATUS_REG | \
                                                       ((swTxSts) & SPI_slave_STS_CLR_ON_RD_BYTES_MASK)) )
#define SPI_slave_GET_STATUS_RX(swRxSts) ( (uint8)(SPI_slave_RX_STATUS_REG | \
                                                       ((swRxSts) & SPI_slave_STS_CLR_ON_RD_BYTES_MASK)) )


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 SPI_slave_initVar;


/***************************************
*           API Constants
***************************************/

#define SPI_slave_TX_ISR_NUMBER     ((uint8)SPI_slave_TxInternalInterrupt__INTC_NUMBER)
#define SPI_slave_RX_ISR_NUMBER     ((uint8)SPI_slave_RxInternalInterrupt__INTC_NUMBER)
#define SPI_slave_TX_ISR_PRIORITY   ((uint8)SPI_slave_TxInternalInterrupt__INTC_PRIOR_NUM)
#define SPI_slave_RX_ISR_PRIORITY   ((uint8)SPI_slave_RxInternalInterrupt__INTC_PRIOR_NUM)


/***************************************
*    Initial Parameter Constants
***************************************/

#define SPI_slave_INT_ON_SPI_DONE    (uint8)(0u << SPI_slave_STS_SPI_DONE_SHIFT)
#define SPI_slave_INT_ON_TX_EMPTY    (uint8)(0u << SPI_slave_STS_TX_FIFO_EMPTY_SHIFT)
#define SPI_slave_INT_ON_TX_NOT_FULL (uint8)(1u << SPI_slave_STS_TX_FIFO_NOT_FULL_SHIFT)
#define SPI_slave_INT_ON_BYTE_COMP   (uint8)(0u << SPI_slave_STS_BYTE_COMPLETE_SHIFT)

#define SPI_slave_TX_INIT_INTERRUPTS_MASK  (SPI_slave_INT_ON_SPI_DONE | \
                                            SPI_slave_INT_ON_TX_EMPTY | SPI_slave_INT_ON_TX_NOT_FULL | \
                                            SPI_slave_INT_ON_BYTE_COMP)

#define SPI_slave_INT_ON_RX_EMPTY     (uint8)(0u << SPI_slave_STS_RX_FIFO_EMPTY_SHIFT)
#define SPI_slave_INT_ON_RX_NOT_EMPTY (uint8)(0u << SPI_slave_STS_RX_FIFO_NOT_EMPTY_SHIFT)
#define SPI_slave_INT_ON_RX_OVER      (uint8)(0u << SPI_slave_STS_RX_FIFO_OVERRUN_SHIFT)
#define SPI_slave_INT_ON_RX_FULL      (uint8)(1u << SPI_slave_STS_RX_FIFO_FULL_SHIFT)

#define SPI_slave_RX_INIT_INTERRUPTS_MASK (SPI_slave_INT_ON_RX_EMPTY | \
                                            SPI_slave_INT_ON_RX_NOT_EMPTY | SPI_slave_INT_ON_RX_OVER | \
                                            SPI_slave_INT_ON_RX_FULL)

#define SPI_slave_BITCTR_INIT           (SPI_slave_DATA_WIDTH - 1u)

#define SPI_slave__MODE_00 0
#define SPI_slave__MODE_01 1
#define SPI_slave__MODE_10 2
#define SPI_slave__MODE_11 3


#define SPI_slave_TX_BUFFER_SIZE         (24u)
#define SPI_slave_RX_BUFFER_SIZE         (4u)

/* Following definitions are for version Compatibility, they are obsolete.
*  Please do not use it in new projects
*/
#define SPI_slave_INIT_INTERRUPTS_MASK  (SPI_slave_INT_ON_SPI_DONE | SPI_slave_INT_ON_TX_EMPTY | \
                                            SPI_slave_INT_ON_TX_NOT_FULL | SPI_slave_INT_ON_RX_EMPTY | \
                                            SPI_slave_INT_ON_RX_NOT_EMPTY | SPI_slave_INT_ON_RX_OVER | \
                                            SPI_slave_INT_ON_BYTE_COMP)


/***************************************
*             Registers
***************************************/
#if(CY_PSOC3 || CY_PSOC5)
    #define SPI_slave_TXDATA_ZERO_REG          (* (reg8  *) \
            SPI_slave_BSPIS_sR8_Dp_u0__A0_REG)

    #define SPI_slave_TXDATA_ZERO_PTR           (  (reg8  *) \
            SPI_slave_BSPIS_sR8_Dp_u0__A0_REG)

    #define SPI_slave_RXDATA_ZERO_REG           (* (reg8  *) \
            SPI_slave_BSPIS_sR8_Dp_u0__A0_REG)

    #define SPI_slave_RXDATA_ZERO_PTR           (  (reg8  *) \
            SPI_slave_BSPIS_sR8_Dp_u0__A0_REG)

    #define SPI_slave_TXDATA_REG                (* (reg8  *) \
            SPI_slave_BSPIS_sR8_Dp_u0__F0_REG)

    #define SPI_slave_TXDATA_PTR                (  (reg8  *) \
            SPI_slave_BSPIS_sR8_Dp_u0__F0_REG)

    #define SPI_slave_RXDATA_REG                (* (reg8  *) \
            SPI_slave_BSPIS_sR8_Dp_u0__F1_REG)

    #define SPI_slave_RXDATA_PTR                (  (reg8  *) \
            SPI_slave_BSPIS_sR8_Dp_u0__F1_REG)
#else
    #if(SPI_slave_DATA_WIDTH <= 8u) /* 8bit - SPIS */
        #define SPI_slave_TXDATA_ZERO_REG           (* (reg8 *) \
                SPI_slave_BSPIS_sR8_Dp_u0__A0_REG)

        #define SPI_slave_TXDATA_ZERO_PTR           (  (reg8  *) \
                SPI_slave_BSPIS_sR8_Dp_u0__A0_REG)

        #define SPI_slave_RXDATA_ZERO_REG           (* (reg8  *) \
                SPI_slave_BSPIS_sR8_Dp_u0__A0_REG)

        #define SPI_slave_RXDATA_ZERO_PTR           (  (reg8 *) \
                SPI_slave_BSPIS_sR8_Dp_u0__A0_REG)

        #define SPI_slave_TXDATA_REG                (* (reg8  *) \
                SPI_slave_BSPIS_sR8_Dp_u0__F0_REG)

        #define SPI_slave_TXDATA_PTR                (  (reg8  *) \
                SPI_slave_BSPIS_sR8_Dp_u0__F0_REG)

        #define SPI_slave_RXDATA_REG                (* (reg8  *) \
                SPI_slave_BSPIS_sR8_Dp_u0__F1_REG)

        #define SPI_slave_RXDATA_PTR                (  (reg8  *) \
                SPI_slave_BSPIS_sR8_Dp_u0__F1_REG)
    #else /* 16bit - SPIS */
        #define SPI_slave_TXDATA_ZERO_REG           (* (reg16  *) \
                SPI_slave_BSPIS_sR8_Dp_u0__16BIT_A0_REG)

        #define SPI_slave_TXDATA_ZERO_PTR           (  (reg16  *) \
                SPI_slave_BSPIS_sR8_Dp_u0__16BIT_A0_REG)

        #define SPI_slave_RXDATA_ZERO_REG           (* (reg16  *) \
                SPI_slave_BSPIS_sR8_Dp_u0__16BIT_A0_REG)

        #define SPI_slave_RXDATA_ZERO_PTR           (  (reg16  *) \
                SPI_slave_BSPIS_sR8_Dp_u0__16BIT_A0_REG)

        #define SPI_slave_TXDATA_REG                (* (reg16  *) \
                SPI_slave_BSPIS_sR8_Dp_u0__16BIT_F0_REG)

        #define SPI_slave_TXDATA_PTR                (  (reg16  *) \
                SPI_slave_BSPIS_sR8_Dp_u0__16BIT_F0_REG)

        #define SPI_slave_RXDATA_REG                (* (reg16  *) \
                SPI_slave_BSPIS_sR8_Dp_u0__16BIT_F1_REG)

        #define SPI_slave_RXDATA_PTR                (  (reg16 *) \
                SPI_slave_BSPIS_sR8_Dp_u0__16BIT_F1_REG)
    #endif /* (SPI_slave_DATA_WIDTH <= 8u) */
#endif     /* (CY_PSOC3 || CY_PSOC5) */

#define SPI_slave_TX_AUX_CONTROL_DP0_REG       (* (reg8 *) \
        SPI_slave_BSPIS_sR8_Dp_u0__DP_AUX_CTL_REG)
#define SPI_slave_TX_AUX_CONTROL_DP0_PTR       (  (reg8 *) \
        SPI_slave_BSPIS_sR8_Dp_u0__DP_AUX_CTL_REG)

#define SPI_slave_RX_AUX_CONTROL_DP0_REG       (* (reg8 *) \
        SPI_slave_BSPIS_sR8_Dp_u0__DP_AUX_CTL_REG)
#define SPI_slave_RX_AUX_CONTROL_DP0_PTR       (  (reg8 *) \
        SPI_slave_BSPIS_sR8_Dp_u0__DP_AUX_CTL_REG)

#if(SPI_slave_DATA_WIDTH > 8u)

    #define SPI_slave_TX_AUX_CONTROL_DP1_REG   (* (reg8 *) \
            SPI_slave_BSPIS_sR8_Dp_u1__DP_AUX_CTL_REG)
    #define SPI_slave_TX_AUX_CONTROL_DP1_PTR   (  (reg8 *) \
            SPI_slave_BSPIS_sR8_Dp_u1__DP_AUX_CTL_REG)

    #define SPI_slave_RX_AUX_CONTROL_DP1_REG   (* (reg8 *) \
            SPI_slave_BSPIS_sR8_Dp_u1__DP_AUX_CTL_REG)
    #define SPI_slave_RX_AUX_CONTROL_DP1_PTR   (  (reg8 *) \
            SPI_slave_BSPIS_sR8_Dp_u1__DP_AUX_CTL_REG)

#endif /* SPI_slave_DATA_WIDTH > 8u */


#define SPI_slave_COUNTER_PERIOD_REG    (* (reg8 *) \
        SPI_slave_BSPIS_BitCounter__PERIOD_REG)
#define SPI_slave_COUNTER_PERIOD_PTR    (  (reg8 *) \
        SPI_slave_BSPIS_BitCounter__PERIOD_REG)

#define SPI_slave_TX_STATUS_MASK_REG    (* (reg8 *) \
        SPI_slave_BSPIS_TxStsReg__MASK_REG)
#define SPI_slave_TX_STATUS_MASK_PTR    (  (reg8 *) \
        SPI_slave_BSPIS_TxStsReg__MASK_REG)

#define SPI_slave_RX_STATUS_MASK_REG    (* (reg8 *) \
        SPI_slave_BSPIS_RxStsReg__MASK_REG)
#define SPI_slave_RX_STATUS_MASK_PTR    (  (reg8 *) \
        SPI_slave_BSPIS_RxStsReg__MASK_REG)

#define SPI_slave_ONE_REG               (* (reg8 *) \
        SPI_slave_BSPIS_SPISlave_dpCounter_u0__D1_REG)
#define SPI_slave_ONE_PTR               (  (reg8 *) \
        SPI_slave_BSPIS_dpCounter_u0__D1_REG)

#define SPI_slave_TX_STATUS_REG         (* (reg8 *) \
        SPI_slave_BSPIS_TxStsReg__STATUS_REG)
#define SPI_slave_TX_STATUS_PTR         (  (reg8 *) \
        SPI_slave_BSPIS__TxStsReg__STATUS_REG)

#define SPI_slave_RX_STATUS_REG         (* (reg8 *) \
        SPI_slave_BSPIS_RxStsReg__STATUS_REG)
#define SPI_slave_RX_STATUS_PTR         (  (reg8 *) \
        SPI_slave_BSPIS_RxStsReg__STATUS_REG)

#define SPI_slave_COUNTER_CONTROL_REG   (* (reg8 *) \
        SPI_slave_BSPIS_BitCounter__CONTROL_AUX_CTL_REG)
#define SPI_slave_COUNTER_CONTROL_PTR   (  (reg8 *) \
        SPI_slave_BSPIS_BitCounter__CONTROL_AUX_CTL_REG)

#define SPI_slave_TX_STATUS_ACTL_REG    (* (reg8 *) \
        SPI_slave_BSPIS_TxStsReg__STATUS_AUX_CTL_REG)
#define SPI_slave_TX_STATUS_ACTL_PTR    (  (reg8 *) \
        SPI_slave_TX_BSPIS_TxStsReg__STATUS_AUX_CTL_REG)

#define SPI_slave_RX_STATUS_ACTL_REG    (* (reg8 *) \
        SPI_slave_BSPIS_RxStsReg__STATUS_AUX_CTL_REG)
#define SPI_slave_RX_STATUS_ACTL_PTR    (  (reg8 *) \
        SPI_slave_RX_BSPIS_RxStsReg__STATUS_AUX_CTL_REG)

#if(SPI_slave_BIDIRECTIONAL_MODE)

    #define SPI_slave_CONTROL_REG       (* (reg8 *) \
   SPI_slave_BSPIS_SyncCtl_CtrlReg__CONTROL_REG)
    #define SPI_slave_CONTROL_PTR       (  (reg8 *) \
   SPI_slave_BSPIS_SyncCtl_CtrlReg__CONTROL_REG)

#endif /* SPI_slave_BIDIRECTIONAL_MODE */


/***************************************
*       Register Constants
***************************************/

/* Status Register Definitions */
#define SPI_slave_STS_SPI_DONE_SHIFT             (0x00u)
#define SPI_slave_STS_TX_FIFO_NOT_FULL_SHIFT     (0x01u)
#define SPI_slave_STS_TX_FIFO_EMPTY_SHIFT        (0x02u)
#define SPI_slave_STS_RX_FIFO_NOT_EMPTY_SHIFT    (0x03u)
#define SPI_slave_STS_RX_FIFO_EMPTY_SHIFT        (0x04u)
#define SPI_slave_STS_RX_FIFO_OVERRUN_SHIFT      (0x05u)
#define SPI_slave_STS_RX_FIFO_FULL_SHIFT         (0x06u)
#define SPI_slave_STS_BYTE_COMPLETE_SHIFT        (0x06u)

#define SPI_slave_STS_SPI_DONE                   ((uint8)(0x01u << SPI_slave_STS_SPI_DONE_SHIFT))
#define SPI_slave_STS_TX_FIFO_EMPTY              ((uint8)(0x01u << SPI_slave_STS_TX_FIFO_EMPTY_SHIFT))
#define SPI_slave_STS_TX_FIFO_NOT_FULL           ((uint8)(0x01u << SPI_slave_STS_TX_FIFO_NOT_FULL_SHIFT))
#define SPI_slave_STS_RX_FIFO_EMPTY              ((uint8)(0x01u << SPI_slave_STS_RX_FIFO_EMPTY_SHIFT))
#define SPI_slave_STS_RX_FIFO_NOT_EMPTY          ((uint8)(0x01u << SPI_slave_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define SPI_slave_STS_RX_FIFO_OVERRUN            ((uint8)(0x01u << SPI_slave_STS_RX_FIFO_OVERRUN_SHIFT))
#define SPI_slave_STS_RX_FIFO_FULL               ((uint8)(0x01u << SPI_slave_STS_RX_FIFO_FULL_SHIFT))
#define SPI_slave_STS_BYTE_COMPLETE              ((uint8)(0x01u << SPI_slave_STS_BYTE_COMPLETE_SHIFT))

#define SPI_slave_STS_CLR_ON_RD_BYTES_MASK       (0x61u)

/* StatusI Register Interrupt Enable Control Bits */
/* As defined by the Register map for the AUX Control Register */
#define SPI_slave_INT_ENABLE                     (0x10u)
#define SPI_slave_TX_FIFO_CLR    (0x01u) /* F0 - TX FIFO */
#define SPI_slave_RX_FIFO_CLR    (0x02u) /* F1 - RX FIFO */
#define SPI_slave_FIFO_CLR       (SPI_slave_TX_FIFO_CLR | SPI_slave_RX_FIFO_CLR)

/* Bit Counter (7-bit) Control Register Bit Definitions */
/* As defined by the Register map for the AUX Control Register */
#define SPI_slave_CNTR_ENABLE                    (0x20u)

/* Bi-Directional mode control bit */
#define SPI_slave_CTRL_TX_SIGNAL_EN              (0x01u)

/* Datapath Auxillary Control Register definitions */
#define SPI_slave_AUX_CTRL_FIFO0_CLR             (0x00u)
#define SPI_slave_AUX_CTRL_FIFO1_CLR             (0x00u)
#define SPI_slave_AUX_CTRL_FIFO0_LVL             (0x00u)
#define SPI_slave_AUX_CTRL_FIFO1_LVL             (0x00u)
#define SPI_slave_STATUS_ACTL_INT_EN_MASK        (0x10u)

/* Component disabled */
#define SPI_slave_DISABLED   (0u)

/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define SPI_slave_TXDATA_ZERO               (SPI_slave_TXDATA_ZERO_REG)
#define SPI_slave_TXDATA                    (SPI_slave_TXDATA_REG)
#define SPI_slave_RXDATA                    (SPI_slave_RXDATA_REG)
#define SPI_slave_MISO_AUX_CONTROLDP0       (SPI_slave_MISO_AUX_CTRL_DP0_REG)
#define SPI_slave_MOSI_AUX_CONTROLDP0       (SPI_slave_MOSI_AUX_CTRL_DP0_REG)
#define SPI_slave_TXBUFFERREAD              (SPI_slave_txBufferRead)
#define SPI_slave_TXBUFFERWRITE             (SPI_slave_txBufferWrite)
#define SPI_slave_RXBUFFERREAD              (SPI_slave_rxBufferRead)
#define SPI_slave_RXBUFFERWRITE             (SPI_slave_rxBufferWrite)

#if(SPI_slave_DATA_WIDTH > 8u)

    #define SPI_slave_MISO_AUX_CONTROLDP1   (SPI_slave_MISO_AUX_CTRL_DP1_REG)
    #define SPI_slave_MOSI_AUX_CONTROLDP1   (SPI_slave_MOSI_AUX_CTRL_DP0_REG)

#endif /* SPI_slave_DATA_WIDTH > 8u */

#define SPI_slave_COUNTER_PERIOD            (SPI_slave_COUNTER_PERIOD_REG)
#define SPI_slave_COUNTER_CONTROL           (SPI_slave_COUNTER_CONTROL_REG)
#define SPI_slave_ONE                       (SPI_slave_ONE_REG)
#define SPI_slave_STATUS                    (SPI_slave_TX_STATUS_REG)
#define SPI_slave_STATUS_MASK               (SPI_slave_TX_STATUS_MASK_REG)
#define SPI_slave_STATUS_ACTL               (SPI_slave_TX_STATUS_ACTL_REG)

#define SPI_slave_WriteByte      (SPI_slave_WriteTxData)
#define SPI_slave_ReadByte       (SPI_slave_ReadRxData)
#define SPI_slave_WriteByteZero  (SPI_slave_WriteTxDataZero)
void  SPI_slave_SetInterruptMode(uint8 intSrc) ;
uint8 SPI_slave_ReadStatus(void) ;
void  SPI_slave_EnableInt(void) ;
void  SPI_slave_DisableInt(void) ;

#define SPI_slave_STS_TX_BUF_NOT_FULL_SHIFT      (0x01u)
#define SPI_slave_STS_TX_BUF_FULL_SHIFT          (0x02u)
#define SPI_slave_STS_RX_BUF_NOT_EMPTY_SHIFT     (0x03u)
#define SPI_slave_STS_RX_BUF_EMPTY_SHIFT         (0x04u)
#define SPI_slave_STS_RX_BUF_OVERRUN_SHIFT       (0x05u)

#define SPI_slave_STS_TX_BUF_NOT_FULL            ((uint8)(0x01u << SPI_slave_STS_TX_BUF_NOT_FULL_SHIFT))
#define SPI_slave_STS_TX_BUF_FULL                ((uint8)(0x01u << SPI_slave_STS_TX_BUF_FULL_SHIFT))
#define SPI_slave_STS_RX_BUF_NOT_EMPTY           ((uint8)(0x01u << SPI_slave_STS_RX_BUF_NOT_EMPTY_SHIFT))
#define SPI_slave_STS_RX_BUF_EMPTY               ((uint8)(0x01u << SPI_slave_STS_RX_BUF_EMPTY_SHIFT))
#define SPI_slave_STS_RX_BUF_OVERRUN             ((uint8)(0x01u << SPI_slave_STS_RX_BUF_OVERRUN_SHIFT))

#define SPI_slave_DataWidth                  (SPI_slave_DATA_WIDTH)
#define SPI_slave_InternalClockUsed          (SPI_slave_INTERNAL_CLOCK)
#define SPI_slave_InternalTxInterruptEnabled (SPI_slave_INTERNAL_TX_INT_ENABLED)
#define SPI_slave_InternalRxInterruptEnabled (SPI_slave_INTERNAL_RX_INT_ENABLED)
#define SPI_slave_ModeUseZero                (SPI_slave_MODE_USE_ZERO)
#define SPI_slave_BidirectionalMode          (SPI_slave_BIDIRECTIONAL_MODE)
#define SPI_slave_Mode                       (SPI_slave_MODE)
#define SPI_slave_DATAWIDHT                  (SPI_slave_DATA_WIDTH)
#define SPI_slave_InternalInterruptEnabled   (0u)

#define SPI_slave_TXBUFFERSIZE   (SPI_slave_TX_BUFFER_SIZE)
#define SPI_slave_RXBUFFERSIZE   (SPI_slave_RX_BUFFER_SIZE)

#define SPI_slave_TXBUFFER       SPI_slave_txBuffer
#define SPI_slave_RXBUFFER       SPI_slave_rxBuffer

#endif  /* CY_SPIS_SPI_slave_H */

/* [] END OF FILE */
