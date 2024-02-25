#pragma once

class KirbyDance : public Action
{
public:
	KirbyDance(Rect* owner);
	~KirbyDance();

	void Render(HDC hdc) override;

	void Start(bool isRight) override;
	void End() override;

private:
	Image* clearUI;
};