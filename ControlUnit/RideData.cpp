// AUTHOR: Frederik Runge-Dalager og Ermin Obradovac
/** @file RideData.cpp
 *  @brief Implementering af RideData
 *
 * Indeholder implementeringerne af funktionerne i RideData-klassen.
 *
 *  @author Frederik Runge-Dalager
 *  @author Ermin Obradovac
 *  @bug Ingen kendte bugs.
 */
#include "RideData.hpp"

RideData::RideData()
{
  updateNum_    = 0;
  topSpeed_     = 0;
  averageSpeed_ = 0;
  distance_     = 0;
}

void RideData::updateValues(int currentSpeed, int distance)
{
  updateNum_++;
  distance_ = distance;
  if (currentSpeed > topSpeed_)
  {
    topSpeed_ = currentSpeed;
  }
  averageSpeed_ =
      (averageSpeed_ * (updateNum_ - 1) + currentSpeed) / updateNum_;
}

void RideData::resetValues()
{
  averageSpeed_ = 0;
  topSpeed_     = 0;
}

void RideData::setStartTime()
{
  time(&rawtime);
  info       = localtime(&rawtime);
  int hour   = info->tm_hour;
  int minute = info->tm_min;

  string hourStr = to_string(hour);
  hourStr        = string(2 - hourStr.length(), '0') + hourStr;

  string minuteStr = to_string(minute);
  minuteStr        = string(2 - minuteStr.length(), '0') + minuteStr;

  string timeStr = hourStr + minuteStr;
  startTime_       = timeStr;
}

void RideData::setEndtime()
{
  time(&rawtime);
  info       = localtime(&rawtime);
  int hour   = info->tm_hour;
  int minute = info->tm_min;

  string hourStr = to_string(hour);
  hourStr        = string(2 - hourStr.length(), '0') + hourStr;

  string minuteStr = to_string(minute);
  minuteStr        = string(2 - minuteStr.length(), '0') + minuteStr;

  string timeStr = hourStr + minuteStr;
  endTime_       = timeStr;
  cout << "RideData set endtime to: " << endTime_ << endl;
}

void RideData::setDate()
{
  time(&rawtime);
  info            = localtime(&rawtime);
  int    day      = info->tm_mday;
  int    month    = info->tm_mon + 1;
  int    year     = info->tm_year - 100;
  string dayStr   = to_string(day);
  dayStr          = string(2 - dayStr.length(), '0') + dayStr;
  string monthStr = to_string(month);
  monthStr        = string(2 - monthStr.length(), '0') + monthStr;
  string yearStr  = to_string(year);
  yearStr         = string(2 - yearStr.length(), '0') + yearStr;

  date_ = dayStr + monthStr + yearStr;
}

void RideData::setID(int id) { ID_ = id; }

float RideData::getAverageSpeed() { return averageSpeed_; }

int RideData::getTopSpeed() { return topSpeed_; }

int RideData::getDistance() { return distance_; }

string RideData::getEndTime() { return endTime_; }

string RideData::getStartTime() { return startTime_; }

string RideData::getDate() { return date_; }

int RideData::getID() { return ID_; }