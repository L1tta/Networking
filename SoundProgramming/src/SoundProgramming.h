#ifndef SOUND_PROGRAMMING_H_
#define SOUND_PROGRAMMING_H_

#include "Application.h"
#include "Camera.h"
#include"fmod.hpp"
#include"fmod_errors.h"

class SoundProgramming : public Application
{
public:
    virtual bool startup();
    virtual void shutdown();
    virtual bool update();
    virtual void draw();

	float time;

    FlyCamera m_camera;
	FMOD::System* m_pFmodSystem;
	FMOD::Sound* Sound;
	FMOD::Sound* Sound2;
	FMOD::Channel* pChannel;
	FMOD::Channel* pChanne2;
	FMOD::ChannelGroup* pChannelGroup;

	FMOD_VECTOR position;
	FMOD_VECTOR velocity;
	FMOD_VECTOR forward;
	FMOD_VECTOR up;
	FMOD_VECTOR channel_position;
	FMOD_VECTOR channel_velocity;

	FMOD_RESULT result;
};

#endif //CAM_PROJ_H_