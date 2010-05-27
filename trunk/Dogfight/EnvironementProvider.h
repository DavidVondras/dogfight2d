#ifndef ENVIRONEMENTPROVIDER_H
#define ENVIRONEMENTPROVIDER_H

#include <SFML\Graphics.hpp>
#include "ObjectEntity.h"

///
/// Provides contextual environement data
///
class EnvironementProvider
{
private:
	sf::Image* _sceneImage;
	sf::Image* _sceneCollisionMask;
	ObjectEntity* _aeroplaneArray[64];
	int _aeroplaneArrayCount;

public:
	//Initialization
	EnvironementProvider(void);
	~EnvironementProvider(void);

	//Properties
	ObjectEntity** GetAeroplaneArray(void) { return _aeroplaneArray; }
	void SetSceneImage(sf::Image* value) { _sceneImage = value; }
	sf::Image* GetSceneImage(void) { return _sceneImage; }
	int GetSceneWidth(void) { return _sceneImage->GetWidth(); }
	int GetSceneHeight(void) { return _sceneImage->GetHeight(); }
};

#endif