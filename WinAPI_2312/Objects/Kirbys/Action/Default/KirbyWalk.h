#pragma once

class KirbyWalk : public Action
{
private:
	const float GRAVITY = 980.0f;
public:
	KirbyWalk(Rect* owner);
	~KirbyWalk();

	void Update();
	void End();
protected:
	void SetIsRun(bool isRun) { this->isRun = isRun; }
private:
	void Control();
	void Push(bool isRight);

private:
	bool isRun = true;
	float landHeight;
	
};