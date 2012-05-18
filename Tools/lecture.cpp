#include "lecture.h"
#include "openal.h"
#include <vector>
#include <QDebug>
#include <QCoreApplication>

Lecture *Lecture::_instance = NULL;

ALuint Lecture::LoadSound(const std::string& Filename)
{
    // Ouverture du fichier audio avec libsndfile
        SF_INFO FileInfos;
        SNDFILE* File = sf_open(Filename.c_str(), SFM_READ, &FileInfos);
        if (!File)
        {
            qDebug() << "Impossible d'ouvrir le fichier audio";
            return 0;
        }

        // Lecture du nombre d'échantillons et du taux d'échantillonnage (nombre d'échantillons à lire par seconde)
        ALsizei NbSamples  = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
        ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);



        // Lecture des échantillons audio au format entier 16 bits signé (le plus commun)
        std::vector<ALshort> Samples(NbSamples);
        if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
        {
            qDebug() << "Impossible de lire les échantillons stockés dans le fichier audio";
            return 0;
        }

        // Fermeture du fichier
        sf_close(File);

        // Détermination du format en fonction du nombre de canaux
        ALenum Format;
        switch (FileInfos.channels)
        {
            case 1 : Format = AL_FORMAT_MONO16;   break;
            case 2 : Format = AL_FORMAT_STEREO16; break;
            default :
                qDebug() << "Format audio non supporté (plus de 2 canaux)";
                return 0;
        }

        // Création du tampon OpenAL
        ALuint Buffer;
        alGenBuffers(1, &Buffer);

        // Remplissage avec les échantillons lus
        alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);

        // Vérification des erreurs
        if (alGetError() != AL_NO_ERROR)
        {
            qDebug() << "Impossible de remplir le tampon OpenAL avec les échantillons du fichier audio" ;
            return 0;
        }

        return Buffer;
}

void Lecture::play(const std::string& Filename)
{
    //initialize OpenAL
    if(OpenAL::InitOpenAL())
        qDebug() << "Initialisation d'OpenAL OK";

    // load the audio file
    ALuint Buffer = LoadSound(Filename);

    // creation of a source
    alGenSources(1, &Source);
    alSourcei(Source, AL_BUFFER, Buffer);

    //Play the source
    alSourcePlay(Source);

    do
    {
//        QCoreApplication::processEvents();
        // Récupération de l'état du son
        alGetSourcei(Source, AL_SOURCE_STATE,&_status);
    }
    while (_status == AL_PLAYING);

    // Delete buffer
   alDeleteBuffers(1, &Buffer);

   // Delete source
   alSourcei(Source, AL_BUFFER, 0);
   alDeleteSources(1, &Source);

   // ShutDown OpenAL
   OpenAL::ShutdownOpenAL();
}

void Lecture::stop()
{
    alSourceStop(Source);
}

void Lecture::setStatus(ALint status)
{
    _status = status;
}

ALint Lecture::Status()
{
    return _status;
}

Lecture *Lecture::instance()
{
    if(NULL == _instance) _instance = new Lecture();

    return _instance;
}

void Lecture::drop()
{
    if(NULL != _instance)
    {
        delete _instance;
        _instance = NULL;
    }
}

Lecture::Lecture()
{}
