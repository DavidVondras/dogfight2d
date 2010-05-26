#include "SceneManager.h"
#include "AeroplaneEntity.h"
#include <iostream>


SceneManager::SceneManager(void)
{
	//Initialize fields
	_sceneImage = NULL;
	_sceneImageSprite = NULL;
	_eventListener = NULL;
	_environementProvider = NULL;
	_renderWindow = NULL;
	_stepBeginMethod = NULL;
	_stepEndMethod = NULL;

	//Create instances
	_sceneImage = new sf::Image();
	if(!_sceneImage->LoadFromFile("maptest.png"))
	{
		std::cerr<<"Error while loading maptest.png"<<std::endl;
	}

	_renderWindow = new sf::RenderWindow(sf::VideoMode(800,600, 32), "== Dogfight ==");
	_eventListener = new EventListener(_renderWindow);
	_environementProvider = new EnvironementProvider();

	_sceneImageSprite = new sf::Sprite(*_sceneImage, sf::Vector2f(0.f,0.f));
	GetEnvironementProvider()->GetAeroplaneArray()[0] = new AeroplaneEntity();
}


SceneManager::~SceneManager(void)
{
	if(_sceneImage != NULL)
		delete _sceneImage;
	if(_sceneImageSprite != NULL)
		delete _sceneImageSprite;
	if(_eventListener != NULL)
		delete _eventListener;
	if(_environementProvider != NULL)
		delete _environementProvider;
	if(_renderWindow != NULL)
	{
		_renderWindow->Close();
		delete _renderWindow;
	}
}


///
/// Run one step of the application
///
void SceneManager::Step(void)
{
	//Invoke begin method
	if(_stepBeginMethod != NULL)
		_stepBeginMethod();

	//Check events
	_eventListener->CheckEvents();

	//Think methods
	GetEnvironementProvider()->GetAeroplaneArray()[0]->Think(_eventListener, _environementProvider);

	//Draw methods
	_renderWindow->Clear(sf::Color(0,100,255));
	_renderWindow->Draw(*_sceneImageSprite);
	GetEnvironementProvider()->GetAeroplaneArray()[0]->Draw(_renderWindow);

	//Display renderWindow
	_renderWindow->Display();

	//Invoke end method
	if(_stepEndMethod != NULL)
		_stepEndMethod();
}