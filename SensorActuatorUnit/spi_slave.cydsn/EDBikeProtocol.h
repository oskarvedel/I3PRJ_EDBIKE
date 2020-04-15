/* ========================================
 *
 *
 *
 * ========================================
*/
#pragma once
#include "project.h"

/*
Following enums are used as:
-Event identifiers in user interface class on master.
-Event identifiers sent to PSoC slave.
-Event identifiers sent from PSoC slave to RPI master.
-Message IDs for messages sent between threads on RPI master. 

The first portion of the events can only originate from the user interface.
The next portion of the events can only originate from the PSoC slave.
*/
enum bikeState
{
    /*=================EVENTS FROM SLAVE=================*/
  UNLOCKING                       = 117, // ASCII u
  UNLOCKED_AND_ACTIVE             = 97,  // ASCII a
  UNLOCKED_AND_IDLE               = 105, // ASCII i
  UNLOCKED_AND_IDLE_READY_TO_LOCK = 114, // ASCII r
  LOCKING                         = 108, // ASCII l
  LOCKED                          = 111, // ASCII o

  /*==================EVENTS FROM UI CLIENT===================*/
  USER_LOCK                   = 76, // ASCII L
  USER_UNLOCK_TRY             = 84, // ASCII T
  USER_REQUESTS_RIDES         = 82, // ASCII R
  USER_SET_WHEELCIRCUMFERENCE = 87, // ASCII W
  USER_DISCARDED_TRIP         = 88, // ASCII X
  USER_SAVED_TRIP             = 83, // ASCII S
  USER_DELETED_TRIP           = 67, // ASCII C

  /*==================EVENTS FROM UI SERVER===================*/
  PIN_VALIDATE_RETURNED_WRONG_PIN    = 77, // ASCII M
  PIN_VALIDATE_RETURNED_TIMEOUT      = 78, // ASCII N
  PIN_VALIDATE_RETURNED_CORRECT_PIN  = 86, // ASCII V
  USER_UNLOCK                        = 85, // ASCII U
  SERVER_SENT_NUMBER_OF_RIDES        = 68, // ASCII D
  SERVER_SENT_LIVEDATA               = 80, // ASCII P
  VALIDATEWHEELSIZE_RETURNED_TRUE    = 81, // ASCII Q
  VALIDATEWHEELSIZE_RETURNED_FALSE   = 89  // ASCII Y
};








/* [] END OF FILE */
