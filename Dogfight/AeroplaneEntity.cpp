#include <iostream>
#include <math.h>
#include "AeroplaneEntity.h"
#include "AppSettings.h"


AeroplaneEntity::AeroplaneEntity(void):
	_imageAeroplane(NULL),
	_vX(0),
	_vY(0)
{
	//Dummy data
	SetPosition(100,100);
	SetCenter(38,40);

	_imageAeroplane = new sf::Image();
	if(!_imageAeroplane->LoadFromFile("rafaletest.png"))
	{
		std::cerr<<"Error while loading rafaletest.png "<<std::endl;
	}
	this->SetImage(*_imageAeroplane);
}


AeroplaneEntity::~AeroplaneEntity(void)
{
	DeleteReference(_imageAeroplane);
}


void AeroplaneEntity::Think(EventListener* eventListener, EnvironementProvider* environementprovider)
{
	if(eventListener->GetInputLeft())
		SetRotation(GetRotation()+3);
	if(eventListener->GetInputRight())
		SetRotation(GetRotation()-3);

	_vX = (float)cos(GetRotation()*PI/180)*10;
	_vY = -(float)sin(GetRotation()*PI/180)*10;

	this->Move(_vX, _vY);
}


void AeroplaneEntity::Draw(sf::RenderWindow* renderWindow)
{
	renderWindow->Draw(*this);
}