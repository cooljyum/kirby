#pragma once

class RunningGameScene : public Scene
{
public:
	RunningGameScene();
	~RunningGameScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void Start() override;
	void End() override;

private:
	void CreateBG();

private:
	vector<Background*> backgrounds;

	Cookie* basicCookie, angelCookie;

	Cookie* cookie;	
};