#ifndef OPENAL_H
#define OPENAL_H

#include "AL/al.h"
#include "AL/alc.h"

class OpenAL
{
public:
    static bool InitOpenAL();
    static bool ShutdownOpenAL();
};

#endif // OPENAL_H
