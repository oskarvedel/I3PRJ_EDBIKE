// AUTHOR: Oskar Vedel & Sebastian Brahe
/** @file UserInterface.cpp
 *  @brief Implementation af UserInterface
 *
 * Indeholder implementationer af medlemsfunktionerne i UserInterface.
 *
 *  @author Sebastian Brahe
 *  @author Oskar Vedel
 *  @bug Det er muligt at indstille hjulstørrelsen til 0
 */

#include "UserInterface.hpp"
using namespace std;

UserInterface::UserInterface() {}
UserInterface::~UserInterface() {}

void UserInterface::UIReceiveToDispatcher(string message)
{
  cout << "Received from client: '" << message << "'" << endl;
  char message_ = 0;
  try
  {
    message_ = stoi(message.substr(0, 2));
  }
  catch (std::exception &)
  {
    cout << "stoi returned error" << endl;
  }

  switch (message_)
  {
  case USER_LOCK:
  {
    ThreadFunctionality::dispatcherMessageQueue.send(USER_LOCK);
    break;
  }

  case USER_UNLOCK_TRY:
  {
    ThreadFunctionality::dispatcherMessageQueue.send(
        USER_UNLOCK_TRY, new userUnlockTry(message.substr(2, 4)));
    break;
  }

  case USER_REQUESTS_RIDES:
  {
    ThreadFunctionality::dispatcherMessageQueue.send(USER_REQUESTS_RIDES);
    break;
  }

  case USER_SET_WHEELCIRCUMFERENCE:
  {
    cout << "user set wheel circumference" << endl;
    ThreadFunctionality::dispatcherMessageQueue.send(
        USER_SET_WHEELCIRCUMFERENCE, new wheelCircumference(message));
    break;
  }

  case USER_SAVED_RIDE:
  {
    ThreadFunctionality::dispatcherMessageQueue.send(USER_SAVED_RIDE);
    break;
  }

  case USER_DISCARDED_RIDE:
  {
    ThreadFunctionality::dispatcherMessageQueue.send(USER_DISCARDED_RIDE);
    break;
  }

  case USER_DELETED_RIDE:
  {
    cout << "ride deletion message: " << message.substr(2, 3) << endl;
    ThreadFunctionality::dispatcherMessageQueue.send(
        USER_DELETED_RIDE, new userDeleteRide(message.substr(2, 3)));
    break;
  }

  default:
    break;
  }
}

void UserInterface::UIReceive()
{
  Hub_.onMessage([this](uWS::WebSocket<uWS::SERVER> *ws, char *message,
                        size_t length, uWS::OpCode opCode) {
    string messageString = string(message, length);
    UIReceiveToDispatcher(messageString);
  });

  if (Hub_.listen(3000))
  {
    Hub_.run();
  }
}

bool UserInterface::validatePin(string inputPin)
{
  if (inputPin == correctPin && pinTimerActive == false)
  {
    pinAttempts = 5;
    sendToUI(to_string(PIN_VALIDATE_RETURNED_CORRECT_PIN));
    cout << "Password correct. EDBIKE unlocked." << endl;
    return true;
  }
  else if (inputPin != correctPin && pinTimerActive == false)
  {
    string attemptsleft;
    pinAttempts--;
    if (pinAttempts > 0)
    {
      attemptsleft = to_string(pinAttempts);
      sendToUI(to_string(PIN_VALIDATE_RETURNED_WRONG_PIN) + attemptsleft);
      cout << "Password incorrect. UI not unlocked" << endl;
      return false;
    }
    else if (pinAttempts <= 0)
    {
      cout << "Password incorrect. Timer started" << endl;
      thread th3(callPinTimer, this);
      th3.detach();
      return false;
    }
  }
  return false;
}

void *UserInterface::callPinTimer(void *arg)
{
  return ((UserInterface *)arg)->pinTimer();
}

void *UserInterface::pinTimer()
{
  pinTimerActive = true;
  string remainingSeconds;
  for (int seconds = 300; seconds >= 0; seconds--)
  {
    remainingSeconds = to_string(seconds);
    sendToUI(to_string(PIN_VALIDATE_RETURNED_TIMEOUT) + remainingSeconds);
    sleep(1);
  }
  pinTimerActive = false;
  pinAttempts    = 5;
  return 0;
}

void UserInterface::sendToUI(string event)
{
  ostringstream ss;
  ss << event;
  UserInterface::Hub_.broadcast(ss.str().c_str(), ss.str().length(),
                                uWS::OpCode::TEXT);
  cout << "Sent to client: '" << event << "'" << endl;
};

bool UserInterface::validateWheelSize(string wheel_input)
{
  for (long unsigned int i = 0; i < wheel_input.length(); i++)
  {
    if (isdigit(wheel_input[i]) ==
        false) // tjek om der er nogle bogstaver og return false hvis ja
    {
      return false;
    }
  }
  return true;
};
