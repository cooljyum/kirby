#pragma once

class KirbyAttackEat : public Action
{
public:
	KirbyAttackEat(Rect* owner);
	~KirbyAttackEat();

	void Start(bool isRight)override;
	void End() override;
};