#pragma once

class KirbyIdle: public Action
{
public:
	KirbyIdle(Rect* owner, int state = 0);
	~KirbyIdle();
};