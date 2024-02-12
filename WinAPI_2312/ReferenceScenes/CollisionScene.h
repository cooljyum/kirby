#pragma once

class CollisionScene : public Scene
{
public:
	CollisionScene();
	~CollisionScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	Rect* rect;
	Rect* rect2;

	HBRUSH redBrush;
	HBRUSH blueBrush;

	bool isCollision = false;
};