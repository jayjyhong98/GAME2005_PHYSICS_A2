#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Trooper.h"
#include "Ball.h"
#include "Button.h"
#include "Wookie.h"

#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:

	void GUI_Function() const;

	glm::vec2 m_mousePosition;

	Ball* m_pBall;
	Wookie* m_pWookie;
	Trooper* m_pTrooper;
	Label* m_pScaleLabel;
	Label* m_pDistanceLabel;
	Label* m_pAngleLabel;  // New label!
	Label* m_pInitVelLabel;  // New label!

	Button* m_pBackButton;
	Button* m_pNextButton;
	std::string m_guiTitle;
};

#endif /* defined (__PLAY_SCENE__) */