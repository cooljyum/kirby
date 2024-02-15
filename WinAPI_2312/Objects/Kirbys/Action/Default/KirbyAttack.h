#pragma once

class KirbyAttack : public Action
{
public:
	KirbyAttack(Rect* owner, int state);
	~KirbyAttack();

	void Render(HDC hdc) override;
	void Update() override;

	void Start(bool isRight) override;

private:
	Rect* collider;
};