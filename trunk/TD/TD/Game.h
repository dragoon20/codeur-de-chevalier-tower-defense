#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Field.h"


class Game
{

public:
  static void Start();

private:
  static bool IsExiting();
  static void GameLoop();

  static void ShowSplashScreen();
  static void ShowMenu();

  enum GameState { Uninitialized, ShowingSplash, Paused, 
          ShowingMenu, Playing, Exiting };
  
  static GameState _gameState;
  static sf::RenderWindow _mainWindow;
  static Field _field;
};