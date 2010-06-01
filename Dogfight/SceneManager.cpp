#include "SceneManager.h"
#include "AeroplaneEntity.h"
#include "AppSettings.h"

SceneManager::SceneManager(void):
	_sceneImageSprite(NULL),
	_eventListener(NULL),
	_environementProvider(NULL),
	_renderWindow(NULL),
	_stepBeginMethod(NULL),
	_stepEndMethod(NULL),
	_sceneView(NULL)
{
	//Create instances
	_renderWindow = new sf::RenderWindow(sf::VideoMode(800,600, 32), "== Dogfight ==");
	_sceneView = new sf::View(sf::FloatRect(0,0,800,600));
	_eventListener = new EventListener(_renderWindow);
	_environementProvider = new EnvironementProvider();

	_sceneImageSprite = new sf::Sprite(*_environementProvider->GetSceneImage(), sf::Vector2f(0.f,0.f));
	GetEnvironementProvider()->GetAeroplaneArray()[0] = new AeroplaneEntity();

	_renderWindow->UseVerticalSync(true);
	_renderWindow->SetFramerateLimit(60);
}


SceneManager::~SceneManager(void)
{
	if(_renderWindow != NULL && _renderWindow->IsOpened())
		_renderWindow->Close();

	DeleteReference(_sceneImageSprite);
	DeleteReference(_eventListener);
	DeleteReference(_environementProvider);
	DeleteReference(_renderWindow);
	DeleteReference(_sceneView);
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
	Think(_environementProvider->GetAeroplaneArray()[0]);

	//Set view
	_renderWindow->SetView(*_sceneView);
	_sceneView->SetCenter(sf::Vector2f(
		GetEnvironementProvider()->GetAeroplaneArray()[0]->GetPosition().x,
		std::min<float>(GetEnvironementProvider()->GetAeroplaneArray()[0]->GetPosition().y,_renderWindow->GetHeight()/2.f)));

	//Draw methods
	_renderWindow->Clear(sf::Color(150,186,219));
	Draw(_sceneImageSprite);
	Draw(GetEnvironementProvider()->GetAeroplaneArray()[0]);

	//Display renderWindow
	_renderWindow->Display();

	//Invoke end method
	if(_stepEndMethod != NULL)
		_stepEndMethod();
}


void SceneManager::Think(ObjectEntity* objectEntity)
{
	sf::Vector2f objectEntityPosition = objectEntity->GetPosition();
	float sceneWidth = (float)_environementProvider->GetSceneWidth();

	//Think
	objectEntity->Think(_eventListener, _environementProvider);

	//Check position
	if(objectEntityPosition.x > sceneWidth)
		objectEntity->SetPosition( objectEntityPosition.x - sceneWidth, objectEntityPosition.y);
	else if(objectEntityPosition.x < 0)
		objectEntity->SetPosition( objectEntityPosition.x + sceneWidth, objectEntityPosition.y);
}


void SceneManager::Draw(ObjectEntity* objectEntity)
{
	//Draw original
	objectEntity->Draw(_renderWindow);

	//Draw clones
	sf::Vector2f viewPosition = _sceneView->GetCenter();
	sf::Vector2f spritePosition = objectEntity->GetPosition();
	
	//Check Left Duplication
	if(viewPosition.x < _renderWindow->GetWidth())
	{
		objectEntity->SetPosition(spritePosition.x - _environementProvider->GetSceneWidth(), spritePosition.y);
		objectEntity->Draw(_renderWindow);
	}

	//Check Right duplication
	if(viewPosition.x > _environementProvider->GetSceneWidth() - _renderWindow->GetWidth())
	{
		objectEntity->SetPosition(spritePosition.x + _environementProvider->GetSceneWidth(), spritePosition.y);
		objectEntity->Draw(_renderWindow);
	}

	//Restore original prosition
	objectEntity->SetPosition(spritePosition);
}


void SceneManager::Draw(sf::Sprite* sprite)
{
	//Draw original
	_renderWindow->Draw(*sprite);

	//Draw clones
	sf::Vector2f viewPosition = _sceneView->GetCenter();
	sf::Vector2f spritePosition = sprite->GetPosition();
	
	//Check Left Duplication
	if(viewPosition.x < _renderWindow->GetWidth())
	{
		sprite->SetPosition(spritePosition.x - _environementProvider->GetSceneWidth(), spritePosition.y);
		_renderWindow->Draw(*sprite);
	}

	//Check Right duplication
	if(viewPosition.x > _environementProvider->GetSceneWidth() - _renderWindow->GetWidth())
	{
		sprite->SetPosition(spritePosition.x + _environementProvider->GetSceneWidth(), spritePosition.y);
		_renderWindow->Draw(*sprite);
	}

	//Restore original prosition
	sprite->SetPosition(spritePosition);
}