/** @file xxx.xxx
 *  @brief kort beskrivelse (på én linje)
 * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
 * lang beskrivelse, lang beskrivelse
 *  @author forfatter1
 *  @author forfatter2
 *  @bug Ingen kendte bugs
 */

// AUTHOR: Kristian Lau Jespersen
// version 6
// updated 26/11/2019
// data types fixed

#pragma once
#include "SerialUnit.hpp"
#include <linux/spi/spidev.h>

#define maxMessageLength 4

class SPI : public serialUnit
{
private:
  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  int deviceNumber_;

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  unsigned char bitsPerWord_ =
      8; // specified number of bits will be sent consequetively

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  unsigned int speed_ = 1000000; // 1MHz

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  unsigned char spiMode_ = SPI_MODE_1;

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  int fileDescriptor_;

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  struct spi_ioc_transfer message_[maxMessageLength];

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  uint8_t rxBuffer_[maxMessageLength] = {'r', 'x', 'r', 'x'};

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  uint8_t txBuffer_[maxMessageLength] = {'t', 'x', 't', 'x'};

public:
  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  SPI(int deviceNumber, unsigned char bitsPerWord, unsigned int speed);

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  virtual ~SPI();

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  virtual int readAndWrite(int messageLen, int csAfterTransfer);

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  virtual void getValueOfRxBuffer(uint8_t *callBackBuffer);

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  virtual void setValueOfTxBuffer(std::string tx);

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  virtual void setValueOfTxBuffer(uint8_t forIndex0, uint8_t forIndex1,
                                  uint8_t forIndex2, uint8_t forIndex3);

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  virtual void printRxToScreen();

  /** @brief kort beskrivelse
   * lang beskrivelse, lang beskrivelse, lang beskrivelse, lang beskrivelse,
   * lang beskrivelse, lang beskrivelse
   * @param param1 beskrivelse af param1
   * @param param2 beskrivelse af param2
   * @return beskrivelse af metodens returværdi
   */
  virtual void printTxToScreen();
};
