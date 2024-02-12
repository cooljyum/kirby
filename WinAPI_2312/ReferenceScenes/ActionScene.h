#pragma once

class ActionScene : public Scene
{
public:
	ActionScene();
	~ActionScene();
		
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void Start() override;

private:
	Robot* robot;
	Slime* slime;
};