#pragma once
#include <ecstasy/core/Entity.hpp>
#include <SFML/Graphics.hpp>

using namespace ecstasy;

class WindowControl
{
private:
	Entity * e;
public:
	WindowControl();
	void lock(Entity * e);
	void update(sf::RenderWindow & window);
	~WindowControl();
};

