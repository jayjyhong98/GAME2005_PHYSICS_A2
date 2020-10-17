#pragma once
#ifndef __BALL__
#define __BALL__

#include "Sprite.h"
#include "Label.h"

class Ball final : public Sprite
{
public:
	Ball();
	~Ball();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopMoving();
	void projectileMotion();
	void setState(int x);

	bool isGravityEnabled = false;
	bool isColliding(GameObject*);
	float getDistance(GameObject*);

	inline float getf_meter() { return f_meter; } // remove ; when if defined .h
	inline void setf_meter(float m) { f_meter = m; } // m = input from users

	inline void setf_initalVel(float v) { f_initialVel = v; }// v = input from users

	inline float getInitialVel() { return initialVel; } // for label

	inline float getf_angle() { return f_angle; } // remove ; when if defined .h
	inline void setf_angle(float a) { f_angle = a; }// a = input from users

	inline float getDegAngle() { return degAngle; }

	glm::vec2 throwSpeed;

private:
	const float deltaTime = 3.0f / 60.f;

	int state = 0;
	
	const float SPEED = 100.0f;
	const float ACCELERATION = 10.0f;
	glm::vec2 m_direction;

	const float GRAVITY = 9.8f; // set const float gravity

	float currAngle; // to calculate in case of 485m and 95m/s
	float degAngle; // to display 
	glm::vec2 initialPos;
	float initialVel;
	float maxdistance;
	float GravityTime;

	float f_angle = 45.0f, f_result; // to calculate in case of input variables from users
	float f_meter = 485.0f, f_initialVel = 95.0f; // to change total meters and initial velocity(speed)
	float f_maxdistance;

	bool b_simulationStop = false;
};

#endif /* defined (__PLAYER__) */