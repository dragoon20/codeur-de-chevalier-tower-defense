#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <list>

class MainMenu
{
 
	public:
		enum MenuResult { Nothing, Exit, Help, Play1, Play2 };  
  
		struct MenuItem
		{
			public:
				sf::Rect<int> rect;
				MenuResult action;
		};
  
		MenuResult Show(sf::RenderWindow& window);

	private:
		MenuResult GetMenuResponse(sf::RenderWindow& window);
		MenuResult HandleClick(int x, int y);
		std::list<MenuItem> _menuItems;
};