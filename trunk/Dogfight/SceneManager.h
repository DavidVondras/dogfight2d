#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include<SFML\Graphics.hpp>

#include"EventListener.h"
#include"EnvironementProvider.h"


///
/// Scene manager class. Manages all scene elements
///
class SceneManager
{
private:
	sf::Image* _sceneImage;
	sf::Sprite* _sceneImageSprite;
	sf::RenderWindow* _renderWindow;

	EventListener* _eventListener;
	EnvironementProvider* _environementProvider;

public:
	//Initialization
	SceneManager(void);
	~SceneManager(void);

	//Properties
	EventListener* GetEventListener(void) { return _eventListener; }
	EnvironementProvider* GetEnvironementProvider(void) { return _environementProvider; }
	sf::RenderWindow* GetRenderWindow(void) { return _renderWindow; }

	//Methods
	void Step(void);
};

#endif