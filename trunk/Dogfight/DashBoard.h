#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <SFML\Graphics.hpp>
#include <string>

namespace ValueListenerType
{
	enum Type
	{
		ptr_int,
		ptr_float
	};
}

struct ValueListener
{
	void* value;
	std::string name;
	ValueListenerType::Type type;
};

class DashBoard
{
private:
	ValueListener _valueListenerArray[32];
	int _valueListenerArrayCount;
	int AddGeneric(void* valueToListen, std::string name);
public:
	DashBoard(void);
	~DashBoard(void);

	void Add(int* valueToListen, std::string name);
	void Add(float* valueToListen, std::string name);
	void Draw(sf::RenderWindow* renderWindow);
};

#endif