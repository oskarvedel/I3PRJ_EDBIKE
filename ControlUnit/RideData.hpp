// AUTHOR: Frederik Runge-Dalager og Ermin Obradovac
/** @file RideData.hpp
 *  @brief Funktionsprototyper til RideData
 *
 * Indeholder prototyperne til funktionerne i RideData-klassen
 *
 *  @author Frederik Runge-Dalager
 *  @author Ermin Obradovac
 *  @bug Ingen kendte bugs.
 */
#pragma once
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

class RideData
{
public:
  /** @brief Klassens constructor.
   * Nulstiller alle variabler
   */
  RideData();
  /** @brief Sætter start tidspunkt på turen
   * Benytter biblioteket time.h til at sætte turens starttidspunkt til det
   * nuværende tidspunkt på RPI'en.
   */
  void setStartTime();
  /** @brief Sætter sluttidspunkt på turen
   * Benytter biblioteket time.h til at sætte turens sluttidspunkt til det
   * nuværnde tidspunkt på RPI'en.
   */
  void setEndtime();
  /** @brief Sætter datoen på turen
   * Benytter biblioteket time.h til at sætte turens dato til den
   * nuværnde dato på RPI'en.
   */
  void setDate();
  /** @brief Giver turen et ID
   * Tager en int id som den så bruger som ID'et på turen.
   * @param int id, ID på turen
   */
  void setID(int);
  /** @brief Nulstiller de topSpeed og avrageSpeed
   * Bruges når der starter en ny tur.
   */
  void resetValues();
  /** @brief Sætter distance, topSpeed og avrageSpeed
   * For besked om hvor langt der er kørt og hvilken hastighed der er lige nu.
   * Så sætter den distance til den distance den får. Hvis den nye hastighed er
   * større end den gamle topSpeed sætter den en ny top speed. Det sidste den
   * gør er at udregne en gennemsnitsfart og så gemme den.
   * @param int currentSpeed, hastigheden lige nu
   * @param int distance, hvor langt der er kørt
   */
  void updateValues(int currentSpeed, int distance);
  /** @brief Returnere avrageSpeed
   */
  float getAverageSpeed();
  /** @brief Returnere TopSpeed
   */
  int getTopSpeed();
  /** @brief Returnere Distance
   */
  int getDistance();
  /** @brief Returnere StartTime
   */
  string getStartTime();
  /** @brief Returnere EndTime
   */
  string getEndTime();
  /** @brief Returnere Data
   */
  string getDate();
  /** @brief Returnere ID
   */
  int getID();

private:
  int        updateNum_;
  float      averageSpeed_;
  int        topSpeed_;
  int        distance_;
  string     startTime_;
  string     endTime_;
  string     date_;
  int        ID_;
  time_t     rawtime;
  struct tm *info;
};