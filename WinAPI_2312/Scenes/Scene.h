#pragma once

class Scene
{
public:
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	virtual void CreateIntroFrame() {}
	virtual void CreateSound() {}

	virtual void Start() {}
	virtual void End() {}
};