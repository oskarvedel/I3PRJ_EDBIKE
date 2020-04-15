/** @file ThreadFunctionality.cpp
 *  @brief Implementation af ThreadFunctionality
 *
 * Indeholder implementateringerne af medlemsfunktionerne i klassen
 * ThreadFunctionality.
 *
 *  @author Kristian Lau Jespersen
 *  @author Oskar Vedel
 *  @bug Ingen kendte bugs.
 */

#include "threadFunctionality.hpp"

MessageQ        ThreadFunctionality::dispatcherMessageQueue(20);
pthread_mutex_t ThreadFunctionality::SPI_mutex = PTHREAD_MUTEX_INITIALIZER;

/********************************************************************************************
Function used by the dispatcher thread. This dispatcher handles events from UI
and slave.
*********************************************************************************************/
void ThreadFunctionality::dispatcher(Message *messagePtr, unsigned long ID)
{
  switch (ID)
  {
    /*==================HANDLING OF EVENTS FROM SLAVE====================*/
  case LIVE_DATA_TRANSMISSION:
  {
    liveData *liveDataPtr = static_cast<liveData *>(messagePtr);
    _userInterface.sendToUI(to_string(SERVER_SENT_LIVEDATA) +
                            to_string(liveDataPtr->speed_));
    _currentRide.updateValues(liveDataPtr->speed_, liveDataPtr->distance_);
    cout << "dispatcher received live data" << endl;
    break;
  }

  case UNLOCKED_AND_IDLE_READY_TO_LOCK:
  {
    // NOTIFY USER: 30 SECONDS TO LOCK.
    break;
  }

  case LOCKED:
  {
    _userInterface.sendToUI(to_string(LOCKED)); // locking userinterface
    _currentRide.setEndtime();
    cout << "dispatcher: received lock from slave" << endl;
    break;
  }

    /*===================HANDLING OF EVENTS FROM UI=====================*/
  case USER_LOCK:
  {
    cout << "dispatcher received user lock" << endl;
    if (_lockUnit.lockBike() == true)
    {
      cout << "bike is locking" << endl;
    }
    _currentRide.setEndtime();
    break;
  }

  case USER_UNLOCK_TRY:
  {
    userUnlockTry *userUnlockTryPtr = static_cast<userUnlockTry *>(messagePtr);
    if (_userInterface.validatePin(userUnlockTryPtr->PIN_) == true)
    {
      _currentRide.resetValues();
      _lockUnit.unlockBike();
      _currentRide.setStartTime();
      _currentRide.setDate();

      int latestRide = 0;

      int numOfRides = _dataBase.getNumberOfRides();
      cout << "dispatcher: numOfRides: " << numOfRides << endl;

      string latestRideString = _dataBase.getRideByNum(numOfRides);
      cout << "disptacher: latest ride string: " << latestRideString << endl;

      if (numOfRides == 0)
      {
        _currentRide.setID(latestRide + 1);
      }
      else if (numOfRides != 0)
      {
        latestRide = stoi(latestRideString.substr(3, 3));
      }

      cout << "dispatcher: latest ride: " << latestRide << endl;
      _currentRide.setID(latestRide + 1);
    }
    break;
  }

  case USER_REQUESTS_RIDES:
  {
    int numberOfRides = _dataBase.getNumberOfRides();
    _userInterface.sendToUI(to_string(SERVER_SENT_NUMBER_OF_RIDES) +
                            to_string(numberOfRides));

    int numberOfRidesToSend = 10;
    numberOfRidesToSend =
        (numberOfRides < 10 ? numberOfRides : numberOfRidesToSend);

    int rideSendingIntervalStart = numberOfRides - numberOfRidesToSend + 1;

    for (int i = numberOfRides; i >= rideSendingIntervalStart; i--)
    {
      string Ride = _dataBase.getRideByNum(i);
      _userInterface.sendToUI(to_string(SERVER_SENT_RIDES) + Ride);
    }
    break;
  }

  case USER_SET_WHEELCIRCUMFERENCE:
  {
    wheelCircumference *wheelCircumferencePtr =
        static_cast<wheelCircumference *>(messagePtr);

    if (_userInterface.validateWheelSize(wheelCircumferencePtr->wheelCirc_))
    {
      int radiusOfWheel = stoi(wheelCircumferencePtr->wheelCirc_.substr(2, 2));
      _sensorUnit.setWheelCirc(radiusOfWheel);
      _userInterface.sendToUI("gg");
      cout << "wheelcircumference set to: " << radiusOfWheel << endl;
      break;
    }
    _userInterface.sendToUI("dd");
    cout << "illegal wheel size" << endl;
    break;
  }

  case USER_SAVED_RIDE:
  {
    _dataBase.saveRide(_currentRide.getID(), _currentRide.getDistance(),
                       _currentRide.getTopSpeed(),
                       _currentRide.getAverageSpeed(),
                       _currentRide.getStartTime(), _currentRide.getEndTime(),
                       _currentRide.getDate());
    break;
  }

  case USER_DISCARDED_RIDE:
  {
    _currentRide.resetValues();
    break;
  }

  case USER_DELETED_RIDE:
  {
    userDeleteRide *userDeleteRidePtr =
        static_cast<userDeleteRide *>(messagePtr);
    cout << "dispatcher: user deleted ride #" << userDeleteRidePtr->rideNum_
         << endl;
    _dataBase.deleteRide(userDeleteRidePtr->rideNum_);
    break;
  }

  default:
    break;
  }
}

/********************************************************************************************
dispatcher thread function
*********************************************************************************************/
void *ThreadFunctionality::dispatcherThreadFunc(void *arg)
{
  unsigned long tempID;
  while (1)
  {
    Message *messagePtr = dispatcherMessageQueue.receive(tempID);
    dispatcher(messagePtr, tempID);
    delete (messagePtr);
  }
}
