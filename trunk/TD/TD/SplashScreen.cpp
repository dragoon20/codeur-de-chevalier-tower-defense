#include "StdAfx.h"
#include "SplashScreen.h"
 
 
void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
	sf::Image image;
	if(image.LoadFromFile("images/SplashScreen.jpg") != true)
	{
		return;
	}

	sf::Sprite sprite(image);
 
	renderWindow.Draw(sprite);
	renderWindow.Display();

	sf::Event event;
	long long temp = 1000000000;
	while(temp--!=0)
	{
	}
	return;
}