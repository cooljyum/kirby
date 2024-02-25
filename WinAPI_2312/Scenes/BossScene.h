#pragma once

class BossScene : public Scene
{
public:
	BossScene();
	~BossScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void CreateSound() override;

	void Start() override;
	void End() override;

private:
	Image* bg1;
	Image* bg2;

	Kirby* kirby;
	HamerBoss* boss;
};