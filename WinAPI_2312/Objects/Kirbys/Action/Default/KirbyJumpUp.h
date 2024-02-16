#pragma once

class KirbyJumpUp : public KirbyJump
{
public:
	KirbyJumpUp(Rect* owner);
	~KirbyJumpUp();

	void Start(bool isRight) override;

private:
	void Jump() override;
};