#pragma once
class KirbyRun : public Action
{
public:
	KirbyRun(Rect* owner);
	~KirbyRun();

	void Update();

private: 
	void Control();

};