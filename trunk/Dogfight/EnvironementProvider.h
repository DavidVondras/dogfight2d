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
	void SetSceneImage(sf::Image* const value) { _sceneImage = value; }
	sf::Image const* GetSceneImage(void) const { return _sceneImage; }
	int GetSceneWidth(void) const { return _sceneImage->GetWidth(); }
	int GetSceneHeight(void) const { return _sceneImage->GetHeight(); }
};

#endif