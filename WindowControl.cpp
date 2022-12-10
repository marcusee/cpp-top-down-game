#include "stdafx.h"
#include "WindowControl.h"
#include "MYComponents.h"
#include <iostream>

using namespace std;

WindowControl::WindowControl()
{
}

void WindowControl::lock(Entity * e)
{
	this->e = e;
}

void WindowControl::update(sf::RenderWindow & window)
{
	if (e == nullptr) return;


	auto view = window.getView();
	view.setCenter(e->get<MaterialComponent>()->sprite.getPosition());
	window.setView(view);
}



WindowControl::~WindowControl()
{
}
