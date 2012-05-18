#include "capture.h"
#include "sndfile.h"

QStringList Capture::getCaptureDevices()
{
    QStringList res;

    // Récupération des devices de capture disponibles
    const ALCchar* DeviceList = alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);

    if (DeviceList)
    {
        // Extraction des devices contenus dans la chaîne renvoyée
        while (strlen(DeviceList) > 0)
        {
            res.append(DeviceList);
            DeviceList += strlen(DeviceList) + 1;
        }
    }
    return res;
}
