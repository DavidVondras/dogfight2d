#include <iostream>
#include <math.h>
#include "AeroplaneEntity.h"


AeroplaneEntity::AeroplaneEntity(void):
	_imageAeroplane(NULL),
	_vX(0),
	_vY(0),
	_vRotation(0),
	_propelValue(0),
	_collisionPointArrayCount(0),
	_czMin(0.01f),
	_czMax(0.95f),
	_czMaxVelocity(40.f)
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

#define ComputeCz(ya, xb, yb, x) 6.f*(ya-yb)*(x*x*x/3-xb*x*x/2.f)/(xb*xb*xb) + ya
void AeroplaneEntity::Think(EventListener* eventListener, EnvironementProvider* environementprovider)
{
	// Check input
	if(eventListener->GetInputLeft())
		_vRotation = 2.f;
	if(eventListener->GetInputRight())
		_vRotation = -2.f;
	if(eventListener->GetInputPropNum())
		_propelValue = eventListener->GetInputPropNumValue()*0.05f;

	// Pre compute values
	float rotationRad = GetRotation()*PI/180.f;
	float cosRotation = std::cosf(rotationRad);
	float sinRotation = std::sinf(rotationRad);

	// Local velocity
	_vXLocal = cosRotation*_vX - sinRotation*_vY;
	_vYLocal = sinRotation*_vX + cosRotation*_vY;

	// Cz
	if(_vXLocal < 0) _cz = 0.03f;
	else if(_vXLocal > 40.f) _cz = 0.95f;
	else _cz = ComputeCz(0.03f, 40.f, 0.95f, _vXLocal);

	// Weight
	_Fpoid.x =0.f;
	_Fpoid.y = -0.2f;
	
	// Propel
	_FPousee.x = cosRotation*_propelValue;
	_FPousee.y = sinRotation*_propelValue;

	// FRx
	_FRx.x = -cosRotation*_vXLocal*0.008f;
	_FRx.y = -sinRotation*_vXLocal*0.008f;
	
	// FRz
	_FRz.x = -sinRotation*_vYLocal*_cz;
	_FRz.y = cosRotation*_vYLocal*_cz;
	
	_vX += _Fpoid.x + _FPousee.x + _FRx.x + _FRz.x;
	_vY -= _Fpoid.y + _FPousee.y + _FRx.y + _FRz.y;

	_vRotation *= 0.7f;

	this->Move(_vX, _vY);
	this->Rotate(_vRotation);

	// Dummy collisions
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


void AeroplaneEntity::AddDebugFields(DashBoard* dashBoard)
{
	dashBoard->Add(&_vX, "Aeroplane Global Vx");
	dashBoard->Add(&_vY, "Aeroplane Global Vy");
	dashBoard->Add(&_vXLocal, "Aeroplane Local Vx");
	dashBoard->Add(&_vYLocal, "Aeroplane Local Vy");
	dashBoard->Add(&_propelValue, "Aeroplane Propel");
	dashBoard->Add(&_cz, "Aeroplane Cz");
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