#ifndef AEROPLANEENTITY_H
#define AEROPLANEENTITY_H

#include <SFML\Graphics.hpp>
#include "ObjectEntity.h"
#include "EventListener.h"
#include "EnvironementProvider.h"
#include "AppSettings.h"

///
/// Object describing aeroplanes entities
///
class AeroplaneEntity :
	public ObjectEntity
{
private:
	float _mass;
	sf::Vector2f _velocity;
	sf::Vector2f _velocity_local;
	float _vNormal, _vNormalQuad;
	float _cz, _cx;
	float _Moffset, _MCelev, _MVcoef, _MVlim, _MelevCoef;
	float _rotationIncidence;
	float _vRotation;
	float _rotateValue;
	float _propelValue, _propelCoef;
	float _czMin,_czMax, _czMaxVelocity;

	sf::Vector2f _landingPoint1;
	sf::Vector2f _landingPoint2;
	sf::Vector2f _landingPoint1_global;
	sf::Vector2f _landingPoint2_global;
	int _landingPoint1_isInCollision;
	int _landingPoint2_isInCollision;

	sf::Vector2f _F_weight;
	sf::Vector2f _F_propel;
	sf::Vector2f _F_Rx;
	sf::Vector2f _F_Rz;

	sf::Image* _imageAeroplane;

	//pre compute values
	float _cosRotation;
	float _sinRotation;
	float _rotationRad;

	//Methods
	inline void PreCompute();
	inline void Compute_F_propel();
	inline void Compute_F_weight();
	inline void Compute_F_Rx();
	inline void Compute_F_Rz(float ellapsedTime);

public:
	//Initialization
	AeroplaneEntity(void);
	~AeroplaneEntity(void);

	//Methods
	virtual void Think(EventListener* const eventListener, EnvironementProvider* const environementprovider);
	virtual void Draw(sf::RenderWindow* const renderWindow);
	virtual void AddDebugFields(DashBoard* const dashBoard);
	void DrawStrengthData(sf::RenderWindow* const renderWindow);
};

#endif