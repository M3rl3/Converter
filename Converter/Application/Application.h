#pragma once

#include "../Window/Window.h"
#include "../Timer/Timer.h"
#include "../UI/UI.h"

class Application
{
public:
	Application();
	~Application();

	void Initialize(const char* title, const int width, const int height, bool fullScreen);
	void Update(float dt);
	void Shutdown(void);
	
	Window* GetWindow(void);
	Timer* GetTimer(void);

private:
	Window* m_Window;
	Timer* m_Timer;
	UI* m_GUI;

	// Delta time
	float deltaTime = 0.f;

	// Frame rate & Frame time
	unsigned int frameCount = 0;
	unsigned int frameRate = 0;
	unsigned int frameTime = 0;
};