#pragma once

class ShootingGameScene : public Scene
{
public:
	ShootingGameScene();
	~ShootingGameScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	Plane* plane;
};