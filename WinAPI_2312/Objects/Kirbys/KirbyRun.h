#pragma once
class KirbyRun : public Action
{
public:
	KirbyRun(Rect* owner, int state);
	~KirbyRun();

	void Update();

private: 
	void Control();

};