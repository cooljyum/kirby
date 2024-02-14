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
	const int MAX_JUMP = 10;

public:
	KirbyJump(Rect* owner);
	~KirbyJump();

	void Update();

	void Start(bool isRight) override;
	void End() override;

private:
	void Jump();
	void Move();

private:
	float landHeight;
	int jumpCount = 0;
};