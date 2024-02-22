#pragma once

class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void CreateSound() override;

	void Start() override;

private:
	Image* bg1;
	Image* bg2;

	Kirby* kirby;
};