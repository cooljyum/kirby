#pragma once

class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	Image* bg1;
	Image* bg2;

	Kirby* kirby;
	Monster* monster;
};