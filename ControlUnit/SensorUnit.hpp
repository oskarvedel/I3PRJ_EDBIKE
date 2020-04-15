/** @file xxx.xxx
 *  @brief kort beskrivelse (på én linje)
 * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
 * lang beskrivelse, lang beskrivelse
 *  @author forfatter1
 *  @author forfatter2
 *  @bug Ingen kendte bugs
 */

// AUTHOR: Kristian Lau Jespersen
//
// updated 26/11/2019
// data types fixed. Pull function made into callback

#pragma once
class sensorUnit;
class SPIprotocol;

#include "EDBikeProtocol.hpp"
#include "SPIprotocol.hpp"
#include "SerialUnit.hpp"
#include "threadFunctionality.hpp"
struct liveData;

#include <iostream>

extern MessageQ dispatcherMessageQueue;

class sensorUnit
{
private:
  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  serialUnit *serialUnit_;

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  liveData *latestLiveData_;

public:
  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  sensorUnit(serialUnit *serialUnit);

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  ~sensorUnit();

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  void pull(uint8_t *retrieveBuffer);

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  void slavePullerToDispatcher(uint8_t *bufferReceived);

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  void slavePullerThreadFunc();

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  int setWheelCirc(int wheelCircInCentiMeters);
};
