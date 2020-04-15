/** @file MessageQ.hpp
 *  @brief Implementation af MessageQ-klassen
 * Denne klasse implementerer en MessageQueue, der bruges til at kommunikere
 * mellem trådene i programmet.
 *  @author Kristian Lau Jespersen
 *  @author Oskar Vedel
 *  @bug Ingen kendte bugs.
 */

#pragma once

#include "Message.hpp"
#include <iostream>
#include <pthread.h>
#include <queue>
#include <string>
#include <unistd.h>
using namespace std;

class MessageQ
{
public:
  /** @brief Klassens constructor
   * Initialiserer køens størrelse
   * @param MaxQCapacity Køens størrelse
   */
  MessageQ(unsigned long maxQCapacity = 20) : maxQCapacity_(maxQCapacity) {}

  /** @brief Lægger besked ind i køen
   *
   * @param ID ID'et på det event, der lægges ind i køen
   * @param msg Dataene for det event, der lægges ind i køen. Sættes til
   * nullptr, hvis ikke der sendes noget data.
   * @return
   */
  void send(unsigned long ID, Message *msg = nullptr)
  {
    pthread_mutex_lock(&sendReceive_mutex);
    while (occupiedSpaces == maxQCapacity_)
    {
      pthread_cond_wait(&item_transmit_cond, &sendReceive_mutex);
    }
    item itemToSend{
        .ID_  = ID,
        .msg_ = msg,
    };
    queue_.push(itemToSend);
    occupiedSpaces++;
    pthread_cond_signal(&item_transmit_cond);
    pthread_mutex_unlock(&sendReceive_mutex);
  }

  /** @brief Henter en besked fra køen
   *
   * @param ID Reference til ID'et på den besked, der hentes fra køen
   * @return Returnerer en pointer til dataene for den besked, der hentes fra
   * køen.
   */
  Message *receive(unsigned long &ID)
  {
    pthread_mutex_lock(&sendReceive_mutex);
    while (occupiedSpaces == 0)
    {
      pthread_cond_wait(&item_transmit_cond, &sendReceive_mutex);
    }
    item tempItem = queue_.front();
    queue_.pop();
    ID = tempItem.ID_;
    occupiedSpaces--;
    pthread_cond_signal(&item_transmit_cond);
    pthread_mutex_unlock(&sendReceive_mutex);
    return tempItem.msg_;
  }
  ~MessageQ() {}

private:
  // Container with messages
  queue<item> queue_;
  // Plus other relevant variables
  unsigned long   maxQCapacity_;
  unsigned long   occupiedSpaces     = 0;
  pthread_mutex_t sendReceive_mutex  = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t  item_transmit_cond = PTHREAD_COND_INITIALIZER;
};
