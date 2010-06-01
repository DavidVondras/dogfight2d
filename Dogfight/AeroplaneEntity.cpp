#include <iostream>
#include <math.h>
#include "AeroplaneEntity.h"


AeroplaneEntity::AeroplaneEntity(void):
	_imageAeroplane(NULL),
	_vX(0),
	_vY(0),
	_vRotation(0),
	_propelheaderValue(0),
	_collisionPointArrayCount(0)
{
	for(int i=0; i < ENTITY_MAX_COLLISIONPOINT_NB; i++)
		_collisionPointArray[i] = NULL;

	_imageAeroplane = new sf::Image();
	if(!_imageAeroplane->LoadFromFile("rafaletest.png"))
	{
		std::cerr<<"Error while loading rafaletest.png "<<std::endl;
	}
	this->SetImage(*_imageAeroplane);

	//Dummy data
	SetPosition(100,500);
	SetCenter(38,40);
	_collisionPointArray[0] = new CollisionPoint(0,50);
}


AeroplaneEntity::~AeroplaneEntity(void)
{
	DeleteReference(_imageAeroplane);
	for(int i=0; i < ENTITY_MAX_COLLISIONPOINT_NB; i++)
		DeleteReference(_collisionPointArray[i]);
}


void AeroplaneEntity::Think(EventListener* eventListener, EnvironementProvider* environementprovider)
{
	if(eventListener->GetInputLeft())
		_vRotation = 2.f;
	if(eventListener->GetInputRight())
		_vRotation = -2.f;
	if(eventListener->GetInputPropNum())
		_propelheaderValue = eventListener->GetInputPropNumValue()*0.05f;

	float rotationRad = GetRotation()*PI/180.f;

	_Fpoid.x =0.f;
	_Fpoid.y = -0.2f;
	
	_FPousee.x = std::cosf(GetRotation()*PI/180.f)*_propelheaderValue;
	_FPousee.y = std::sinf(GetRotation()*PI/180.f)*_propelheaderValue;

	sf::Vector2f velocityLocal = sf::Vector2f(
		std::cosf(rotationRad)*_vX - std::sinf(rotationRad)*_vY,
		std::sinf(rotationRad)*_vX + std::cosf(rotationRad)*_vY);

	_FRx.x = -std::cosf(GetRotation()*PI/180.f)*velocityLocal.x*0.008f;
	_FRx.y = -std::sinf(GetRotation()*PI/180.f)*velocityLocal.x*0.008f;
	
	_FRz.x = -std::sinf(GetRotation()*PI/180.f)*velocityLocal.y*0.3f;
	_FRz.y = std::cosf(GetRotation()*PI/180.f)*velocityLocal.y*0.3f;
	
	_vX += _Fpoid.x + _FPousee.x + _FRx.x + _FRz.x;
	_vY -= _Fpoid.y + _FPousee.y + _FRx.y + _FRz.y;
	_vRotation *= 0.7f;

	this->Move(_vX, _vY);
	this->Rotate(_vRotation);


	//Dummy collisions
	if(GetPosition().y > 550)
	{
		_vY = 0;
		SetPosition(GetPosition().x, 550);
	}
}


void AeroplaneEntity::Draw(sf::RenderWindow* renderWindow)
{
	renderWindow->Draw(*this);
	DrawStrengthData(renderWindow);
}

#define DrawStrenght(strenght) sf::Shape::Line(position, sf::Vector2f( position.x + strenght.x*200.f, position.y - strenght.y*200.f), 2, sf::Color(0,0,255));
void AeroplaneEntity::DrawStrengthData(sf::RenderWindow* renderWindow)
{
	sf::Vector2f position = GetPosition();
	sf::Shape vectorStrenght = DrawStrenght(_Fpoid);
	renderWindow->Draw(vectorStrenght);
	vectorStrenght = DrawStrenght(_FPousee);
	renderWindow->Draw(vectorStrenght);
	vectorStrenght = DrawStrenght(_FRx);
	renderWindow->Draw(vectorStrenght);
	vectorStrenght = DrawStrenght(_FRz);
	renderWindow->Draw(vectorStrenght);
	renderWindow->Draw(sf::Shape::Circle(position, 2, sf::Color(255, 0, 0)));
}