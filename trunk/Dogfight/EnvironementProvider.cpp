#include <iostream>
#include "EnvironementProvider.h"
#include "AppSettings.h"


EnvironementProvider::EnvironementProvider(void)
	:_aeroplaneArrayCount(0),
	_sceneImage(NULL),
	_sceneCollisionMask(NULL)
{
	_sceneImage = new sf::Image();
	if(!_sceneImage->LoadFromFile("maptest.png"))
	{
		std::cerr<<"Error while loading maptest.png"<<std::endl;
	}

	for(int i=0; i<64;i++)
		_aeroplaneArray[i] = NULL;
}


EnvironementProvider::~EnvironementProvider(void)
{
	DeleteReference(_sceneImage);
	DeleteReference(_sceneCollisionMask);

	for(int i=0;i<64;i++)
		if(_aeroplaneArray[i] != NULL)
			delete _aeroplaneArray[i];
}
