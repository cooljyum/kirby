#pragma once

class FlappyBirdScene : public Scene
{
public:
	FlappyBirdScene();
	~FlappyBirdScene();
		
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	void SetBackground();

private:
	map<string, Background*> backgrounds;
	Kirby* kirby;
};
