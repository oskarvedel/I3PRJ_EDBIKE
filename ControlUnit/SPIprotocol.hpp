/** @file xxx.xxx
 *  @brief kort beskrivelse (på én linje)
 * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
 * lang beskrivelse, lang beskrivelse
 *  @author forfatter1
 *  @author forfatter2
 *  @bug Ingen kendte bugs
 */

#pragma once
#include <stdint.h>
#include <unistd.h>

class SPIprotocol
{
private:
public:
  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  static void extractFromBuffer(uint8_t &speed, uint8_t &distance,
                                uint8_t *buffer);

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  static bool errorCheckWithOddParity(uint8_t *buffer, uint8_t lengthOfBuffer);

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  static void createParityBits(uint8_t *buffer, uint8_t lengthOfBuffer);
};

enum data_transmission_indexes
{
  MESSAGE_TYPE_ID_INDEX = 0,
  SPEED_INDEX           = 1,
  DISTANCE_INDEX        = 2,
  ERROR_CHECK_INDEX     = 3
};

enum event_transmission_indexes
{
  // MESSAGE_TYPE_ID_INDEX = 0,
  FIRST_EVENT_INDEX  = 1,
  SECOND_EVENT_INDEX = 2,
  // ERROR_CHECK_INDEX     = 3
};

enum SPItransmissionIdentifiers
{
  LIVE_DATA_TRANSMISSION         = 100, // ASCII d
  EVENT_TRANSMISSION_TO_MASTER   = 101, // ASCII e
  EVENT_TRANSMISSION_FROM_MASTER = 69   // ASCII E
};