#pragma once

class PixelCollisionScene : public Scene
{
public:
	PixelCollisionScene();
	~PixelCollisionScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Start() override;
	virtual void End() override;

private:
	Image* bg;
	Image* mountain;

	Robot* robot;
};