#pragma once

#include "../Window/Window.h"

class UI 
{
public:
	UI();
	~UI();

	void Initialize(Window* window);
	void Update(float dt);
	void Shutdown();

public:
	bool m_Render;

private:
};