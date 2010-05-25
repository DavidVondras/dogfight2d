#include <stdlib.h>
#include <iostream>

#include "SceneManager.h"

int main(void)
{
	SceneManager sceneManager;
	sf::Clock clock;
	float elapsedTime;
	float frameDuration = 1.f/30.f;

	do
	{
		clock.Reset();
		sceneManager.Step();
		elapsedTime = clock.GetElapsedTime();
		if(elapsedTime < frameDuration)
			//Do step
			sf::Sleep(frameDuration - elapsedTime);
		else
			//Notice that framerate is not supported
			std::cout<<"Warning: Framerate is too low ["<<1/25 - elapsedTime<<" secondes]"<<std::endl;
	}
	while(!sceneManager.GetEventListener()->GetInputClose());

	return EXIT_SUCCESS;
}