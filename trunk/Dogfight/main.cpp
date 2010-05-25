#include <stdlib.h>
#include <iostream>

#include "SceneManager.h"

int main(void)
{
	SceneManager sceneManager;

	do
	{
		sf::Sleep(0.01f);
		sceneManager.Step();
	}
	while(!sceneManager.GetEventListener()->GetInputClose());

	return EXIT_SUCCESS;
}