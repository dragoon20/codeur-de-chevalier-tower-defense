#include "stdafx.h"
#include "Game.h"
#include "SplashScreen.h"
#include "MainMenu.h"

void Game::Start(void)
{
  if(_gameState != Uninitialized)
    return;

  _mainWindow.Create(sf::VideoMode(1024,768,32),"Pang!");
  _field.Load("example.txt");
  _gameState = Game::ShowingSplash;
  
  while(!IsExiting())
  {
    GameLoop();
  }

  _mainWindow.Close();
}

bool Game::IsExiting()
{
  if(_gameState == Game::Exiting) 
    return true;
  else 
    return false;
}

void Game::GameLoop()
{
  sf::Event currentEvent;
  while(_mainWindow.GetEvent(currentEvent))
  {
  
    switch(_gameState)
    {
	case Game::ShowingMenu:
		{
			ShowMenu();
			break;
		}
	case Game::ShowingSplash:
		{
			ShowSplashScreen();
			break;
		}
	 case Game::Playing:
        {
          _mainWindow.Clear(sf::Color(0,0,0));
		  _field.Draw(_mainWindow);
		  _mainWindow.Display();
        
          if(currentEvent.Type == sf::Event::Closed || currentEvent.Key.Code == sf::Key::Escape)
            {
              _gameState = Game::Exiting;
            }
          break;
        }
    }
  }
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch(result)
	{
	case MainMenu::Exit:
		_gameState = Game::Exiting;
		break;
	case MainMenu::Play:
		_gameState = Game::Playing;
		break;
	}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
Field Game::_field;