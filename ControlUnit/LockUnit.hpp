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
// data types fixed.

class lockUnit;
#pragma once
#include "EDBikeProtocol.hpp"
#include "SPIprotocol.hpp"
#include "SerialUnit.hpp"
#include "threadFunctionality.hpp"
#include <string.h>

class lockUnit
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
  bool        lockStatus_;

public:
  lockUnit(serialUnit *serialUnit);
  ~lockUnit();
  bool lockBike();
  bool unlockBike();
};
