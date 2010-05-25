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
	sf::Image* _sceneCollisionMask;
	ObjectEntity* _aeroplaneArray[64];

public:
	//Initialization
	EnvironementProvider(void);
	~EnvironementProvider(void);

	//Properties
	ObjectEntity** GetAeroplaneArray(void) { return _aeroplaneArray; }
};

#endif