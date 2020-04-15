/** @file UserInterface.hpp
 *  @brief Funktionsprototyper til UserInterface-klassen
 *
 * Indeholder prototyperne til UserInterface.cpp, der håndterer kommunikation
 * mellem server og brugerflade.
 *
 *  @author Sebastian
 *  @author Oskar Vedel
 *  @bug Det er muligt at indstille hjulstørrelsen til 0
 */
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
  /** @brief Klassens constructor.
   * Har ingen funktionalitet, men er deklareret for en sikkerheds skyld.
   */
  UserInterface();

  /** @brief Klassens destructor
   * Har ingen funktionalitet, men er deklareret for en sikkerheds skyld.
   */
  ~UserInterface();

  /** @brief Modtager events fra brugerfladen
   * Kaldes af UserInterface::UIReceive og evaluerer eventets type på
   * baggrund af den overordnede protokol for EDBike. Eventet og relevant data
   * sendes derefter videre til dispatcher-tråden via MessageQueue.
   * @param event String der indeholder det event der skal sendes til
   * brugerfladen
   */
  void UIReceiveToDispatcher(string event);

  /** @brief Validerer PIN, der er indtastet af bruger i client browser
   *
   * Tjekker, om den indtastede PIN stemmer overens med den korrekte PIN og
   * kalder et PIN-timeout, (medlemsfunktionen pinTimer (Tabel 10)) hvis PIN er
   * skrevet forkert 5 gange i brugerfladen. Antallet af brugte forsøg
   * dekrementeres hver gang, funktionen kaldes med en forkert pin.
   * @param event String der indeholder den indtastede PIN som skal tjekkes.
   * @return True, hvis den indtastede PIN stemmer overens med den korrekte PIN.
   * False, hvis den indtastede PIN ikke stemmer overens med den korrekte PIN
   * eller hvis PIN-timeoutet er aktivt.
   */
  bool validatePin(string inputPin);

  /** @brief Lytter efter data fra brugerflade i client browser.
   * Indeholder en overloaded version af Hub::onMessage
   * lampda-funktionen fra uWebSockets-biblioteket. Denne funktion kører som en
   * tråd og lytter efter events fra client browser og kalder
   * UserInterface::UIReceiveToDispatcher, når der modtages et event.
   */
  void UIReceive();

  /** @brief Sender event til brugerflade i client browser
   * Sender en string til brugerflade i client browser via
   * uWebSockets-funktionen Hub_::broadcast.
   * @param event String der indeholder det event der skal sendes til
   * brugerflade i client browser
   */
  void sendToUI(string event);

  /** @brief Kalder UserInterface::pinTimer
   * Denne funktion gør det muligt at kalde pinTimer() (Tabel 10) som en tråd
   * fra andre medlemsklasser, og fungerer altså som ’limen’ mellem de andre
   * medlemsfunktioner og den egentlige pinTimer-metode. Grunden er,
   * atstd::thread i C++ skal kaldes på statiske medlemsfunktioner. Denne
   * funktion returnerer en pointer til pinTimer-metoden for objekt, der gives
   * med som argument.
   * @param arg Void-pointer, som castes til UserInterface::Pintimer
   * @return Returnerer static void for at kunne blive kaldt af
   * std::thread-biblioteket
   */
  static void *callPinTimer(void *arg);

  /** @brief Blokerer for tjek af PIN-kode i 5 minutter
   * Køres som en tråd og blokerer for validering af PIN i 5 minutter, når den
   * kaldes. Når de 5 minutter er gået sættes antallet af resterende PIN-forsøg
   * til 5.
   */
  void *pinTimer();

  /** @brief Validerer den indtastede hjulstørrelse
   * Tjekker om den indtastede hjulstørrelse overholder en række regler
   * @return Returnerer en bool, der indikerer om hjulstørrelsen er godkendt
   */
  bool validateWheelSize(string wheel_input);

private:
  string   correctPin     = "1234";
  int      pinAttempts    = 5;
  bool     pinTimerActive = false;
  uWS::Hub Hub_;
};
