#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include<SFML\Graphics.hpp>

#include"EventListener.h"
#include"EnvironementProvider.h"
#include "DashBoard.h"


///
/// Scene manager class. Manages all scene elements
///
class SceneManager
{
private:
	float _frameRate;

	sf::Sprite* _sceneImageSprite;
	sf::RenderWindow* _renderWindow;
	sf::View* _sceneView;

	EventListener* _eventListener;
	EnvironementProvider* _environementProvider;
	DashBoard* _dashboard;

	void (*_stepBeginMethod)(void);
	void (*_stepEndMethod)(void);

public:
	//Initialization
	SceneManager(void);
	~SceneManager(void);

	//Properties
	EventListener* GetEventListener(void) { return _eventListener; }
	EnvironementProvider* GetEnvironementProvider(void) { return _environementProvider; }
	sf::RenderWindow* GetRenderWindow(void) { return _renderWindow; }
	void SetStepBeginMethod(void (*value)(void)) { _stepBeginMethod = value; }
	void SetStepEndMethod(void (*value)(void)) { _stepEndMethod = value; }

	//Methods
	void Step(void);
	void Think(ObjectEntity* objectEntity);
	void Draw(ObjectEntity* objectEntity);
	void Draw(sf::Sprite* sprite);
};

#endif