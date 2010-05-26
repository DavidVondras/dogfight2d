#include "EnvironementProvider.h"
#include "AppSettings.h"


EnvironementProvider::EnvironementProvider(void)
	:_aeroplaneArrayCount(0),
	_sceneCollisionMask(NULL)
{
	for(int i=0; i<64;i++)
		_aeroplaneArray[i] = NULL;
}


EnvironementProvider::~EnvironementProvider(void)
{
	DeleteReference(_sceneCollisionMask);

	for(int i=0;i<64;i++)
		if(_aeroplaneArray[i] != NULL)
			delete _aeroplaneArray[i];
}
