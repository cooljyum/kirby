#pragma once

class KirbyWalk : public Action
{
private:
	const float GRAVITY = 980.0f;
public:
	KirbyWalk(Rect* owner, int state);
	~KirbyWalk();

	void Update();
	void End();
private:
	void Control();
	void Push(bool isRight);

private:
	float landHeight;
};