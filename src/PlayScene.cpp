#include "PlayScene.h"
#include "Game.h"
#include "Util.h"
#include "EventManager.h"

#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("background", 0, 0, 0, 255, false);
	GUI_Function();
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	std::string labelText = "";

	labelText = "Distance(m) = " + std::to_string(m_pBall->getDistance(m_pWookie));
	m_pDistanceLabel->setText(labelText);

	labelText = "Initial Velocity(m/s) = " + std::to_string(m_pBall->getInitialVel());
	m_pInitVelLabel->setText(labelText);

	labelText = "Angle(deg) = " + std::to_string(m_pBall->getDegAngle());
	m_pAngleLabel->setText(labelText);
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	m_pBall->stopMoving();

	if (EventManager::Instance().getMouseButton(RIGHT))	// set up start by click here!
	{
	}
	// Player movement by keyboard
	//if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A) || EventManager::Instance().isKeyDown(SDL_SCANCODE_D) ||
	//	EventManager::Instance().isKeyDown(SDL_SCANCODE_W) || EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	//{
	//	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A)) // Check x in put and y input seperately
	//	{
	//		m_pPlayer->moveLeft();
	//	}
	//	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	//	{
	//		m_pPlayer->moveRight();
	//	}
	//	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	//	{
	//		m_pPlayer->moveUp();
	//	}
	//	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	//	{
	//		m_pPlayer->moveDown();
	//	}
	//}
	//else {
	//	m_pPlayer->stopMoving();
	//}
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void PlayScene::start()
{
	// Background Sprite
	TextureManager::Instance()->load("../Assets/textures/background.png", "background");

	// Set GUI Title
	m_guiTitle = "Play Scene";

	// Trooper Sprite
	m_pTrooper = new Trooper();
	addChild(m_pTrooper);

	// Projectile Sprite
	m_pBall = new Ball();
	addChild(m_pBall);

	// Wookie Sprite
	m_pWookie = new Wookie();
	addChild(m_pWookie);

	// Labels
	const SDL_Color yellow = { 255, 255, 153, 255 };

	m_pScaleLabel = new Label("Scale = 1PPM         Assuming gravity is 9.8m/s^2", "Consolas", 15, yellow, glm::vec2(400.0f, 10.0f));
	m_pScaleLabel->setParent(this);
	addChild(m_pScaleLabel);

	m_pDistanceLabel = new Label("Distance", "Consolas", 25, yellow, glm::vec2(400.0f, 40.0f));
	m_pDistanceLabel->setParent(this);
	addChild(m_pDistanceLabel);

	m_pInitVelLabel = new Label("Initial Velocity", "Consolas", 25, yellow, glm::vec2(400.0f, 70.0f));
	m_pInitVelLabel->setParent(this);
	addChild(m_pInitVelLabel);

	m_pAngleLabel = new Label("Angle", "Consolas", 25, yellow, glm::vec2(400.0f, 100.0f));
	m_pAngleLabel->setParent(this);
	addChild(m_pAngleLabel);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	ImGui::Begin("Scenerio Adjuster", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if (ImGui::Button("Set to Original Problem <Question 1.a>"))
	{
		m_pBall->setState(0);
		m_pWookie->getTransform()->position.x = 275;
		m_pBall->getTransform()->position.x = m_pWookie->getTransform()->position.x;
		m_pBall->getTransform()->position.y = m_pWookie->getTransform()->position.y;
	}

	if (ImGui::Button("Set to Furthest Distance <Question 1.b>"))
	{
		m_pBall->setState(1);
		m_pBall->getTransform()->position.x = m_pWookie->getTransform()->position.x;
		m_pBall->getTransform()->position.y = m_pWookie->getTransform()->position.y;
	}

	ImGui::Separator();

	static int xWookiePos = 275;
	if (ImGui::SliderInt("Wookie's Position X", &xWookiePos, 0, 700))
	{
		m_pWookie->getTransform()->position.x = xWookiePos;
	}
	static int newVelocity = 95.0f;
	if (ImGui::SliderInt("Initial Velocity", &newVelocity, 0, 300))
	{
	}
	static int throwAngle = 45.0f;
	if (ImGui::SliderInt("Angle", &throwAngle, 0, 90))
	{
	}

	if (ImGui::Button("Throw Based off Input From Sliders"))
	{
		m_pBall->setf_initalVel(newVelocity);
		m_pBall->setf_angle(throwAngle);
		m_pBall->setState(2);
		m_pBall->getTransform()->position.x = m_pWookie->getTransform()->position.x;
		m_pBall->getTransform()->position.y = m_pWookie->getTransform()->position.y;
	}
	if (ImGui::Button("Throw to Trooper Based off Angle"))
	{
		m_pBall->setf_angle(throwAngle);
		m_pBall->setf_meter(m_pTrooper->getTransform()->position.x - m_pWookie->getTransform()->position.x);
		m_pBall->setState(3);
		m_pBall->getTransform()->position.x = m_pWookie->getTransform()->position.x;
		m_pBall->getTransform()->position.y = m_pWookie->getTransform()->position.y;
	}

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
