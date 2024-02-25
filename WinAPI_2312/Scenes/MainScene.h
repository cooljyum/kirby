#pragma once

class MainScene : public Scene
{
private:
	const float KIRBY_START_OFFSET = 200.0f;
public:
	MainScene();
	~MainScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void CreateSound() override;

	void Start() override;
	void End() override;

private:
	Image* bg1;
	Image* bg2;

	Kirby* kirby;
};