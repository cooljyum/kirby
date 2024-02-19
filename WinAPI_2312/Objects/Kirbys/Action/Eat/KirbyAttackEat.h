#pragma once

class KirbyAttackEat : public KirbyAttack
{
public:
	KirbyAttackEat(Rect* owner);
	~KirbyAttackEat();



	void Start(bool isRight);
};