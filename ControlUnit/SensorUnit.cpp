/** @file xxx.xxx
 *  @brief kort beskrivelse (på én linje)
 * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
 * lang beskrivelse, lang beskrivelse
 *  @author forfatter1
 *  @author forfatter2
 *  @bug Ingen kendte bugs
 */

#include "SensorUnit.hpp"

sensorUnit::sensorUnit(serialUnit* serialUnit):serialUnit_(serialUnit), latestLiveData_(new liveData(0,0))
{
    
}

sensorUnit::~sensorUnit()
{
}

void sensorUnit::pull(uint8_t* retrieveBuffer)
{
    pthread_mutex_lock(&ThreadFunctionality::SPI_mutex);
    serialUnit_->setValueOfTxBuffer("####");
    serialUnit_->readAndWrite(4,1);
    serialUnit_->getValueOfRxBuffer(retrieveBuffer);
    serialUnit_->printRxToScreen();
    pthread_mutex_unlock(&ThreadFunctionality::SPI_mutex);
}


/****************************************************************************************
Function that pushes to dispatcher messageQueue after evaluating data received from slave.
Function is used in slavePuller thread
*****************************************************************************************/
void sensorUnit::slavePullerToDispatcher(uint8_t*  bufferReceived)
{
    switch (bufferReceived[MESSAGE_TYPE_ID_INDEX])
    {
        case LOCKED:
        {
            ThreadFunctionality::dispatcherMessageQueue.send(LOCKED);
            break;
        }    
    
        case UNLOCKED_AND_IDLE_READY_TO_LOCK:
        {
            ThreadFunctionality::dispatcherMessageQueue.send(UNLOCKED_AND_IDLE_READY_TO_LOCK);
            break;
        }    
    
        case LIVE_DATA_TRANSMISSION:
        {
            uint8_t speed;
            uint8_t distance;
            if((SPIprotocol::errorCheckWithOddParity(bufferReceived,4))==true)
            {
                SPIprotocol::extractFromBuffer(speed,distance,bufferReceived);
                ThreadFunctionality::dispatcherMessageQueue.send(LIVE_DATA_TRANSMISSION,new liveData(speed,distance));
                latestLiveData_->speed_=speed;
                latestLiveData_->distance_=distance;
            }
            else if ((SPIprotocol::errorCheckWithOddParity(bufferReceived,4))==false)
            {
                std::cout<<"PARITY ERROR"<<endl;
                ThreadFunctionality::dispatcherMessageQueue.send(LIVE_DATA_TRANSMISSION,new liveData(latestLiveData_->speed_,latestLiveData_->distance_));
            }
            
            
            break;
        }

        default:
        {
            break;
        }
    }
}


void sensorUnit::slavePullerThreadFunc()
{
    uint8_t bufferReceived[4];
    while(1)
    {
        sleep(1);
        this->pull(bufferReceived);
        this->slavePullerToDispatcher(bufferReceived);
    }
}



int sensorUnit::setWheelCirc(int wheelCircInCentiMeters)
{
    pthread_mutex_lock(&ThreadFunctionality::SPI_mutex);
    serialUnit_->setValueOfTxBuffer(EVENT_TRANSMISSION_FROM_MASTER,USER_SET_WHEELCIRCUMFERENCE,wheelCircInCentiMeters,'#');
    serialUnit_->readAndWrite(4,1);
    pthread_mutex_unlock(&ThreadFunctionality::SPI_mutex);
    return 1;
}