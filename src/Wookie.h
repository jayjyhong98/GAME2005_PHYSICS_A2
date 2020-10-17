#pragma once
#ifndef __ENEMY__
#define __ENEMY__

#include "Sprite.h"

class Wookie : public Sprite
{
public:
	Wookie();
	~Wookie();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
};

#endif


