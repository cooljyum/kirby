#pragma once

class KirbyIdle: public Action
{
public:
	KirbyIdle(Rect* owner);
	~KirbyIdle();

	void Start(bool isRight) override;
};