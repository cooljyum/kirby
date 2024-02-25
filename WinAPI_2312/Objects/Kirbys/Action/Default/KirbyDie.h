#pragma once

class KirbyDie : public Action
{
private:
	const float DIE_STAY_TIME = 3.0f;

	const float JUMP_POWER = -800.0f;
	const float GRAVITY = 980.0f;

public:
	KirbyDie(Rect* owner);
	~KirbyDie();

	void Start(bool isRight) override;

	void Update() override;

private:
	float dieStayTime = 0.0f;
};