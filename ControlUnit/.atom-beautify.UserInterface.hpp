// AUTHOR: Oskar Vedel & Sebastian Brahe
//

#pragma once

class UserInterface;

#include "MessageQ.hpp"
#include "threadFunctionality.hpp"
#include </home/stud/uwebsockets/uWS/uWS.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

extern MessageQ dispatcherMessageQueue;

class UserInterface
{
public:
  UserInterface();
  ~UserInterface();
  void         UIReceiveToDispatcher(string message);
  bool         validatePin(string inputPin);
  void         UIReceive();
  void         sendToUI(string event);
  static void *callPinTimer(void *arg);
  void *       pinTimer();
  void         updateLiveData(int speed);

private:
  string   correctPin     = "1234";
  int      pinAttempts    = 5;
  bool     pinTimerActive = false;
  uWS::Hub Hub_;
};
