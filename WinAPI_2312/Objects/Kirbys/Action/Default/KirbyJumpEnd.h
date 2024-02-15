#pragma once

class KirbyJumpEnd : public KirbyJump
{
public:
	KirbyJumpEnd(Rect* owner, int state);
	~KirbyJumpEnd();

	void End();
private:
	void Jump() override;
private:
	float landHeight;
};