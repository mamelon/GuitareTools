#ifndef LECTURE_H
#define LECTURE_H

#include "AL/al.h"
#include "AL/alc.h"
#include <sndfile.h>
#include <iostream>

class Lecture
{
public:
   static Lecture * instance();
   static void drop();
   ALuint LoadSound(const std::string& Filename);
   void play(const std::string &Filename);
   void stop();
   void setStatus(ALint status);
   ALint Status();

private:
   Lecture();
   ~Lecture(){}

private:
   static Lecture * _instance;
   ALint _status;
   ALuint Source;
};

#endif // LECTURE_H
