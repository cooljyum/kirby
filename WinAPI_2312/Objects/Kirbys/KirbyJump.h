#pragma once

class KirbyJump : public Action
{
private:
	enum JumpState
	{
		START_L, START_R, LAND_L, LAND_R
	};

	const float JUMP_POWER = -500.0f;
	const float GRAVITY = 980.0f;
	const int MAX_JUMP = 30;

public:
	KirbyJump(Rect* owner, int state);
	~KirbyJump();

	void Update();

	void Start(bool isRight) override;
	void End() override;

private:
	void Jump();
	void Move();
	void Push(bool isRight);

private:
	float landHeight;
	int jumpCount = 0;
};