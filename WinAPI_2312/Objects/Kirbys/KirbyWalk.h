#pragma once

class KirbyWalk : public Action
{
public:
	KirbyWalk(Rect* owner);
	~KirbyWalk();

	void Update();

private:
	void Control();
};