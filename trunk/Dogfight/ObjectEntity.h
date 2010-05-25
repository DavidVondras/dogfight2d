#ifndef EVENTLISTNER_H
#define EVENTLISTNER_H

#include<SFML\Graphics.hpp>

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
	virtual void Think(EventListener* eventListener, EnvironementProvider* environementprovider)=0;
	virtual void Draw(sf::RenderWindow* renderWindow)=0;
};

#endif