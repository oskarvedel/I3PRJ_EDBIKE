// AUTHOR: Frederik Runge-Dalager og Ermin Obradovac
/** @file DataBase.hpp
 *  @brief Funktionsprototyper til DataBasen
 *
 * Indeholder prototyperne til funktionerne i DataBasen.
 *
 *  @author Frederik Runge-Dalager
 *  @author Ermin Obradovac
 *  @bug Hvis vi sletter en tur der ikke findes forsvinder hele DataBasen.
 */
#pragma once

#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <math.h>

using namespace std;

class DataBase
{
public:
  /** @brief Klassens constructor.
  * Opretter et database tekst dokument, hvis der ikke ligger et i forvejen.
  */
  DataBase();
  /** @brief Klassens destructor
   * Har ingen funktionalitet, men er deklareret for en sikkerheds skyld.
   */  
  ~DataBase();
  /** @brief Gemmer en tur i DataBasen
   * Kaldes når brugeren har kørt en tur og vil gemme den. Benytter sig af get 
   * funktioner til at hente dataen fra RideData. Gemmer turen på én linje og 
   * laver så linjeskift så den er klar til næste tur. Funktionen sørger også
   * for at formateringen bliver lavet så det passer til at skrive ud på brugerfladen.
   * @param int ID
   * @param float Distance
   * @param int Topspeed
   * @param float Avragespeed
   * @param string StartTime
   * @param string EndTime
   * @param string Date
   */
  void   saveRide(int, int, int, float, string, string, string);
   /** @brief Fjerner en tur fra DataBasen
    * Bruges til at fjerne en tur fra DataBasen. Tager en int RideNum som er
    * den tur man gernve vil slette. Så laver den en temp tekst fil hvor den overføre
    * alt fra Database tekstdokumentet til. Hvis den finder den tur man gernve vil slette
    * lader den værd med at overføre den.
    * @param string rideNum, turen man gerne vil slette
   */
  void   deleteRide(string);
  /** @brief Henter antallet af ture
   * Bruges til at hente antallet af ture i databasen.
   * Løber linjerne i tekstdokumentet igennem og tæller en op per linje.
   * Returnere så antalet af ture.
   */  
  int    getNumberOfRides();
  /** @brief Henter en tur fra DataBasen ud fra dens ID
   * Bruges til at hente bestemt tur i databasen.
   * Tager en int RideNum som er den tur man gerne vil hente.
   * Den benytter sig af findInDB funktionen som tjekker efter om 
   * @param int RideNum, turen man gerne vil hente på ID
   */  
  string getRideByID(int);
  /** @brief Henter en tur fra DataBasen ud fra dens position i DataBasen
   * Bruges til at hente bestemt tur i databasen.
   * Tager en int RideNum som er den tur man gerne vil hente.
   * Den løber linjerne igennem intil den finder den tur man gerne vil
   * have ud og så returnere den turen.
   * @param int RideNum, turen man gerne vil hente på position
   */    
  string getRideByNum(int);
  /** @brief Tjekker om input er ens med noget der ligger på en linje
   * Bruges når vi skal finde tur på ID
   * @param string &line, det er en const string
   * @param string turs
   */    
  bool   findInDB(const string &line, string tur);

private:
};
