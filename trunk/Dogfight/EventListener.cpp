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

		if(Event.Type == sf::Event::KeyPressed)
		{
			// Escape key
			_inputClose |= (Event.Key.Code == sf::Key::Escape);

			_inputPropNum = false;
			_inputPropNumValue = false;
			switch(Event.Key.Code)
			{
			// Prop key
			case sf::Key::Num0:
				_inputPropNum = true;
				_inputPropNumValue = 0;
				break;
			case sf::Key::Num1:
				_inputPropNum = true;
				_inputPropNumValue = 1;
				break;
			case sf::Key::Num2:
				_inputPropNum = true;
				_inputPropNumValue = 2;
				break;
			case sf::Key::Num3:
				_inputPropNum = true;
				_inputPropNumValue = 3;
				break;
			case sf::Key::Num4:
				_inputPropNum = true;
				_inputPropNumValue = 4;
				break;
			case sf::Key::Num5:
				_inputPropNum = true;
				_inputPropNumValue = 5;
				break;
			case sf::Key::Num6:
				_inputPropNum = true;
				_inputPropNumValue = 6;
				break;
			case sf::Key::Num7:
				_inputPropNum = true;
				_inputPropNumValue = 7;
				break;
			case sf::Key::Num8:
				_inputPropNum = true;
				_inputPropNumValue = 8;
				break;
			case sf::Key::Num9:
				_inputPropNum = true;
				_inputPropNumValue = 9;
				break;
			default: break;
			}
		}
    }

	// Directionnal key
	_inputLeft = (_renderWindow->GetInput()).IsKeyDown(sf::Key::Left);
	_inputRight = (_renderWindow->GetInput()).IsKeyDown(sf::Key::Right);
	_inputUp = (_renderWindow->GetInput()).IsKeyDown(sf::Key::Up);
	_inputDown = (_renderWindow->GetInput()).IsKeyDown(sf::Key::Down);
}