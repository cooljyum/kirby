#pragma once

class EndScene : public Scene
{
private:
	float BASIC_FRAME_TIME = 0.8f;
	float FAST_FRAME_TIME = 0.1f;
public:
	EndScene();
	~EndScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void Start() override; 

	void CreateIntroFrame() override;
	void CreateSound() override;

	void CloseWindow();

private:
	vector<Image*> endings;

	Image* endingImg;
	Image* gameoverImg;
	
	float time;
	float frameTime = BASIC_FRAME_TIME;

	int cnt = 0;

public:
	static bool isEnd;
};