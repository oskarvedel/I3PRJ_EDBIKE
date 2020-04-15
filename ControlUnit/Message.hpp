/** @file Message.hpp
 *  @brief Implementation af Message-klassen
 * Denne klasse implementerer en Message-klasse, der bruges som base-class til beskederne i systemet
 *  @author Kristian Lau Jespersen
 *  @author Oskar Vedel
 *  @bug Ingen kendte bugs.
 */
#include <pthread.h>
#include <iostream>
#include <queue> 
#include <string>
#include <unistd.h>


class Message 
{
public:
    virtual ~Message(){}
};

struct item
{
    unsigned long ID_;
    Message* msg_;
};