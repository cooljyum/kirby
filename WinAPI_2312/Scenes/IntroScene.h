#pragma once

class IntroScene : public Scene
{
private: 
	float BASIC_FRAME_TIME = 0.03f;
	float FAST_FRAME_TIME = 0.01f;

	float BASIC_STARTINTRO_FRAME_TIME = 0.8f;
	float FAST_STARTINTRO_FRAME_TIME = 0.1f;
public:
	IntroScene();
	~IntroScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void CreateIntroFrame();
	void CreateSound() override;

	void Start() override;
	void End() override;

private:
	vector<Image*> intros;
	vector<Image*> startIntros;

	Image* startSelect;
	Image* controlSelect;

	Image* control;

	bool openControl = false;
	bool isStart = true;
	bool isStartIntro = false;

	float time; 
	float frameTime = BASIC_FRAME_TIME;

	int cnt = 0;
	int cntStartIntro = 0;
};