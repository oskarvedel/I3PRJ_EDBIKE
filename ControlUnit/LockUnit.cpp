/** @file xxx.xxx
 *  @brief kort beskrivelse (på én linje)
 * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
 * lang beskrivelse, lang beskrivelse
 *  @author forfatter1
 *  @author forfatter2
 *  @bug Ingen kendte bugs
 */
#include "LockUnit.hpp"

lockUnit::lockUnit(serialUnit *serialUnit) : serialUnit_(serialUnit) {}

lockUnit::~lockUnit() {}

bool lockUnit::lockBike()
{
  pthread_mutex_lock(&ThreadFunctionality::SPI_mutex);
  std::cout << "lockBike called" << std::endl;
  // serialUnit_->setValueOfTxBuffer(EVENT_TRANSMISSION_FROM_MASTER,USER_LOCK,'#','#');
  // serialUnit_->setValueOfTxBuffer('E','L','#','#');
  serialUnit_->setValueOfTxBuffer("EL##");
  serialUnit_->printTxToScreen();
  serialUnit_->readAndWrite(4, 1);

  // check for return from PSoc
  serialUnit_->setValueOfTxBuffer(
      "####"); // # is dummy value. Only a read is desired
  uint8_t bufferReceived[4];
  usleep(5000);
  serialUnit_->readAndWrite(4, 1);
  std::cout << std::endl;
  serialUnit_->getValueOfRxBuffer(bufferReceived);
  pthread_mutex_unlock(&ThreadFunctionality::SPI_mutex);
  if (bufferReceived[MESSAGE_TYPE_ID_INDEX] == EVENT_TRANSMISSION_TO_MASTER &&
      bufferReceived[FIRST_EVENT_INDEX] ==
          LOCKING) // locking response from slave
  {
    return true;
  }
  return false;
}

bool lockUnit::unlockBike()
{
  pthread_mutex_lock(&ThreadFunctionality::SPI_mutex);
  std::cout << "unlockBike called" << std::endl;
  // serialUnit_->setValueOfTxBuffer(EVENT_TRANSMISSION_FROM_MASTER,USER_UNLOCK,'#','#');
  // serialUnit_->setValueOfTxBuffer('E','U','#','#');
  serialUnit_->setValueOfTxBuffer("EU##");
  serialUnit_->printTxToScreen();
  serialUnit_->readAndWrite(4, 1);

  // check for return from PSoc
  serialUnit_->setValueOfTxBuffer(
      "####"); //"#" is dummy value. Only a read is desired
  uint8_t bufferReceived[4];
  usleep(5000);
  serialUnit_->readAndWrite(4, 1);
  std::cout << std::endl;
  serialUnit_->getValueOfRxBuffer(bufferReceived);
  pthread_mutex_unlock(&ThreadFunctionality::SPI_mutex);
  if (bufferReceived[MESSAGE_TYPE_ID_INDEX] == EVENT_TRANSMISSION_TO_MASTER &&
      bufferReceived[FIRST_EVENT_INDEX] ==
          UNLOCKING) //"u" unlocking response from slave
  {
    return true;
  }
  return false;
}