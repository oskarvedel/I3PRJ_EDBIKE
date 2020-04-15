// AUTHOR: Frederik Runge-Dalager og Ermin Obradovac
/** @file DataBase.cpp
 *  @brief Implementering af DataBasen
 *
 * Indeholder implementeringerne af funktionerne i DataBasen.
 *
 *  @author Frederik Runge-Dalager
 *  @author Ermin Obradovac
 *  @bug Hvis vi sletter en tur der ikke findes forsvinder hele DataBasen.
 */
#include "DataBase.hpp"

DataBase::DataBase()
{
  fstream dataBaseStream;
  dataBaseStream.open("EDBikeDataBase.txt", fstream::app);
  dataBaseStream.close();
}

DataBase::~DataBase() {}

void DataBase::saveRide(int ID, int distance, int topSpeed, float averageSpeed,
                        string startTime, string endTime, string date)
{
  string ID_ = to_string(ID);
  ID_ = string(3 - ID_.length(), '0') + ID_; // prepend 0 to ID if necessary

  string distance_ = to_string(distance).substr(0, 3);
  distance_        = distance_ + string(3 - distance_.length(), '0');

  string topSpeed_ = to_string(topSpeed).substr(0, 3);
  topSpeed_        = string(3 - topSpeed_.length(), '0') + topSpeed_;

  cout << "averageSpeed unrounded: " << averageSpeed << endl;
  int averageSpeedRounded = round(averageSpeed);
  cout << "averageSpeed rounded: " << averageSpeedRounded << endl;
  string averageSpeed_ = to_string(averageSpeedRounded).substr(0, 2);
  averageSpeed_ = string(2 - averageSpeed_.length(), '0') + averageSpeed_;
  cout << "averageSpeed rounded with trailing zeros: " << averageSpeed_ << endl;

  fstream dataBaseStream;
  dataBaseStream.open("EDBikeDataBase.txt", std::ios_base::app);
  dataBaseStream << "R" << ID_ << "@" << distance_ << "@" << topSpeed_ << "@"
                 << averageSpeed_ << "@" << startTime << "@" << endTime << "@"
                 << date << endl;
  dataBaseStream.close();
}

string DataBase::getRideByID(int RideNum)
{
  string RideNum_ = to_string(RideNum);
  RideNum_        = string(2 - RideNum_.length(), '0') + RideNum_;
  string RideToGet;
  string returnThis;

  fstream dataBaseStream;
  dataBaseStream.open("EDBikeDataBase.txt");
  string lineOutput = "R" + RideNum_;
  while (getline(dataBaseStream, RideToGet))
  {
    if (findInDB(RideToGet, lineOutput))
    {
      returnThis = RideToGet;
    }
  }

  dataBaseStream.close();
  return returnThis;
}

string DataBase::getRideByNum(int RideNum)
{
  if (RideNum == 0)
  {
    return "0";
  };

  string lineOutput;

  fstream dataBaseStream;
  dataBaseStream.open("EDBikeDataBase.txt");
  for (int i = 0; i <= RideNum; i++)
  {
    getline(dataBaseStream, lineOutput);
  }
  dataBaseStream.close();
  return lineOutput;
}

void DataBase::deleteRide(string rideNum)
{
  string rideToDelete = "R" + rideNum;

  string emptyString;

  fstream  dataBaseStream;
  ofstream temp;
  temp.open("temp.txt");
  dataBaseStream.open("EDBikeDataBase.txt");
  while (getline(dataBaseStream, emptyString))
  {
    if (findInDB(emptyString, rideToDelete) != true)
    {
      temp << emptyString << endl;
    }
  }
  dataBaseStream.close();
  temp.close();
  remove("EDBikeDataBase.txt");
  rename("temp.txt", "EDBikeDataBase.txt");
}

int DataBase::getNumberOfRides()
{
  fstream dataBaseStream;
  dataBaseStream.open("EDBikeDataBase.txt");
  int    number_of_lines = 0;
  string lineOutput;

  while (getline(dataBaseStream, lineOutput))
  {
    number_of_lines++;
  }
  dataBaseStream.close();

  return number_of_lines - 1;
}

bool DataBase::findInDB(const string &line, string tur)
{
  return line.find(tur) != string::npos;
}
