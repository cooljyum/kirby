#pragma once

class KirbyJumpDown : public KirbyJump
{
public:
	KirbyJumpDown(Rect* owner);
	~KirbyJumpDown();

private:
	void Jump() override;

private:
	float landHeight;
};