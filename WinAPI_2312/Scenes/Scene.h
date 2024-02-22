#pragma once

class Scene
{
public:
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	virtual void CreateIntroFrame() {}
	virtual void End() {}
};