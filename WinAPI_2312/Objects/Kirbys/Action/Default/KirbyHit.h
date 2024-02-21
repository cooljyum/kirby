#pragma once

class KirbyHit : public Action
{
public:
	KirbyHit(Rect* owner);
	~KirbyHit();

	void Start(bool isRight) override;
};