#pragma once

class IntroScene : public Scene
{
private: 
	float BASIC_FRAME_TIME = 0.03f;
	float FAST_FRAME_TIME = 0.01f;
public:
	IntroScene();
	~IntroScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void CreateIntroFrame();
private:
	vector<Image*> intros;

	Image* startSelect;
	Image* controlSelect;

	Image* control;

	bool openControl = false;
	bool isStart = true;

	float time; 
	float frameTime = BASIC_FRAME_TIME;

	int cnt = 0;
};