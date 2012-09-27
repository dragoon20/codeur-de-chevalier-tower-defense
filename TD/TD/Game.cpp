#include "stdafx.h"
#include "Game.h"
#include "SplashScreen.h"
#include "MainMenu.h"

void Game::Start(void)
{
  if(_gameState != Uninitialized)
    return;

  _mainWindow.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32),"La tour de défense");
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

sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

const sf::Input& Game::GetInput() 
{
	return _mainWindow.GetInput();
}

const GameObjectManager& Game::GetGameObjectManager()
{
	return _gameObjectManager;
}


void Game::GameLoop()
{
  sf::Event currentEvent;
  _mainWindow.GetEvent(currentEvent);
  
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
		  
		  _gameObjectManager.UpdateAll();
		  _gameObjectManager.DrawAll(_mainWindow);
		  
		  _mainWindow.Display();
		  if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

		  if(currentEvent.Type == sf::Event::KeyPressed)
			{
				if(currentEvent.Key.Code == sf::Key::Escape) ShowMenu();
			}

		  break;
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
	case MainMenu::Play1:
		_gameState = Game::Playing;
		break;
	}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
Field Game::_field;