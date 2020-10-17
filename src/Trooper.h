#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "Sprite.h"
#include "Label.h"

class Trooper final : public Sprite
{
public:
	Trooper();
	~Trooper();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopMoving();

	bool isColliding(GameObject*);
	float getDistance(GameObject*);

	void projectileMotion(float distance, float power);

private:
	const float SPEED = 100.0f;
	const float ACCELERATION = 10.0f;
	glm::vec2 m_direction;

	const float GRAVITY = 9.8f; // set const float gravity
	const int maxAngle = sin(45); // to get max distance, a 45 degree angle is optimum

	float angle; // to calculate in case of 485m and 95m/s
	float maxdistance;
	float GravityTime;

	float f_angle, f_distance, f_power; // to calculate in case of input variables from users
};

#endif /* defined (__PLAYER__) */