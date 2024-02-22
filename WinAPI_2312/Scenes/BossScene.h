#pragma once

class BossScene : public Scene
{
public:
	BossScene();
	~BossScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	Image* bg1;
	Image* bg2;

	Kirby* kirby;
	//Monster* monster;
	Boss* boss;
};