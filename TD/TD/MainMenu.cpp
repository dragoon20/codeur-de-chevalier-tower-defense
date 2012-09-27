#include "stdafx.h"
#include "MainMenu.h"


MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{

	//Load menu image from file
	sf::Image image;
	image.LoadFromFile("images/MainScreen.png");
	sf::Sprite sprite(image);

	//Setup clickable regions

	//Play menu item coordinates
	MenuItem playButton1;
	playButton1.rect.Top= 35;
	playButton1.rect.Bottom =103;
	playButton1.rect.Left = 35;
	playButton1.rect.Right = 367;
	playButton1.action = Play1;

	MenuItem playButton2;
	playButton2.rect.Top= 130;
	playButton2.rect.Bottom = 198;
	playButton2.rect.Left = 35;
	playButton2.rect.Right = 367;
	playButton2.action = Play2;

	//Exit menu item coordinates
	MenuItem helpButton;
	helpButton.rect.Left = 0;
	helpButton.rect.Right = 1023;
	helpButton.rect.Top = 383;
	helpButton.rect.Bottom = 560;
	helpButton.action = Help;

	_menuItems.push_back(playButton1);
	_menuItems.push_back(playButton2);
	_menuItems.push_back(helpButton);

	window.Draw(sprite);
	window.Display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
  std::list<MenuItem>::iterator it;

  for ( it = _menuItems.begin(); it != _menuItems.end(); it++)
  {
    sf::Rect<int> menuItemRect = (*it).rect;
    if( menuItemRect.Bottom > y 
      && menuItemRect.Top < y 
      && menuItemRect.Left < x 
      && menuItemRect.Right > x)
      {
        return (*it).action;
      }
  }

  return Nothing;
}

MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
  sf::Event menuEvent;

  while(true)
  {

    while(window.GetEvent(menuEvent))
    {
      if(menuEvent.Type == sf::Event::MouseButtonPressed)
      {
        return HandleClick(menuEvent.MouseButton.X,menuEvent.MouseButton.Y);
      }
      if(menuEvent.Type == sf::Event::Closed)
      {
        return Exit;
      }
    }
  }
}