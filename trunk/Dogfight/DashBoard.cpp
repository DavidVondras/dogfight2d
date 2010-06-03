#include "DashBoard.h"
#include "AppSettings.h"
#include <sstream>

DashBoard::DashBoard(void)
	:_valueListenerArrayCount(0){}


DashBoard::~DashBoard(void){}


int DashBoard::AddGeneric(void* valueToListen, std::string name)
{
	if(_valueListenerArrayCount < 32)
	{
		_valueListenerArray[_valueListenerArrayCount].value = valueToListen;
		_valueListenerArray[_valueListenerArrayCount].name = name;
		return _valueListenerArrayCount++;
	}
	return -1;
}

void DashBoard::Add(int* valueToListen, std::string name)
{
	int index = AddGeneric(valueToListen, name);
	if(index >= 0)
		_valueListenerArray[index].type = ValueListenerType::ptr_int;
}


void DashBoard::Add(float* valueToListen, std::string name)
{
	int index = AddGeneric(valueToListen, name);
	if(index >= 0)
		_valueListenerArray[index].type = ValueListenerType::ptr_float;
}


void DashBoard::Draw(sf::RenderWindow* renderWindow)
{
	sf::String SFstring;
	SFstring.SetSize(11);
	SFstring.SetColor(sf::Color(0,0,0));

	for(int i=0; i < _valueListenerArrayCount; i++)
	{ 
		std::ostringstream os;
		os<<_valueListenerArray[i].name<<": ";

		switch(_valueListenerArray[i].type)
		{
			case ValueListenerType::ptr_int:
				os<<*( (int*)_valueListenerArray[i].value );
				break;
			case ValueListenerType::ptr_float:
				os<<*( (float*)_valueListenerArray[i].value );
				break;
			default: os<<"Unknown type " << _valueListenerArray[i].type;
		}

		SFstring.SetText(os.str());
		renderWindow->Draw(SFstring);
		SFstring.Move(0,15.f);
	}
}