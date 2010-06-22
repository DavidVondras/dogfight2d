#ifndef EVENTLISTNER_H
#define EVENTLISTNER_H

#include<SFML\Graphics.hpp>
#include "DashBoard.h"

//Forward declarations
class EventListener;
class EnvironementProvider;
class RenderWindow;

///
/// Base class for object entities
///
class ObjectEntity: public sf::Sprite
{
public:
	virtual void Think(EventListener* const eventListener, EnvironementProvider* const environementprovider)=0;
	virtual void Draw(sf::RenderWindow* const renderWindow)=0;
	virtual void AddDebugFields(DashBoard* const dashBoard) {}
};

#endif