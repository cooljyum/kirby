#pragma once

class KirbyAttack : public Action
{
public:
	KirbyAttack(Rect* owner);
	~KirbyAttack();

	void Render(HDC hdc) override;
	void Update() override;

	void Start(bool isRight) override;


protected:
	Rect* collider;
};