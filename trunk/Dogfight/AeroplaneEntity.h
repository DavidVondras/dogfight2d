#ifndef AEROPLANEENTITY_H
#define AEROPLANEENTITY_H

#include <SFML\Graphics.hpp>
#include "ObjectEntity.h"
#include "EventListener.h"
#include "EnvironementProvider.h"

///
/// Object describing aeroplanes entities
///
class AeroplaneEntity :
	public ObjectEntity
{
private:
	float _vX, _vY;

	sf::Image* _imageAeroplane;
public:
	//Initialization
	AeroplaneEntity(void);
	~AeroplaneEntity(void);

	//Properties
	float GetVX(void) { return _vX; }
	void SetVX(float value) { _vX = value; }

	float GetVY(void) { return _vY; }
	void SetVY(float value) { _vY = value; }

	//Methods
	virtual void Think(EventListener* eventListener, EnvironementProvider* environementprovider);
	virtual void Draw(sf::RenderWindow* renderWindow);
};

#endif