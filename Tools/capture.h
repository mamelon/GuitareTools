#ifndef CAPTURE_H
#define CAPTURE_H

#include <QStringList>
#include "AL/alc.h"
#include <AL/al.h>

class Capture
{
public:
    static QStringList getCaptureDevices();
};

#endif // CAPTURE_H
