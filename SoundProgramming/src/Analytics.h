#ifndef ANALYTICS_H_
#define ANALYTICS_H_

#include "Application.h"
#include "Camera.h"
#include "heatmap.h"
class Analytics : public Application
{
public:
	virtual bool startup();
	virtual void shutdown();
	virtual bool update();
	virtual void draw();

	float time;

	unsigned char pixelData[(100*100*4)];
	heatmap_t* deathMap;

	FlyCamera m_camera;
};

#endif //ANALYTICS_H_