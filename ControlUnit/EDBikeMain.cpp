// AUTHOR: Oskar Vedel & Kristian Lau Jespersen
/** @file EDBikeMain.cpp
 *  @brief Main-programmet for EDBike
 *
 * Starter de tre tråde UIReceiver, slavePuller og dispatcherThread, som
 * tilsammen håndterer EDBike-funktionaliteten på RPi.
 *
 *  @author Kristian Lau Jespersen
 *  @author Oskar Vedel
 *  @bug Ingen kendte bugs.
 */

#include "threadFunctionality.hpp"

#include <string>

SPI           _SPI(1, 8, 1000000);
lockUnit      _lockUnit(&_SPI);
sensorUnit    _sensorUnit(&_SPI);
DataBase      _dataBase;
RideData      _currentRide;
UserInterface _userInterface;

int main()
{
  thread UIreceiver(&UserInterface::UIReceive, &_userInterface);

  thread slavePuller(&sensorUnit::slavePullerThreadFunc, &_sensorUnit);

  thread dispatcherThread_(&ThreadFunctionality::dispatcherThreadFunc, nullptr);

  while (1)
  {
  }
  return 0;
}
