/** @file xxx.xxx
 *  @brief kort beskrivelse (på én linje)
 * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
 * lang beskrivelse, lang beskrivelse
 *  @author forfatter1
 *  @author forfatter2
 *  @bug Ingen kendte bugs
 */

// AUTHOR: Kristian Lau Jespersen

#pragma once
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <linux/types.h>
#include <sys/ioctl.h>
#include <unistd.h>

class serialUnit
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
  serialUnit();

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  virtual ~serialUnit() = 0;

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  virtual int readAndWrite(int messageLen, int optionalArg) = 0;

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  virtual void getValueOfRxBuffer(uint8_t *callBackBuffer) = 0;

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  virtual void setValueOfTxBuffer(std::string tx) = 0;

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  virtual void setValueOfTxBuffer(uint8_t forIndex0, uint8_t forIndex1,
                                  uint8_t forIndex2, uint8_t forIndex3) = 0;

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  virtual void printRxToScreen() = 0;

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  virtual void printTxToScreen() = 0;
};
