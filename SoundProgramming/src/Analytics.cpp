#include "Analytics.h"
#include "heatmap.h"
#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"
#include "Gizmos.h"
#include <cstdio>

bool Analytics::startup()
{
	if (Application::startup() == false)
	{
		return false;
	}

	time = 0;

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	Gizmos::create();

	m_camera = FlyCamera(1280.0f / 720.0f, 10.0f);
	m_camera.setLookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	m_camera.sensitivity = 3;

	// create a heatmap
	deathMap = heatmap_new(100, 100);

	// add points to a heatmap, it this case representing a death
	heatmap_add_point(deathMap, 100, 100);

	// once points are added we can generate pixel data
	// pixelData is unsigned char array of size (width * height * 4)
	// it holds RGBA data as 4 bytes per-pixel
	heatmap_render_default_to(deathMap, pixelData);

	// the pixel data could now be used in a texture!
	// we can render multiple times if we need
	// when we're done with a heatmap we free it
	//heatmap_free(deathMap);

	return true;
}

void Analytics::shutdown()
{
	Gizmos::destroy();	heatmap_free(deathMap);
	Application::shutdown();
}

bool Analytics::update()
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

void Analytics::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Gizmos::draw(m_camera.proj, m_camera.view);

	glfwSwapBuffers(m_window);
	glfwPollEvents();
}