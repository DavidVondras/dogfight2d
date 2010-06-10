#ifndef AEROPLANEENTITY_H
#define AEROPLANEENTITY_H

#include <SFML\Graphics.hpp>
#include "ObjectEntity.h"
#include "EventListener.h"
#include "EnvironementProvider.h"
#include "CollisionPoint.h"
#include "AppSettings.h"

///
/// Object describing aeroplanes entities
///
class AeroplaneEntity :
	public ObjectEntity
{
private:
	float _vX, _vY, _vXLocal, _vYLocal, _vNormal;
	float _cz;
	float _Moffset, _Melev, _MVcoef, _MVlim, _MelevCoef;
	float _rotationIncidence;
	float _vRotation;
	float _rotateValue;
	float _propelValue;
	float _czMin,_czMax, _czMaxVelocity;
	CollisionPoint* _collisionPointArray[ENTITY_MAX_COLLISIONPOINT_NB];
	int _collisionPointArrayCount;

	sf::Vector2f _Fpoid;
	sf::Vector2f _FPousee;
	sf::Vector2f _FRx;
	sf::Vector2f _FRz;

	sf::Image* _imageAeroplane;

public:
	//Initialization
	AeroplaneEntity(void);
	~AeroplaneEntity(void);

	//Methods
	virtual void Think(EventListener* eventListener, EnvironementProvider* environementprovider);
	virtual void Draw(sf::RenderWindow* renderWindow);
	virtual void AddDebugFields(DashBoard* dashBoard);
	void DrawStrengthData(sf::RenderWindow* renderWindow);
};

#endif