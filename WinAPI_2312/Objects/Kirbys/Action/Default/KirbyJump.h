#pragma once


class KirbyJump : public Action
{
public:
	const float JUMP_POWER = -500.0f;
	const float GRAVITY = 980.0f;
	const int MAX_JUMP = 30;

public:
	KirbyJump(Rect* owner) : Action(owner) { } ;
	~KirbyJump();

	virtual void Update();
	virtual void Start(bool isRight);

protected:
	virtual void Jump();
	virtual void Move();
	virtual void Push(bool isRight);

protected:
	static int jumpCount;
};