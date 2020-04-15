/** @file ThreadFunctionality.hpp
 *  @brief Funktionsprototyper for Threadfunctionality-klassen
 *
 * Indeholder prototyperne til Threadfunctionality.cpp, der håndterer
 * kommnukationen mellem trådene i programmet
 *
 *  @author Kristian Lau Jespersen
 *  @author Oskar Vedel
 *  @bug Ingen kendte bugs.
 */

#pragma once
#include "DataBase.hpp"
#include "EDBikeProtocol.hpp"
#include "LockUnit.hpp"
#include "MessageQ.hpp"
#include "RideData.hpp"
#include "SPI.hpp"
#include "SPIprotocol.hpp"
#include "SensorUnit.hpp"
#include "UserInterface.hpp"

class SPIprotocol;
extern SPI           _SPI;
extern lockUnit      _lockUnit;
extern sensorUnit    _sensorUnit;
extern DataBase      _dataBase;
extern RideData      _currentRide;
extern UserInterface _userInterface;

class ThreadFunctionality
{
private:
public:
  /** @brief Dispatcher-funktion, der håndterer indkommende events
   * Disptacher-funktionen håndterer de beskeder, der er modtaget i programmets
   * MessageQueue. Dette gøres ved at switche på det modtagne event, som er
   * defineret af den fælles protokol.
   */
  static void dispatcher(Message *messagePtr, unsigned long ID);

  /** @brief Kører dispatcher-funktionen i et 'receive-handle-delete'-loop
   */
  static void *dispatcherThreadFunc(void *arg);

  static MessageQ        dispatcherMessageQueue;
  static pthread_mutex_t SPI_mutex;
};

/****************************Message children slave
 * related*******************************/
struct liveData : public Message
{
  liveData(int speed, int distance) : speed_(speed), distance_(distance) {}
  virtual ~liveData() {}
  int speed_;
  int distance_;
};

/****************************Message children UI
 * related*******************************/
struct wheelCircumference : public Message
{
  wheelCircumference(string wheelCirc) : wheelCirc_(wheelCirc) {}
  string wheelCirc_;
};

struct userUnlockTry : public Message
{
  userUnlockTry(std::string PIN) : PIN_(PIN) {}
  std::string PIN_;
};

struct userDeleteRide : public Message
{
  userDeleteRide(string rideNum) : rideNum_(rideNum) {}
  string rideNum_;
};
