#include "SoundProgramming.h"

#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"
#include "Gizmos.h"
#include <cstdio>

bool SoundProgramming::startup()
{
    if (Application::startup() == false)
    {
        return false;
    }

	time = 0;

	// Initialize FMOD
	result;
	m_pFmodSystem = NULL;
	// Create the main system object.
	result = FMOD::System_Create(&m_pFmodSystem);
	if (result != FMOD_OK){
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return false;
	}
	// Initialize FMOD with 512 channels
	result = m_pFmodSystem->init(512, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK){
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return false;
	}	// 2d sounding
	/*result = m_pFmodSystem->createSound("./data/audio/background_music.ogg", FMOD_DEFAULT, 0, &Sound2);	result = m_pFmodSystem->createSound("./data/audio/evironmental_effect_01.ogg", FMOD_DEFAULT, 0, &Sound);
	result = m_pFmodSystem->playSound(Sound, 0, false, &pChannel);
	result = m_pFmodSystem->playSound(Sound2, 0, false, &pChanne2);

	result = m_pFmodSystem->createChannelGroup("MyChannelGroup", &pChannelGroup);

	result = m_pFmodSystem->playSound(Sound, pChannelGroup, false, &pChannel);
	result = m_pFmodSystem->playSound(Sound, pChannelGroup, false, &pChanne2);

	m_pFmodSystem->update();*/	position = { 0, 0, 0 };
	velocity = { 0, 0, 0 };
	forward = { 1, 0, 0 };
	up = { 0, 1, 0 };
	channel_position = { 0, 1, 0 };
	channel_velocity = { 0, 1, 0 };

	m_pFmodSystem->set3DListenerAttributes(0, &position, &velocity, &forward, &up);	result = m_pFmodSystem->createSound("./data/audio/background_music.ogg",FMOD_CREATESTREAM | FMOD_3D, 0, &Sound);	result = pChannel->set3DAttributes(&channel_position, &channel_velocity, 0);	result = m_pFmodSystem->playSound(Sound, 0, false, &pChannel);		result = m_pFmodSystem->createChannelGroup("MyChannelGroup", &pChannelGroup);		result = m_pFmodSystem->playSound(Sound, pChannelGroup, false, &pChannel);

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    Gizmos::create();

    m_camera = FlyCamera(1280.0f / 720.0f, 10.0f);
    m_camera.setLookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
    m_camera.sensitivity = 3;

    return true;
}

void SoundProgramming::shutdown()
{
    Gizmos::destroy();

	Sound->release();
	Sound2->release();
	m_pFmodSystem->close();
	m_pFmodSystem->release();
    Application::shutdown();
}

bool SoundProgramming::update()
{
    if (Application::update() == false)
    {
        return false;
    }

    Gizmos::clear();

    float dt = (float)glfwGetTime();
    glfwSetTime(0.0);

	if (time > 0)
	{
		time -= dt;
	}

    vec4 white(1);
    vec4 black(0, 0, 0, 1);
    for (int i = 0; i <= 20; ++i)
    {
        Gizmos::addLine(vec3(-10 + i, -0.01, -10), vec3(-10 + i, -0.01, 10),
            i == 10 ? white : black);
        Gizmos::addLine(vec3(-10, -0.01, -10 + i), vec3(10, -0.01, -10 + i),
            i == 10 ? white : black);
    }

    m_camera.update(dt);

    return true;
}

void SoundProgramming::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Gizmos::draw(m_camera.proj, m_camera.view);

	if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && time <= 0)
	{
		time = 0.2;		result = m_pFmodSystem->createSound("./data/audio/gunshot.ogg", FMOD_DEFAULT, 0, &Sound2);
		result = m_pFmodSystem->playSound(Sound2, 0, false, &pChanne2);

		result = m_pFmodSystem->playSound(Sound2, pChannelGroup, false, &pChanne2);
	}
	m_pFmodSystem->update();
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}