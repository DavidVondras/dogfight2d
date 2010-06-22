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
	float _zoomFactor;

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
	EventListener* const GetEventListener(void) const { return _eventListener; }
	EnvironementProvider* const GetEnvironementProvider(void) const { return _environementProvider; }
	sf::RenderWindow* const GetRenderWindow(void) const { return _renderWindow; }
	void SetStepBeginMethod(void (*value)(void)) { _stepBeginMethod = value; }
	void SetStepEndMethod(void (*value)(void)) { _stepEndMethod = value; }

	//Methods
	void Step(void);
	void Think(ObjectEntity* const objectEntity);
	void Draw(ObjectEntity* const objectEntity);
	void Draw(sf::Sprite* const sprite);
};

#endif