#pragma once

class KirbySit : public Action
{
public:
	KirbySit(Rect* owner, int state);
	~KirbySit();

	void Update() override;

	void Start(bool isRight) override;
};