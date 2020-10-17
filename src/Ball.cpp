#include "Ball.h"
#include "Util.h"
#include "TextureManager.h"
#include "EventManager.h"
using namespace std;

Ball::Ball()
{
	TextureManager::Instance()->load("../Assets/textures/circle.png", "circle");
	
	auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);

	initialPos = getTransform()->position = glm::vec2(275.0f, 460.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);

	getRigidBody()->isColliding = false;
	setType(BALL);

	GravityTime = 0.0f;
}

Ball::~Ball()
= default;

void Ball::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("circle", x, y, 0, 255, true);
}

void Ball::update()
{
	projectileMotion();
}

void Ball::clean()
{

}

void Ball::moveLeft() {
	m_direction.x = -1;
}

void Ball::moveRight() {
	m_direction.x = 1;
}

void Ball::moveUp() {
	m_direction.y = -1;
}

void Ball::moveDown() {
	m_direction.y = 1;
}

void Ball::stopMoving() {
	m_direction = glm::vec2(0.0f, 0.0f);
}

void Ball::projectileMotion()
{
	//GravityTime += deltaTime;
	if (!b_simulationStop)
	{
		getRigidBody()->velocity.y += GRAVITY * deltaTime;

		glm::vec2 pos = getTransform()->position;
		pos.x += getRigidBody()->velocity.x * deltaTime;
		pos.y += getRigidBody()->velocity.y * deltaTime;
		getTransform()->position = pos;

		if (pos.y >= 460)
		{
			getTransform()->position.y = 460.0f;
			b_simulationStop = true;
		}
	}
}

void Ball::setState(int x) // Here we can change current input data when new simulation is started
{
	state = x;
	if (state == 0) // original problem (question 1a) -> angle unknown
	{
		currAngle = Util::projectileAngle(485.0f, 95.0f, GRAVITY);
		degAngle = currAngle * Util::Rad2Deg;

		initialVel = 95.0f;
	}
	else if (state == 1) // second problem (question 1b) -> distance unknown
	{
		currAngle = 45.0f * Util::Deg2Rad;
		degAngle = 45.0; // optimal angle for max distance is 45 degrees

		initialVel = 95.0f;
	}
	else if (state == 2)// user input
	{
		currAngle = f_angle * Util::Deg2Rad;
		degAngle = f_angle; // in degrees, user input

		initialVel = f_initialVel; // set current vel to adjusted vel
	}
	else // stormtrooper lock on ->initial velocity unknown
	{
		currAngle = f_angle * Util::Deg2Rad;
		degAngle = f_angle;

		initialVel = sqrt(f_meter * GRAVITY / sin(2 * currAngle));
	}

	getRigidBody()->velocity.x = initialVel * cos(currAngle); // x component of initial power, without wind resistance 'law of inertia' says it won't change :D

	getRigidBody()->velocity.y = -initialVel * sin(currAngle); // '-power' because we want to go 'up', add total of the y-forces

	b_simulationStop = false;
}

//	 Processes to answer questions------------------------------------------------START
//
//	 A. To calculate angle - basic (485m and 95m/s)
//	 angle = ((485.0f * GRAVITY) / pow(95.0f, 2.0f));
//	 result = 0.5 * asin(angle);
//
//	 if change some variables
// 	 f_angle = ((f_meter * GRAVITY) / pow(f_initalVel, 2.0f));
//	 f_result = 0.5 * asin(f_angle);
//
//
//	 B. To calculate maximum distance
//	 *Maximum distance can be obtained by throwing at an angle of 45 degrees <<<<<<<<<<<<
//	 maxdistance = ( pow(95.0f, 2.0f) * maxangle / GRAVITY);
//
//	 if change some variables
//
//	 f_maxdistance = (pow(f_initalVel, 2.0f) * maxangle / GRAVITY);
//
//	 Processes to answer questions------------------------------------------------END

bool Ball::isColliding(GameObject* pOther) {
	// Works for square sprites only
	float myRadius = getWidth() * 0.5f;
	float otherRadius = pOther->getWidth() * 0.5f;

	return (getDistance(pOther) <= myRadius + otherRadius);
}

float Ball::getDistance(GameObject* pOther) {
	glm::vec2 myPos = getTransform()->position;
	glm::vec2 otherPos = pOther->getTransform()->position;

	// Use pythagorean to calculate distance c = sqrt(a^2 + b^2)
	float a = myPos.x - otherPos.x;
	float b = myPos.y - otherPos.y;
	return sqrt(a * a + b * b);
}
