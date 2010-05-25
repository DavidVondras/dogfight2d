#include <SFML\Graphics.hpp>
#include "EventListener.h"

void EventListener::CheckEvents(void)
{
	//Check events
	sf::Event Event;
    while (_renderWindow->GetEvent(Event))
    {
        // close window
		_inputClose |= Event.Type == sf::Event::Closed; 

        // Escape key
        _inputClose |= (Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape);
    }

	// Directionnal keys
	_inputLeft = (_renderWindow->GetInput()).IsKeyDown(sf::Key::Left);
	_inputRight = (_renderWindow->GetInput()).IsKeyDown(sf::Key::Right);
	_inputUp = (_renderWindow->GetInput()).IsKeyDown(sf::Key::Up);
	_inputDown = (_renderWindow->GetInput()).IsKeyDown(sf::Key::Down);
}