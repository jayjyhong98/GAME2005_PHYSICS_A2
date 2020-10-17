#include "Trooper.h"
#include "Util.h"
#include "TextureManager.h"
#include "EventManager.h"

Trooper::Trooper()
{
	TextureManager::Instance()->load("../Assets/textures/trooper.png", "trooper");
	
	auto size = TextureManager::Instance()->getTextureSize("trooper");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(760.0f, 460.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(TROOPER);

	GravityTime = 0.0f;
}

Trooper::~Trooper()
= default;

void Trooper::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("trooper", x, y, 0, 255, true);
}

void Trooper::update()
{
	const float deltaTime = 1.0f / 60.f;

	// for movement
	//float dirMagnitude = Util::magnitude(m_direction); 
	//if (dirMagnitude > 0)
	//{
	//	m_direction *= 1.0f / dirMagnitude;
	//	getRigidBody()->acceleration = Util::normalize(m_direction) * ACCELERATION; // Set accel
	//}
	//else if (Util::magnitude(getRigidBody()->velocity) > ACCELERATION * 0.1f)
	//{
	//	getRigidBody()->acceleration = Util::normalize(getRigidBody()->velocity) * -ACCELERATION;
	//}
	//else if (Util::magnitude(getRigidBody()->velocity) <= ACCELERATION * 0.1f)
	//{
	//		getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	//		getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	//}

	//getRigidBody()->velocity += getRigidBody()->acceleration * deltaTime; // Add it to vel

	//projectileMotion(485.0f, 95.0f);

	glm::vec2 pos = getTransform()->position;
	pos.x += getRigidBody()->velocity.x;
	if (pos.y > 460)
	{
		pos.y = 460;
		std::cout << pos.x << std::endl;
	}
	else
	{
		pos.y += getRigidBody()->velocity.y;
	}
	getTransform()->position = pos;
}

void Trooper::clean()
{

}

void Trooper::moveLeft() {
	m_direction.x = -1;
}

void Trooper::moveRight() {
	m_direction.x = 1;
}

void Trooper::moveUp() {
	m_direction.y = -1;
}

void Trooper::moveDown() {
	m_direction.y = 1;
}

void Trooper::stopMoving() {
	m_direction = glm::vec2(0.0f, 0.0f);
}

void Trooper::projectileMotion(float distance, float power)
{
	const float deltaTime = 1.0f / 60.f;

	angle = Util::projectileAngle(distance, power, GRAVITY) /** Util::Rad2Deg*/;

	GravityTime += deltaTime;

	glm::vec2 pos = getTransform()->position;

	getRigidBody()->velocity.x = power * cos(angle) * deltaTime; // x component of initial power, without wind resistance 'law of inertia' says it won't change :D

	getRigidBody()->velocity.y = (-power * sin(angle) + 0.5f * (GRAVITY) * pow(GravityTime, 2.0f)) * deltaTime; // '-power' because we want to go 'up', add total of the y-forces

	// Processes to answer questions------------------------------------------------START

	// A. To calculate angle - basic (485m and 95m/s)
	//angle = ((485.0f * GRAVITY) / pow(95.0f, 2.0f));
	//result = 0.5 * asin(angle);

	// if change some variables
	//f_angle = ((f_meter * GRAVITY) / pow(f_initalVel, 2.0f));
	//f_result = 0.5 * asin(f_angle);


	// B. To calculate maximum distance
	// *Maximum distance can be obtained by throwing at an angle of 45 degrees <<<<<<<<<<<<
	//maxdistance = ( pow(95.0f, 2.0f) * maxangle / GRAVITY);

	// if change some variables

	//f_maxdistance = (pow(f_initalVel, 2.0f) * maxangle / GRAVITY);

	// Processes to answer questions------------------------------------------------END
}

bool Trooper::isColliding(GameObject* pOther) {
	// Works for square sprites only
	float myRadius = getWidth() * 0.5f;
	float otherRadius = pOther->getWidth() * 0.5f;

	return (getDistance(pOther) <= myRadius + otherRadius);
}

float Trooper::getDistance(GameObject* pOther) {
	glm::vec2 myPos = getTransform()->position;
	glm::vec2 otherPos = pOther->getTransform()->position;

	// Use pythagorean to calculate distance c = sqrt(a^2 + b^2)
	float a = myPos.x - otherPos.x;
	float b = myPos.y - otherPos.y;
	return sqrt(a * a + b * b);
}
