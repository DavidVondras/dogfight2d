#include <iostream>
#include "AeroplaneEntity.h"


AeroplaneEntity::AeroplaneEntity(void)
{
	_imageAeroplane = NULL;
	_vX = _vY = 0;

	//Dummy data
	//_vX = 2;
	SetPosition(100,100);
	SetCenter(40,40);

	_imageAeroplane = new sf::Image();
	if(!_imageAeroplane->LoadFromFile("rafaletest.png"))
	{
		std::cerr<<"Error while loading rafaletest.png "<<std::endl;
	}
	this->SetImage(*_imageAeroplane);
}


AeroplaneEntity::~AeroplaneEntity(void)
{
	if(_imageAeroplane != NULL)
		delete _imageAeroplane;
}


void AeroplaneEntity::Think(EventListener* eventListener, EnvironementProvider* environementprovider)
{
	if(eventListener->GetInputLeft())
		SetRotation(GetRotation()+2);
	if(eventListener->GetInputRight())
		SetRotation(GetRotation()-2);
	this->Move(_vX, _vY);
}


void AeroplaneEntity::Draw(sf::RenderWindow* renderWindow)
{
	renderWindow->Draw(*this);
}