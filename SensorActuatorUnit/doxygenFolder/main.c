//Author: Jonathan Hartvigsen Juncker, Kristan Lau Jespersen
/** 
*@file main.c
*@brief PSoC main
*
*@author Jonathan Hartvigsen Juncker
*@author Kristian Lau Jespersen
*@bug Ingen kendte bugs.
*/
#include <stdio.h>
#include "project.h"
#include "EDBikeProtocol.h"
#include "lockUnit.h"
#include "SPI.h"
#include "wheelSensor.h"
#include "Accelerometer.h"
#include "UART.h"
#include "bikeState.h"
#include "SPIprotocol.h"

/***********************initial state************************/
 enum bikeState STATE=LOCKED;

/***********************SPI variables************************/
 uint8 rxBuffer[maxMessageLength]={'#','#','#','#'};
 uint8 txBuffer[maxMessageLength]={'#','#','#','#'};
 uint8 txCloneBuffer[maxMessageLength*6];


/***********************UART variables************************/
char8 UART_buffer[16];

/*******************Wheel sensor variables*******************/
int wheel_revolutions = 0;
uint8 speed = 0;
uint8 dist = 0;
double time_temp = 0;
double wheelRadius = 25;
double wheelCirc = 0.00314;

/************************handler declarations*************************/
void handleCommandReceived(uint8* rxBuffer);
void centralDispatcher(uint16 STATE);

/************************handler definitions*************************/
void handleCommandReceived(uint8* rxBuffer)
{
    
//    for (uint32_t i = 0; i < maxMessageLength; i++)
//        {
//       
//        sprintf(UART_buffer,"rx Byte %d: %d \n\r",i,rxBuffer[i]);
//        UART_1_PutString(UART_buffer);
//        }
    
    
    switch (rxBuffer[FIRST_EVENT_INDEX])
    {
        //CASE LOCK
        case USER_LOCK:
        {
            STATE=LOCKING;
            centralDispatcher(STATE);
            break;
        }
        
        //CASE UNLOCK
        case USER_UNLOCK:
        {
            STATE=UNLOCKING;
            centralDispatcher(STATE);
            break;
        }
        case USER_SET_WHEELCIRCUMFERENCE:
        {
            wheelCirc = calcWheelCirc(WheelRadiusToMetres(rxBuffer[FIRST_EVENT_INDEX]));
            break;
        }
        
        default:
        break;
}   
}


void centralDispatcher(uint16 STATE)
{
    switch(STATE)
        {
            case UNLOCKING:
            {
                //UART_1_PutString("\nDispatcher: unlocking bike %d\n");
                unlockBike();
                LED_pin_Write(1);
                loadToSpecificTxBufferIndex(txBuffer,MESSAGE_TYPE_ID_INDEX,EVENT_TRANSMISSION_TO_MASTER);
                loadToSpecificTxBufferIndex(txBuffer,FIRST_EVENT_INDEX,UNLOCKING);
                transferIsReady(txBuffer);
                isr_bike_is_idle_Enable();
                break;
            }
            case UNLOCKED_AND_ACTIVE:
            {
                break;
            }
            case UNLOCKED_AND_IDLE:
            {
                break;
            }
            case UNLOCKED_AND_IDLE_READY_TO_LOCK:
            {
                break;
            }
            case LOCKING:
            {
                //UART_1_PutString("\nDispatcher: locking bike %d\n");
                lockBike();
                LED_pin_Write(0);
                loadToSpecificTxBufferIndex(txBuffer,MESSAGE_TYPE_ID_INDEX,EVENT_TRANSMISSION_TO_MASTER);
                loadToSpecificTxBufferIndex(txBuffer,FIRST_EVENT_INDEX,LOCKING);
                transferIsReady(txBuffer);
                isr_bike_is_idle_Disable();
             
                stopAccelerometerTimer();
                dist=0;
                wheel_revolutions=0;
                
                //pseudo implementation. Actual lock confirm needs to be received from sensor. 
                STATE=LOCKED;
                centralDispatcher(STATE);
                break;
            }
            case LOCKED:
            {
                loadToSpecificTxBufferIndex(txBuffer,MESSAGE_TYPE_ID_INDEX,EVENT_TRANSMISSION_TO_MASTER);
                loadToSpecificTxBufferIndex(txBuffer,FIRST_EVENT_INDEX,LOCKED);
                transferIsReady(txBuffer);
                break;
            }
        }
}


/************************definition of SPI ISR*************************/
CY_ISR(slave_rx_interrupt_handler)         
{
    //UART_1_PutString("SLAVE RX ISR CALLED \n\r");
    receiveSPI(rxBuffer);
    handleCommandReceived(rxBuffer);
    /*
    if (SPI_slave_ReadTxStatus()==SPI_slave_STS_TX_FIFO_EMPTY_SHIFT)
    {
        SPI_slave_PutArray(txBuffer,maxMessageLength);
     }
    */
  
    
    
}

/************************definition of wheel tick ISR*************************/
CY_ISR( isr_wheel_tick_Handler )
{  
    time_temp = WheelTickTimer_ReadCounter();
    resetSpeedTimer();
    wheel_revolutions ++;
    time_temp = 3000 - time_temp;
    
    dist = (uint8)calcDistance(wheel_revolutions, wheelCirc);
    speed = (uint8)calcSpeed(time_temp, wheelCirc);
    


    //debug
    /*
    
    sprintf(UART_buffer,"\n\rtime_temp: %f\n",time_temp);
    UART_1_PutString(UART_buffer);
    
    sprintf(UART_buffer,"\n\rSpeed calc read: %d\n",speed);
    UART_1_PutString(UART_buffer);
    
    sprintf(UART_buffer,"\n\rDist calc read: %d\n",dist);
    UART_1_PutString(UART_buffer);
    
    UART_1_PutString("printing tx buffer before send in wheel tick handler\n\r");
    for (uint32_t i = 0; i < maxMessageLength; i++)
    {
       
        sprintf(UART_buffer,"tx Byte %d: %d \n\r",i,txBuffer[i]);
        UART_1_PutString(UART_buffer);
    }
    */
    
    time_temp = 0;
    
    loadToSpecificTxBufferIndex(txBuffer,MESSAGE_TYPE_ID_INDEX,LIVE_DATA_TRANSMISSION);
    loadToSpecificTxBufferIndex(txBuffer,SPEED_INDEX,speed);
    loadToSpecificTxBufferIndex(txBuffer,DISTANCE_INDEX,dist);
    createParityBits(txBuffer,4);
    transferIsReady(txBuffer);
    
    WheelTickPin_ClearInterrupt();
}
/************************definition of Counter ISR*************************/
CY_ISR( Timer_Isr_BikeIsStopping_handler )
{   
    setSpeedToZero(&speed);
       
    loadToSpecificTxBufferIndex(txBuffer,MESSAGE_TYPE_ID_INDEX,LIVE_DATA_TRANSMISSION);
    loadToSpecificTxBufferIndex(txBuffer,SPEED_INDEX,speed);
    loadToSpecificTxBufferIndex(txBuffer,DISTANCE_INDEX,dist);
    createParityBits(txBuffer,4);
    transferIsReady(txBuffer);

    
    //debug
    
    //UART_1_PutString("\n\rBike is Stopping\n");
    /*
        UART_1_PutString("printing tx buffer before send\n\r");
            for (uint32_t i = 0; i < maxMessageLength; i++)
            {
       
                sprintf(UART_buffer,"tx Byte %d: %d \n\r",i,txBuffer[i]);
                UART_1_PutString(UART_buffer);
                
            }
    
    transferIsReady(txBuffer);
    
    UART_1_PutString("printing tx clone buffer before after transferisready\n\r");
            for (uint32_t i = 0; i < maxMessageLength; i++)
            {
       
                sprintf(UART_buffer,"tx Byte %d: %d \n\r",i,txCloneBuffer[i]);
                UART_1_PutString(UART_buffer);
                
            }
    //    sprintf(UART_buffer,"\n\rSpeed calc read: %d\n",speed);
    //    UART_1_PutString(UART_buffer);
    
    UART_1_PutString("printing tx buffer in bikeisstoppinghandler\n\r");
    for (uint32_t i = 0; i < maxMessageLength; i++)
    {
       
        sprintf(UART_buffer,"tx Byte %d: %d \n\r",i,txBuffer[i]);
        UART_1_PutString(UART_buffer);
    }
    */
    
    WheelTickTimer_ReadStatusRegister();
}

/************************definition of UART ISR*************************/

CY_ISR(UART_rx_interrupt_handler)
{
   uint8_t bytesToRead = UART_1_GetRxBufferSize();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_1_ReadRxData();
        UART_1_WriteTxData(byteReceived); // echo back
        bytesToRead--;
    }
}

/************************Accelerometer interupt routines *********/

CY_ISR(bike_is_idle_handler)
{
    Pin_2_ac_moving_ClearInterrupt();
    isr_bike_is_idle_ClearPending();
      for (uint8_t i = 0; i < 10; i++)           
    {
        LED_pin_Write(1);
        CyDelay(50);
        LED_pin_Write(0);              
        CyDelay(50);
    }
    //UART_1_PutString("\r\n idle handler\n");
    
    startAccelerometerTimer();
    resetAccelerometerTimer();
    Pin_1_ac_idle_ClearInterrupt();
    
}

CY_ISR(bike_is_moving_handler)
{
    LED_pin_Write(1);
    CyDelay(200);
    LED_pin_Write(0);   
    
    //UART_1_PutString("\r\n moving handler\n");
    stopAccelerometerTimer();
    Pin_2_ac_moving_ClearInterrupt();
}

CY_ISR(bike_stopped_handler)
{
    
      for (uint8_t i = 0; i < 10; i++)           
    {
        LED_pin_Write(1);
        CyDelay(200);
        LED_pin_Write(0);              
        CyDelay(200);
    }
    //UART_1_PutString("\r\nMotor Laases\n");
    //lockBike();
   
    STATE=LOCKING;
    centralDispatcher(STATE);
    AccelerometerTimer_ReadStatusRegister();
}

/********************interrupt routine for stopping motorized lock*********************/

CY_ISR(isr_bikelock)
{
    stopLockTimer();
    In_1_Write(0);
    In_2_Write(0);
    EA_Write(0);
    MotorLockTimer_ReadStatusRegister();
}


/************************main*************************/
int main(void)
{
    //indicating start of test program.
    for (uint8_t i = 0; i < 10; i++)           
    {
        LED_pin_Write(1);
        CyDelay(50);
        LED_pin_Write(0);              
        CyDelay(50);
    }
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    initUART();
    initSPI();
    initWheelSensor();
    init_accelerometer();
    initLockUnit();

        while(1)
        {
            //debug
            //CyDelay(900);
            /*
            UART_1_PutString("printing tx buffer in main\n\r");
            for (uint32_t i = 0; i < maxMessageLength; i++)
            {
       
                sprintf(UART_buffer,"tx Byte %d: %d \n\r",i,txBuffer[i]);
                UART_1_PutString(UART_buffer);
                
            }*/
            
            //sprintf(UART_buffer,"size of tx buffer: %d \n\r",SPI_slave_GetTxBufferSize());
            //UART_1_PutString(UART_buffer);
           
            /*
            CyDelay(900);
            loadToSpecificTxBufferIndex(txBuffer,MESSAGE_TYPE_ID_INDEX,LIVE_DATA_TRANSMISSION);
            loadToSpecificTxBufferIndex(txBuffer,SPEED_INDEX,23);
            //transferIsReady(txBuffer);
            
            CyDelay(900);
            loadToSpecificTxBufferIndex(txBuffer,MESSAGE_TYPE_ID_INDEX,LIVE_DATA_TRANSMISSION);
            loadToSpecificTxBufferIndex(txBuffer,SPEED_INDEX,25);
            transferIsReady(txBuffer);
            
            CyDelay(900);
            loadToSpecificTxBufferIndex(txBuffer,MESSAGE_TYPE_ID_INDEX,LIVE_DATA_TRANSMISSION);
            loadToSpecificTxBufferIndex(txBuffer,SPEED_INDEX,13);
            transferIsReady(txBuffer);
            
            CyDelay(900);
            loadToSpecificTxBufferIndex(txBuffer,MESSAGE_TYPE_ID_INDEX,LIVE_DATA_TRANSMISSION);
            loadToSpecificTxBufferIndex(txBuffer,SPEED_INDEX,43);
            transferIsReady(txBuffer);
            */
        }
}



/* [] END OF FILE */
