// TD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "GameObjectManager.h"
#include "Enemy.h"
#include "Tower.h"
#include "Field.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

/* ---- Bagian Menu Utama ---- */

const static int SCREEN_WIDTH = 1216;
const static int SCREEN_HEIGHT = 640;

enum GameState { Uninitialized, ShowingSplash, Paused, 
        ShowingMenu, Playing1, Playing2, Exiting, Help};
  
static GameState _gameState;
static sf::RenderWindow _mainWindow;
  
static GameObjectManager _gameObjectManager;
static Field _field;

static sf::Image	_imageTowerBlue;
static sf::Image	_imageTowerRed;
static sf::Image	_imageTowerGreen;
static sf::Sprite	_spriteTowerBlue;
static sf::Sprite	_spriteTowerRed;
static sf::Sprite	_spriteTowerGreen;

static sf::Image	_imageEnemy;
static sf::Image	_imageEnemy2;
static sf::Sprite	_spriteEnemy;
static sf::Sprite	_spriteEnemy2;

static sf::Image	_imageTile;
static sf::Sprite	_spriteTile;

static sf::Image	_imageButtonStart;
static sf::Sprite	_spriteButtonStart;

static sf::Image	_imageButtonExit;
static sf::Sprite	_spriteButtonExit;

static sf::Image	_imageButtonHelp;
static sf::Sprite	_spriteButtonHelp;

vector<Enemy> musuh;
vector<Tower> tower;
vector<sf::String> kata2;
vector<sf::Sprite> stower;

int enemygold;
int playergold;
Enemy * listmusuh;
Tower * listtower;

sf::String tPlayerM;
sf::String tEnemyM;
sf::String tMoneyP;
sf::String tMoneyE;								

stringstream convert;

void DrawTowerUpgradeInformation(Tower t);

void refresh();

bool IsExiting()
{
  if(_gameState == Exiting) 
    return true;
  else 
    return false;
}

void ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = ShowingMenu;
}

void ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch(result)
	{
		case MainMenu::Exit:
			_gameState = Exiting;
			break;
		case MainMenu::Play1:
			_gameState = Playing1;
			break;
		case MainMenu::Play2:
			_gameState = Playing2;
			break;
		case MainMenu::Help:
			_gameState = Help;
		default:break;
	}
}


/* ---- Bagian Menu Utama ---- */


/* ---- Bagian Persiapan ---- */

enum MenuResult { Nothing, Exit, Start, Menu, TowerUp, Build};

struct MenuItem
{
	sf::Rect<int> rect;
	MenuResult action;
	int id;
};

std::list<MenuItem> _menuItems;

MenuItem HandleClick(int x, int y)
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
			return (*it);
		}
	}

	MenuItem temp;
	temp.action = Nothing;

	return temp;
}

MenuItem GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while (true)
	{
		while(window.GetEvent(menuEvent))
		{
			if(menuEvent.Type == sf::Event::MouseButtonPressed)
			{
				int x = menuEvent.MouseButton.X/64;
				int y = menuEvent.MouseButton.Y/64;

				if (x<16)
				{
					bool cekluar = true;
					sf::Event even;

					refresh();
					sf::Sprite temp;
					temp.SetColor(sf::Color(0,0,255,64));
					temp.SetScaleX(64);
					temp.SetScaleY(64);
					temp.SetPosition(x*64,y*64);
					window.Draw(temp);

					bool cek = true;
					int j = 0;
					while ((cek)&&(j<tower.size()))
					{
						if ((tower[j].getX()==x)&&(tower[j].getY()==y))
						{
							cek = false;
						}
						j++;
					}

					j--;

					if (j!=-1)
					{
						cout << tower[j].getNama();
						if ((tower[j].getNama()!="Blaze")&&(tower[j].getNama()!="Torrent")&&(tower[j].getNama()!="Meadow"))
						{
							DrawTowerUpgradeInformation(tower[j]);
						
							sf::Image img;
							img.LoadFromFile("images/button_upgrade.png");
							sf::Sprite temp2;
							temp2.SetImage(img);
							temp2.SetPosition(16*64+20,500);
							window.Draw(temp2);

							img.LoadFromFile("images/button_cancel.png");
							sf::Sprite temp3;
							temp3.SetImage(img);
							temp3.SetPosition(16*64+20,550);
							window.Draw(temp3);

							_mainWindow.Display();

							while (cekluar)
							{
								_mainWindow.GetEvent(even);
						
								if (even.Type==sf::Event::MouseButtonReleased)
								{
									int tempx = even.MouseButton.X;
									int tempy = even.MouseButton.Y;

									if ((tempx>16*64+20)&&(tempx<16*64+174)&&(tempy>500)&&(tempy<535))
									{
										cekluar = false;
										tower[j] = tower[j].Upgrade(tower[j].getUpgradelist(tower[j].getNama())[0].getNama());
									}

									if ((tempx>16*64+20)&&(tempx<16*64+174)&&(tempy>550)&&(tempy<585))
									{
										cekluar = false;
									}
								}
						
							}
						}
					}
					else
					{
						_mainWindow.Display();
					}					
				}
				else
					return HandleClick
						(menuEvent.MouseButton.X,menuEvent.MouseButton.Y);
			}
			if(menuEvent.Type == sf::Event::Closed)
			{
				MenuItem temp;
				temp.action = Exit;
				return temp;
			}
			if(menuEvent.Type == sf::Event::MouseMoved)
			{
				int x = menuEvent.MouseMove.X;
				int y = menuEvent.MouseMove.Y;
				bool cektemp = true;

				std::list<MenuItem>::iterator it;

				for ( it = _menuItems.begin(); it != _menuItems.end(); it++)
				{
					sf::Rect<int> menuItemRect = (*it).rect;
					if( menuItemRect.Bottom > y 
						&& menuItemRect.Top < y 
						&& menuItemRect.Left < x 
						&& menuItemRect.Right > x)
					{
						if ((*it).action==Start)
						{
							_spriteButtonStart.SetColor(sf::Color(255, 255, 255, 128));
							cektemp = false;
						}
						else if ((*it).action==Exit)
						{
							_spriteButtonExit.SetColor(sf::Color(255, 255, 255, 128));
							cektemp = false;
						}
					}
				}
				if (cektemp)
				{
					{
						_spriteButtonStart.SetColor(sf::Color(255, 255, 255, 255));
						_spriteButtonExit.SetColor(sf::Color(255, 255, 255, 255));
					}
				}

				MenuItem temp;
				temp.action = Nothing;
				return temp;
			}
		}
	}
}

void refresh()
{
	_mainWindow.Clear();
	_field.Draw(_mainWindow);

	for (int i=0;i<tower.size();++i){
		if (tower[i].getNama()=="Splash"){
			_spriteTowerBlue.SetSubRect(sf::IntRect(0, 0, 64, 64));
			_spriteTowerBlue.SetCenter(32, 32);
			_spriteTowerBlue.SetPosition(tower[i].getX()*64+32, tower[i].getY()*64+32);
			_mainWindow.Draw(_spriteTowerBlue);
		} else if (tower[i].getNama()=="Ember"){
			_spriteTowerRed.SetSubRect(sf::IntRect(0, 0, 64, 64));
			_spriteTowerRed.SetCenter(32, 32);
			_spriteTowerRed.SetPosition(tower[i].getX()*64+32, tower[i].getY()*64+32);
			_mainWindow.Draw(_spriteTowerRed);
		} else if (tower[i].getNama()=="Sprout"){
			_spriteTowerGreen.SetSubRect(sf::IntRect(0, 0, 64, 64));
			_spriteTowerGreen.SetCenter(32, 32);
			_spriteTowerGreen.SetPosition(tower[i].getX()*64+32, tower[i].getY()*64+32);
			_mainWindow.Draw(_spriteTowerGreen);
		} else if (tower[i].getNama()=="Torrent"){
			_spriteTowerBlue.SetSubRect(sf::IntRect(64, 0, 128, 64));
			_spriteTowerBlue.SetCenter(32, 32);
			_spriteTowerBlue.SetPosition(tower[i].getX()*64+32, tower[i].getY()*64+32);
			_mainWindow.Draw(_spriteTowerBlue);
		} else if (tower[i].getNama()=="Blaze"){
			_spriteTowerRed.SetSubRect(sf::IntRect(64, 0, 128, 64));
			_spriteTowerRed.SetCenter(32, 32);
			_spriteTowerRed.SetPosition(tower[i].getX()*64+32, tower[i].getY()*64+32);
			_mainWindow.Draw(_spriteTowerRed);
		} else if (tower[i].getNama()=="Meadow"){
			_spriteTowerGreen.SetSubRect(sf::IntRect(64, 0, 128, 64));
			_spriteTowerGreen.SetCenter(32, 32);
			_spriteTowerGreen.SetPosition(tower[i].getX()*64+32, tower[i].getY()*64+32);
			_mainWindow.Draw(_spriteTowerGreen);
		}
	}

	_mainWindow.Draw(_spriteButtonStart);
	_mainWindow.Draw(_spriteButtonExit);

	convert.str("");
	convert << enemygold;

	tMoneyE.SetText(convert.str());
	_mainWindow.Draw(tMoneyE);

	convert.str("");
	convert << playergold;

	tMoneyP.SetText(convert.str());
	_mainWindow.Draw(tMoneyP);

	for (int i=0;i<kata2.size();++i)
	{
		_mainWindow.Draw(kata2[i]);
	}

	for (int i=0;i<stower.size();++i)
	{
		_mainWindow.Draw(stower[i]);
	}
}

void DrawTowerUpgradeInformation(Tower t)
{
	sf::Sprite temp;
	temp.SetColor(sf::Color(255,255,255));
	temp.SetScaleX(160);
	temp.SetScaleY(350);
	temp.SetPosition(16*64+16,275);
	_mainWindow.Draw(temp);

	sf::String temps;
	temps.SetColor(sf::Color(0,0,0));
	temps.SetSize(18);

	temps.SetText("Nama :");
	temps.SetPosition(16*64+24,300);
	_mainWindow.Draw(temps);

	temps.SetText("Attack :");
	temps.SetPosition(16*64+24,335);
	_mainWindow.Draw(temps);

	temps.SetText("Range :");
	temps.SetPosition(16*64+24,370);
	_mainWindow.Draw(temps);

	temps.SetText("Elemen :");
	temps.SetPosition(16*64+24,405);
	_mainWindow.Draw(temps);

	temps.SetText("Price :");
	temps.SetPosition(16*64+24,440);
	_mainWindow.Draw(temps);
												
	temps.SetText(t.getUpgradelist(t.getNama())[0].getNama());
	temps.SetPosition(16*64+96,300);
	_mainWindow.Draw(temps);

	convert.str("");
	convert << t.getUpgradelist(t.getNama())[0].getAttack();
	temps.SetText(convert.str());
	temps.SetPosition(16*64+96,335);
	_mainWindow.Draw(temps);

	convert.str("");
	convert << t.getUpgradelist(t.getNama())[0].getRange();
	temps.SetText(convert.str());
	temps.SetPosition(16*64+96,370);
	_mainWindow.Draw(temps);

	temps.SetText(t.getUpgradelist(t.getNama())[0].getElement());
	temps.SetPosition(16*64+96,405);
	_mainWindow.Draw(temps);

	convert.str("");
	convert << t.getUpgradelist(t.getNama())[0].getPrice();
	temps.SetText(convert.str());
	temps.SetPosition(16*64+96,440);
	_mainWindow.Draw(temps);
}

void DrawTowerInformation(int tempi)
{
	sf::Sprite temp;
	temp.SetColor(sf::Color(255,255,255));
	temp.SetScaleX(160);
	temp.SetScaleY(350);
	temp.SetPosition(16*64+16,275);
	_mainWindow.Draw(temp);

	sf::String temps;
	temps.SetColor(sf::Color(0,0,0));
	temps.SetSize(18);

	temps.SetText("Nama :");
	temps.SetPosition(16*64+24,300);
	_mainWindow.Draw(temps);

	temps.SetText("Attack :");
	temps.SetPosition(16*64+24,335);
	_mainWindow.Draw(temps);

	temps.SetText("Range :");
	temps.SetPosition(16*64+24,370);
	_mainWindow.Draw(temps);

	temps.SetText("Elemen :");
	temps.SetPosition(16*64+24,405);
	_mainWindow.Draw(temps);

	temps.SetText("Price :");
	temps.SetPosition(16*64+24,440);
	_mainWindow.Draw(temps);
												
	temps.SetText(listtower[tempi].getNama());
	temps.SetPosition(16*64+96,300);
	_mainWindow.Draw(temps);

	convert.str("");
	convert << listtower[tempi].getAttack();
	temps.SetText(convert.str());
	temps.SetPosition(16*64+96,335);
	_mainWindow.Draw(temps);

	convert.str("");
	convert << listtower[tempi].getRange();
	temps.SetText(convert.str());
	temps.SetPosition(16*64+96,370);
	_mainWindow.Draw(temps);

	temps.SetText(listtower[tempi].getElement());
	temps.SetPosition(16*64+96,405);
	_mainWindow.Draw(temps);

	convert.str("");
	convert << listtower[tempi].getPrice();
	temps.SetText(convert.str());
	temps.SetPosition(16*64+96,440);
	_mainWindow.Draw(temps);
}


/* ---- Bagian Persiapan ---- */

/* Program Utama */

int main()
{
	// variabel
	enemygold = 100;
	playergold = 100;
	listmusuh = getEnemylist();
	listtower = getTowerList();

	bool cekpersiapan;
	bool cekwave;

	if(_gameState != Uninitialized)
		return 0;

	_mainWindow.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32),"Space Defender");
	_mainWindow.SetFramerateLimit(40);
	_field.Load("example.txt");
	
	_imageTowerRed.LoadFromFile("images/tower_red.png");
	_imageTowerBlue.LoadFromFile("images/tower_blue.png");
	_imageTowerGreen.LoadFromFile("images/tower_green.png");
	_spriteTowerRed.SetImage(_imageTowerRed);
	_spriteTowerRed.SetSubRect(sf::IntRect(0,0,64,64));
	_spriteTowerRed.SetPosition(16*64+64, 300);
	_spriteTowerBlue.SetImage(_imageTowerBlue);
	_spriteTowerBlue.SetSubRect(sf::IntRect(0,0,64,64));
	_spriteTowerBlue.SetPosition(16*64+64, 400);
	_spriteTowerGreen.SetImage(_imageTowerGreen);
	_spriteTowerGreen.SetSubRect(sf::IntRect(0,0,64,64));
	_spriteTowerGreen.SetPosition(16*64+64, 500);

	stower.push_back(_spriteTowerRed);
	stower.push_back(_spriteTowerBlue);
	stower.push_back(_spriteTowerGreen);

	_imageEnemy.LoadFromFile("images/aliens.png");
	_spriteEnemy.SetImage(_imageEnemy);
	_imageEnemy2.LoadFromFile("images/aliens2.png");
	_spriteEnemy2.SetImage(_imageEnemy2);
	sf::Shape HP, aHP;
	int c = 0; 
	int r = 0;
	bool facingRight = false;
	 
	//button
	_imageButtonStart.LoadFromFile("images/button_start.png");
	_spriteButtonStart.SetImage(_imageButtonStart);
	_spriteButtonStart.SetPosition(16*64+20, 10);

	_imageButtonExit.LoadFromFile("images/button_exit.png");
	_spriteButtonExit.SetImage(_imageButtonExit);
	_spriteButtonExit.SetPosition(16*64+20, 65);

	_gameState = ShowingMenu;
  
	//Inisialisasi bagian2
	tPlayerM.SetText("Player Money: ");
	tPlayerM.SetSize(20);
	tPlayerM.SetColor(sf::Color(255,255,255));
	tPlayerM.SetPosition(16*64+20,155);
	kata2.push_back(tPlayerM);

	tEnemyM.SetText("Enemy Money: ");
	tEnemyM.SetSize(20);
	tEnemyM.SetColor(sf::Color(255,255,255));
	tEnemyM.SetPosition(16*64+20,205);
	kata2.push_back(tEnemyM);

	//Bikin tombol-tombol menu
	MenuItem startButton;
	startButton.rect.Top= 10;
	startButton.rect.Bottom = 48;
	startButton.rect.Left = 16*64+20;
	startButton.rect.Right = 16*64+173;
	startButton.action = Start;
	_menuItems.push_back(startButton);
					
	MenuItem exitButton;
	exitButton.rect.Top= 65;
	exitButton.rect.Bottom = 102;
	exitButton.rect.Left = 16*64+20;
	exitButton.rect.Right = 16*64+173;
	exitButton.action = Exit;
	_menuItems.push_back(exitButton);

	MenuItem towerButton1;
	towerButton1.rect.Top= 300;
	towerButton1.rect.Bottom = 364;
	towerButton1.rect.Left = 16*64+64;
	towerButton1.rect.Right = 16*64+128;
	towerButton1.action = Build;
	towerButton1.id = 1;
	_menuItems.push_back(towerButton1);

	MenuItem towerButton2;
	towerButton2.rect.Top= 400;
	towerButton2.rect.Bottom = 464;
	towerButton2.rect.Left = 16*64+64;
	towerButton2.rect.Right = 16*64+128;
	towerButton2.action = Build;
	towerButton2.id = 2;
	_menuItems.push_back(towerButton2);

	MenuItem towerButton3;
	towerButton3.rect.Top= 500;
	towerButton3.rect.Bottom = 564;
	towerButton3.rect.Left = 16*64+64;
	towerButton3.rect.Right = 16*64+128;
	towerButton3.action = Build;
	towerButton3.id = 3;
	_menuItems.push_back(towerButton3);

	tMoneyE.SetSize(20);
	tMoneyE.SetColor(sf::Color(255,255,255));
	tMoneyE.SetPosition(16*64+40,230);

	tMoneyP.SetSize(20);
	tMoneyP.SetColor(sf::Color(255,255,255));
	tMoneyP.SetPosition(16*64+40,180);

	
	vector<pair<int,int>> pathtower;
	pathtower.push_back(make_pair(0,3));
	pathtower.push_back(make_pair(1,3));
	pathtower.push_back(make_pair(2,3));
	pathtower.push_back(make_pair(2,4));
	pathtower.push_back(make_pair(2,5));
	pathtower.push_back(make_pair(2,6));
	pathtower.push_back(make_pair(2,7));
	pathtower.push_back(make_pair(2,8));
	pathtower.push_back(make_pair(4,9));
	pathtower.push_back(make_pair(4,8));
	pathtower.push_back(make_pair(4,7));
	pathtower.push_back(make_pair(4,6));
	pathtower.push_back(make_pair(4,5));
	pathtower.push_back(make_pair(4,4));
	pathtower.push_back(make_pair(4,3));
	pathtower.push_back(make_pair(4,2));
	pathtower.push_back(make_pair(4,1));
	pathtower.push_back(make_pair(6,0));
	pathtower.push_back(make_pair(6,1));
	pathtower.push_back(make_pair(6,2));
	pathtower.push_back(make_pair(6,3));
	pathtower.push_back(make_pair(6,4));
	pathtower.push_back(make_pair(6,5));
	pathtower.push_back(make_pair(6,6));
	pathtower.push_back(make_pair(6,7));
	pathtower.push_back(make_pair(6,8));
	pathtower.push_back(make_pair(8,9));
	pathtower.push_back(make_pair(8,8));
	pathtower.push_back(make_pair(8,7));
	pathtower.push_back(make_pair(8,6));
	pathtower.push_back(make_pair(8,5));
	pathtower.push_back(make_pair(8,4));
	pathtower.push_back(make_pair(8,3));
	pathtower.push_back(make_pair(8,2));
	pathtower.push_back(make_pair(8,1));
	pathtower.push_back(make_pair(10,0));
	pathtower.push_back(make_pair(10,1));
	pathtower.push_back(make_pair(10,2));
	pathtower.push_back(make_pair(10,3));
	pathtower.push_back(make_pair(10,4));
	pathtower.push_back(make_pair(10,5));
	pathtower.push_back(make_pair(10,6));
	pathtower.push_back(make_pair(10,7));
	pathtower.push_back(make_pair(10,8));
	pathtower.push_back(make_pair(12,9));
	pathtower.push_back(make_pair(12,8));
	pathtower.push_back(make_pair(12,7));
	pathtower.push_back(make_pair(12,6));
	pathtower.push_back(make_pair(12,5));
	pathtower.push_back(make_pair(12,4));
	pathtower.push_back(make_pair(12,3));
	pathtower.push_back(make_pair(12,2));
	pathtower.push_back(make_pair(12,1));
	pathtower.push_back(make_pair(14,0));
	pathtower.push_back(make_pair(14,1));
	pathtower.push_back(make_pair(14,2));
	pathtower.push_back(make_pair(14,3));
	pathtower.push_back(make_pair(14,4));
	pathtower.push_back(make_pair(14,5));
	pathtower.push_back(make_pair(14,6));
	pathtower.push_back(make_pair(14,7));
	pathtower.push_back(make_pair(14,8));

	while(!IsExiting())
	{
		sf::Event currentEvent;
		_mainWindow.GetEvent(currentEvent);		
  
		switch(_gameState)
		{
			case ShowingMenu:
			{
				ShowMenu();
				break;
			}
			case Playing2:
			{
				refresh();
				_mainWindow.Display();


				// greedy musuh di sini
				// berdasarkan kondisi dari field saat ini
				int max=0;
				int felement[3];
				for (int i=0;i<3;++i)
					felement[i] = 0;
				for (int i=0;i<tower.size();++i)
				{
					if (tower[i].getElement()=="Fire")
					{
						if (tower[i].getNama()=="Blaze")
							felement[0]++;
						felement[0]++;
						if (felement[0]>felement[max])
							max = 0;
					}
					else if (tower[i].getElement()=="Water")
					{
						if (tower[i].getNama()=="Torrent")
							felement[1]++;
						felement[1]++;
						if (felement[1]>felement[max])
							max = 1;
					}
					else if (tower[i].getElement()=="Nature")
					{
						if (tower[i].getNama()=="Meadow")
							felement[2]++;
						felement[2]++;
						if (felement[2]>felement[max])
							max = 2;
					}
				}
				string upgrade;
				if (max==0)
				{
					max = 1;
					upgrade = "Lizardman";
				}
				else if (max==1)
				{
					max = 2;
					upgrade = "Mandragora";
				}
				else
				{
					max = 0;
					upgrade = "Salamander";
				}
				for (int i=0;i<musuh.size();++i)
				{
					if ((musuh[i].getName()!="Efreet")&&(musuh[i].getName()!="Undine")&&(musuh[i].getName()!="Dryad")&&(musuh[i].getElement()==listmusuh[max].getElement()))
					{
						if (musuh[i].getUpgradelist(musuh[i].getName())[0].getPrice()<enemygold)
						{
							musuh[i] = musuh[i].Upgrade(musuh[i].getUpgradelist(musuh[i].getName())[0].getName());
							enemygold -= musuh[i].getPrice();
						}
					}
				}
				while (listmusuh[max].getPrice()<enemygold)
				{
					musuh.push_back(Enemy(listmusuh[max].getName()));
					enemygold -= listmusuh[max].getPrice();
					if (musuh[musuh.size()-1].getUpgradelist(musuh[musuh.size()-1].getName())[0].getPrice()<enemygold)
					{
						musuh[musuh.size()-1] = musuh[musuh.size()-1].Upgrade(musuh[musuh.size()-1].getUpgradelist(musuh[musuh.size()-1].getName())[0].getName());
						enemygold -= musuh[musuh.size()-1].getPrice();
					}
				}

				cout << "Susunan musuh: " << endl;
				for (int i=0;i<musuh.size();++i)
				{
					cout << musuh[i].getName() << endl;
				}

				// greedy tower di sini
				for (int i=0;i<3;++i)
					felement[i] = 0;
				for (int i=0;i<musuh.size();++i)
				{
					if (musuh[i].getElement()=="Fire")
					{
						if (musuh[i].getName()=="Efreet")
							felement[0]++;
						felement[0]++;
						if (felement[0]>felement[max])
							max = 0;
					}
					else if (musuh[i].getElement()=="Water")
					{
						if (musuh[i].getName()=="Undine")
							felement[1]++;
						felement[1]++;
						if (felement[1]>felement[max])
							max = 1;
					}
					else if (musuh[i].getElement()=="Nature")
					{
						if (musuh[i].getName()=="Dryad")
							felement[2]++;
						felement[2]++;
						if (felement[2]>felement[max])
							max = 2;
					}
				}
				upgrade;
				if (max==0)
				{
					max = 1;
					upgrade = "Splash";
				}
				else if (max==1)
				{
					max = 2;
					upgrade = "Sprout";
				}
				else
				{
					max = 0;
					upgrade = "Blaze";
				}

				int j = 0;
				for (int k=0;k<tower.size();++k)
				{
					if ((tower[k].getNama()!="Blaze")&&(tower[k].getNama()!="Torrent")&&(tower[k].getNama()!="Meadow")&&(tower[k].getElement()==listtower[max].getElement()))
					{
						if (tower[k].getUpgradelist(tower[k].getNama())[0].getPrice()<playergold)
						{
							cout << "Tower " << tower[k].getNama() << "(" << tower[k].getX() << "," << tower[k].getY() << ") diupgrade" << endl;
							tower[k] = tower[k].Upgrade(tower[k].getUpgradelist(tower[k].getNama())[0].getNama());
							playergold -= tower[k].getPrice();
						}
					}
				}

				while ((pathtower.size()>0)&&(listtower[max].getPrice()<playergold))
				{
					tower.push_back(Tower(pathtower[0].first,pathtower[0].second,listtower[max].getNama()));
					if (tower[tower.size()-1].getUpgradelist(tower[tower.size()-1].getNama())[0].getPrice()<enemygold)
					{
						tower[tower.size()-1] = tower[tower.size()-1].Upgrade(tower[tower.size()-1].getUpgradelist(tower[tower.size()-1].getNama())[0].getNama());
					}
					enemygold -= musuh[musuh.size()-1].getPrice();
					_field.setNode(pathtower[0].second,pathtower[0].first,'X');
					pathtower.erase(pathtower.begin());
					playergold-=listtower[max].getPrice();
				}
			
				// menentukan jalur yang ingin dilalui musuh dengan djikstra
				vector<int> path = _field.getPath();

				int pathsize = path.size();// field.getPath().size;
				for (int j=musuh.size()-1;j>=0;--j)
				{
					// set urutan, darah, kecepatan, posisi musuh dan musuh dapat pemasukan
					musuh[j].setPos(j*-1-1);
					musuh[j].setaHealth(musuh[j].getHealth());
					musuh[j].setaSpeed(musuh[j].getSpeed());
					musuh[j].setX(-1);
					musuh[j].setY(4);
					enemygold += musuh[j].getIncome();
				}				

				_spriteButtonStart.SetColor(sf::Color(255, 255, 255, 128));
					
				
				// 
			
				cout << "Wave Start" << endl;

				cekwave = true;
				while (cekwave)
				{
					// penyerangan
					for (int i=0;i<tower.size();++i)
					{
						bool cekmusuh = true;
						if ((tower[i].getTarget()!=-1)&&(musuh[tower[i].getTarget()].getaHealth()>0)&&(abs(tower[i].getX()-musuh[tower[i].getTarget()].getX())+abs(tower[i].getY()-musuh[tower[i].getTarget()].getY())<=tower[i].getRange()))
						// tower sudah ada target dan musuh masih dalam range
						{
							int j = tower[i].getTarget();
							tower[i].attack(&musuh[j]);

							cout << "Tower " << tower[i].getNama() << "(" << tower[i].getX() << "," << tower[i].getY() << ") menyerang " << musuh[j].getName()<< " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ")" << endl;
							cout << "Darah " << musuh[j].getName() << " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ") tinggal " << musuh[j].getaHealth() << endl;

							if (musuh[j].getaHealth()<=0)
							{
								cout << "Tower "<< tower[i].getNama() << "(" << tower[i].getX() << "," << tower[i].getY() << ") menyerang " << musuh[j].getName()<< " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ")" << endl;
								/*float difX = tower[i].getX() - musuh[j].getX();
								float difY = tower[i].getY() - musuh[j].getY();
								tower[i].setAngle(atan(difX/difY));
								if (tower[i].getNama()=="Splash"){
									if (musuh[j].getY() <= tower[i].getY()){ //musuh di sebelah atas tower
										tower[i].setAngle(atan(difX/difY));
									} else if (musuh[j].getY() > tower[i].getY()){ //musuh di sebelah bawah tower
										tower[i].setAngle(atan(difX/difY) + 180.0);
									}
								} else if (tower[i].getNama()=="Ember"){
									if (musuh[j].getY() <= tower[i].getY()){ //musuh di sebelah atas tower
										_spriteTowerRed.SetRotation(atan(difX/difY));
									} else if (musuh[j].getY() > tower[i].getY()){ //musuh di sebelah bawah tower
										_spriteTowerRed.SetRotation(atan(difX/difY) + 180.0);
									}
								} else if (tower[i].getNama()=="Sprout"){
									if (musuh[j].getY() <= tower[i].getY()){ //musuh di sebelah atas tower
										_spriteTowerRed.SetRotation(atan(difX/difY));
									} else if (musuh[j].getY() > tower[i].getY()){ //musuh di sebelah bawah tower
										_spriteTowerRed.SetRotation(atan(difX/difY) + 180.0);
									}
								}*/

								j = tower[i].getTarget();
								tower[i].attack(&musuh[j]);
								if (musuh[j].getaHealth()<=0)
								{
									// musuh mati dan player dapat uang
									playergold += musuh[j].getReward();
									tower[i].setTarget(-1);
									cout << "Monster " << musuh[j].getName() << " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ")" << " tewas" << endl;
								}
							}
						}
						else
						{	
							int j = 0;
							while ((cekmusuh)&&(j<musuh.size()))
							{
								if ((musuh[j].getaHealth()>0)&&(abs(tower[i].getX()-musuh[j].getX())+abs(tower[i].getY()-musuh[j].getY())<=tower[i].getRange()))
								// jika tower dapat menyerang musuh (dalam jangkauan) dann tower sedang tidak ada target 
								// health musuh berkurang
								{
									tower[i].setTarget(j);
									tower[i].attack(&musuh[j]);
								
									cout << "Tower "<< tower[i].getNama() << "(" << tower[i].getX() << "," << tower[i].getY() << ") menyerang " << musuh[j].getName() << " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ")" << endl;
									cout << "Darah " << musuh[j].getName() << " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ") tinggal " << musuh[j].getaHealth() << endl;

									if (musuh[j].getaHealth()<=0)
									{
										cout << "Tower "<< tower[i].getNama() << "(" << tower[i].getX() << "," << tower[i].getY() << ") menyerang " << musuh[j].getName() << " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ")" << endl;
										/*float difX = tower[i].getX() - musuh[j].getX();
										float difY = tower[i].getY() - musuh[j].getY();
										if (musuh[j].getY() <= tower[i].getY()){ //musuh di sebelah atas tower
											tower[i].setAngle(atan(difY/difX));
										} else if (musuh[j].getY() > tower[i].getY()){ //musuh di sebelah bawah tower
											tower[i].setAngle(atan(difY/difX) + 180.0);
										}*/
										

										tower[i].setTarget(j);
										tower[i].attack(&musuh[j]);
										if (musuh[j].getaHealth()<=0)
										{
											// musuh mati dan player dapat uang
											playergold += musuh[j].getReward();
											tower[i].setTarget(-1);
											cout << "Monster " << musuh[j].getName() << " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ")" << " tewas" << endl;
										}
										cekmusuh = false;
									}
								}						
								j++;
							}
						}
					}
						
					refresh();

					bool cektemp = true;
					bool cektemp2 = true;
					int j=0;
					c++;
					while (j<musuh.size())
					{
						// cek apakah semua musuh telah mati
						if (musuh[j].getaHealth()>0)
							cektemp = false;
						// musuh bergerak
						if ((musuh[j].getaHealth()>0)&&(musuh[j].getPos()>=0)&&(musuh[j].getPos()<pathsize))
						{
							cektemp2 = false;
								
							for (int k=0;k<musuh[j].getaSpeed();++k)
							{
								if (musuh[j].getPos()+k<pathsize)
									musuh[j].move(path[musuh[j].getPos()+k]);								
							}							
								
							cout << musuh[j].getName() << " " << j+1 << " bergerak ke titik (" << musuh[j].getX() << "," << musuh[j].getY() << ")" << endl;
							/**draw enemy**/
							if (c > 5) c = 0; 
							if (musuh[j].getName()=="Lizardman"){
								r = 0;
								_spriteEnemy.SetSubRect(sf::IntRect(c*58, r*64, c*58+58, r*64+64));
							} else if (musuh[j].getName()=="Salamander"){
								r = 1;
								_spriteEnemy.SetSubRect(sf::IntRect(c*58, r*64, c*58+58, r*64+64));
							} else if (musuh[j].getName()=="Mandragora"){
								r = 2;
								_spriteEnemy.SetSubRect(sf::IntRect(c*58, r*64, c*58+58, r*64+64));
							} else if (musuh[j].getName()=="Undine"){
								r = 0;
								_spriteEnemy2.SetSubRect(sf::IntRect(c*128, r*96, c*128+128, r*96+96));
							} else if (musuh[j].getName()=="Efreet"){
								r = 1;
								_spriteEnemy2.SetSubRect(sf::IntRect(c*128, r*96, c*128+128, r*96+96));
							} else if (musuh[j].getName()=="Dryad"){
								r = 2;
								_spriteEnemy2.SetSubRect(sf::IntRect(c*128, r*96, c*128+128, r*96+96));
							}
								

							if ((musuh[j].getName()=="Lizardman") || (musuh[j].getName()=="Salamander") || (musuh[j].getName()=="Mandragora")){
								_spriteEnemy.SetPosition(musuh[j].getX()*64+3,musuh[j].getY()*64);
								_mainWindow.Draw(_spriteEnemy);
							} else if ((musuh[j].getName()=="Undine") || (musuh[j].getName()=="Efreet") || (musuh[j].getName()=="Dryad")){
								_spriteEnemy2.SetPosition(musuh[j].getX()*64-32,musuh[j].getY()*64-32);								
								_mainWindow.Draw(_spriteEnemy2);
							}

							HP = sf::Shape::Rectangle(musuh[j].getX()*64+10,musuh[j].getY()*64,musuh[j].getX()*64+44,musuh[j].getY()*64+5,sf::Color(255,0,0));
							aHP = sf::Shape::Rectangle(musuh[j].getX()*64+10,musuh[j].getY()*64,musuh[j].getX()*64+((double)musuh[j].getaHealth()/(double)musuh[j].getHealth())*44,musuh[j].getY()*64+5,sf::Color(0,255,0));
							
							_mainWindow.Draw(HP);
							_mainWindow.Draw(aHP);
						}
						else if (musuh[j].getPos()<0)
						{
							cektemp2 = false;
						}
							
						if (musuh[j].getaHealth()>0){}
							musuh[j].setPos(musuh[j].getPos()+musuh[j].getaSpeed());
						++j;
					}

					if ((cektemp)||(cektemp2)) // kondisi wave berhenti
					{
						cekwave = false;
					}
						
					_mainWindow.Display();

					float a = 0;
					float b = 0;
					for (int l=0;l<20;l++)
					{
						refresh();

						for (int j=0;j<musuh.size();++j)
						{								
							if ((musuh[j].getaHealth()>0)&&(musuh[j].getPos()>0)&&(musuh[j].getPos()<pathsize))
							{
								// pilih gambar
								if (l == 10){c++;}
								if (c > 5) c = 0; 
								if (musuh[j].getName()=="Lizardman"){
									r = 0;
									_spriteEnemy.SetSubRect(sf::IntRect(c*58, r*64, c*58+58, r*64+64));
								} else if (musuh[j].getName()=="Salamander"){
									r = 1;
									_spriteEnemy.SetSubRect(sf::IntRect(c*58, r*64, c*58+58, r*64+64));
								} else if (musuh[j].getName()=="Mandragora"){
									r = 2;
									_spriteEnemy.SetSubRect(sf::IntRect(c*58, r*64, c*58+58, r*64+64));
								} else if (musuh[j].getName()=="Undine"){
									r = 0;
									_spriteEnemy2.SetSubRect(sf::IntRect(c*128, r*96, c*128+128, r*96+96));
								} else if (musuh[j].getName()=="Efreet"){
									r = 1;
									_spriteEnemy2.SetSubRect(sf::IntRect(c*128, r*96, c*128+128, r*96+96));
								} else if (musuh[j].getName()=="Dryad"){
									r = 2;
									_spriteEnemy2.SetSubRect(sf::IntRect(c*128, r*96, c*128+128, r*96+96));
								}
															
								if (path[musuh[j].getPos()]==0)
								{ //ke atas
									if ((musuh[j].getName()=="Lizardman") || (musuh[j].getName()=="Salamander") || (musuh[j].getName()=="Mandragora")){
										_spriteEnemy.SetPosition(musuh[j].getX()*64+3, musuh[j].getY()*64-a);
										_mainWindow.Draw(_spriteEnemy);
									} else if ((musuh[j].getName()=="Undine") || (musuh[j].getName()=="Efreet") || (musuh[j].getName()=="Dryad")){
										_spriteEnemy2.SetPosition(musuh[j].getX()*64-32, musuh[j].getY()*64-32-b);
										_mainWindow.Draw(_spriteEnemy2);
									}
									HP = sf::Shape::Rectangle(musuh[j].getX()*64+10, /**/musuh[j].getY()*64-a, /**/musuh[j].getX()*64+44, /**/musuh[j].getY()*64+5-a, sf::Color(255, 0, 0));
									aHP = sf::Shape::Rectangle(musuh[j].getX()*64+10, /**/musuh[j].getY()*64-a, /**/musuh[j].getX()*64+ ((double)musuh[j].getaHealth()/(double)musuh[j].getHealth())*44,/**/ musuh[j].getY()*64+5-a, /**/sf::Color(0, 255, 0));
									
								} else 
								if (path[musuh[j].getPos()]==1){ //ke kanan			
									if (facingRight == false)
									{
										_spriteEnemy.FlipX(true);
										_spriteEnemy2.FlipX(true);
										facingRight = true;
									} 
									if ((musuh[j].getName()=="Lizardman") || (musuh[j].getName()=="Salamander") || (musuh[j].getName()=="Mandragora")){
										_spriteEnemy.SetPosition(musuh[j].getX()*64+3+a, musuh[j].getY()*64);
										_mainWindow.Draw(_spriteEnemy);
									} else if ((musuh[j].getName()=="Undine") || (musuh[j].getName()=="Efreet") || (musuh[j].getName()=="Dryad")){
										_spriteEnemy2.SetPosition(musuh[j].getX()*64-32+b, musuh[j].getY()*64-32);
										_mainWindow.Draw(_spriteEnemy2);
									}
									HP = sf::Shape::Rectangle(musuh[j].getX()*64+10+a, musuh[j].getY()*64, musuh[j].getX()*64+44 + a, musuh[j].getY()*64+5, sf::Color(255, 0, 0));
									aHP = sf::Shape::Rectangle(musuh[j].getX()*64+10+a, /**/musuh[j].getY()*64, /**/musuh[j].getX()*64+ ((double)musuh[j].getaHealth()/(double)musuh[j].getHealth())*44 + a,/**/ musuh[j].getY()*64+5, /**/sf::Color(0, 255, 0));
									
								} else
								if (path[musuh[j].getPos()]==2){ //ke bawah
									if ((musuh[j].getName()=="Lizardman") || (musuh[j].getName()=="Salamander") || (musuh[j].getName()=="Mandragora")){
										_spriteEnemy.SetPosition(musuh[j].getX()*64+3, musuh[j].getY()*64+a);
										_mainWindow.Draw(_spriteEnemy);
									} else if ((musuh[j].getName()=="Undine") || (musuh[j].getName()=="Efreet") || (musuh[j].getName()=="Dryad")){
										_spriteEnemy2.SetPosition(musuh[j].getX()*64-32, musuh[j].getY()*64-32+b);
										_mainWindow.Draw(_spriteEnemy2);
									}
									HP = sf::Shape::Rectangle(musuh[j].getX()*64+10, musuh[j].getY()*64+a, musuh[j].getX()*64+44, musuh[j].getY()*64+5 +a, sf::Color(255, 0, 0));
									aHP = sf::Shape::Rectangle(musuh[j].getX()*64+10, /**/musuh[j].getY()*64+a, /**/musuh[j].getX()*64+ ((double)musuh[j].getaHealth()/(double)musuh[j].getHealth())*44,/**/ musuh[j].getY()*64+5 +a, /**/sf::Color(0, 255, 0));
									
								} else
								if (path[musuh[j].getPos()]==3){ //ke kiri
									if (facingRight == true)
									{
										_spriteEnemy.FlipX(true);
										_spriteEnemy2.FlipX(true);
										facingRight = false;
									} 
									if ((musuh[j].getName()=="Lizardman") || (musuh[j].getName()=="Salamander") || (musuh[j].getName()=="Mandragora")){
										_spriteEnemy.SetPosition(musuh[j].getX()*64+3-a, musuh[j].getY()*64);
										_mainWindow.Draw(_spriteEnemy);
									} else if ((musuh[j].getName()=="Undine") || (musuh[j].getName()=="Efreet") || (musuh[j].getName()=="Dryad")){
										_spriteEnemy2.SetPosition(musuh[j].getX()*64-32-b, musuh[j].getY()*64-32);
										_mainWindow.Draw(_spriteEnemy2);
									}
									HP = sf::Shape::Rectangle(musuh[j].getX()*64+10-a, musuh[j].getY()*64, musuh[j].getX()*64+44-a, musuh[j].getY()*64+5, sf::Color(255, 0, 0));
									aHP = sf::Shape::Rectangle(musuh[j].getX()*64+10-a, /**/musuh[j].getY()*64, /**/musuh[j].getX()*64+ ((double)musuh[j].getaHealth()/(double)musuh[j].getHealth())*44 -a,/**/ musuh[j].getY()*64+5, /**/sf::Color(0, 255, 0));
									
								} 
								//draw HP bar
								_mainWindow.Draw(HP); _mainWindow.Draw(aHP);
							}
						}					
						a += 64/20;
						b += 64/20;
						_mainWindow.Display();
					}								
				}			
				// next wave
				_spriteButtonStart.SetColor(sf::Color(255, 255, 255, 255));
				break;
			}
			case Playing1:
			{
				refresh();
				_mainWindow.Display();

				cekpersiapan = true;
				cout << "Preparation Start" << endl;

				while (cekpersiapan)
				{
					_mainWindow.GetEvent(currentEvent);
					if (currentEvent.Type == sf::Event::Closed)
					{
						_gameState = Exiting;
						cekpersiapan = false;
						_mainWindow.Close();
						return 0;
					}

					MenuItem result = GetMenuResponse(_mainWindow);
						
					switch(result.action)
					{
						case Start:
						{
							cekpersiapan = false;
							break;
						}
						case Exit:
						{
							_gameState = Exiting;
							cekpersiapan = false;
							_mainWindow.Close();
							return 0;
							break;
						}
						case Build:
						{
							// Bikin tower di sini berdasarkan id
							cout << "Build" << endl;
							
							switch(result.id)
							{
								case 1:
								{
									if (playergold>=listtower[0].getPrice())
									{
										_spriteTowerRed.SetSubRect(sf::IntRect(0,0,64,64));
										
										sf::Event now;
										now.Type = sf::Event::Count;
	
										bool cek = true;
										while (cek)
										{
											_mainWindow.GetEvent(now);
											if (now.Type==sf::Event::Closed)
											{
												_mainWindow.Close();
												return 0;
											}
											if (now.Type==sf::Event::MouseMoved)
											{
												refresh();

												int x = now.MouseMove.X;
												int y = now.MouseMove.Y;
												x/=64;
												y/=64;

												if (x<16)
												{
													sf::Sprite temp;
													if (_field.getNode(y,x)=='O')
													{
														_field.setNode(y,x,'X');
														vector<int> temppath = _field.getPath();
														if (temppath.size()<=1)
														{
															temp.SetColor(sf::Color(255,0,0,64));
														}
														else
														{
															temp.SetColor(sf::Color(0,255,0,64));
														}
														_field.setNode(y,x,'O');
													}
													else
													{
														temp.SetColor(sf::Color(255,0,0,64));
													}
													temp.SetScaleX(64);
													temp.SetScaleY(64);
													temp.SetPosition(x*64, y*64);
													_spriteTowerRed.SetCenter(0,0);
													_spriteTowerRed.SetPosition(x*64, y*64);
													_mainWindow.Draw(temp);
													_mainWindow.Draw(_spriteTowerRed);
												}

												DrawTowerInformation(0);

												sf::Image img;
												img.LoadFromFile("images/button_cancel.png");
												sf::Sprite temp3;
												temp3.SetImage(img);
												temp3.SetPosition(16*64+20,550);
												_mainWindow.Draw(temp3);


												_mainWindow.Display();
											}
											if (now.Type==sf::Event::MouseButtonReleased)
											{
												int x = now.MouseButton.X;
												int y = now.MouseButton.Y;

												x/=64;
												y/=64;

												if ((x>16*64+20)&&(x<16*64+174)&&(y>550)&&(y<585))
												{
													cek = false;
												}

												_field.setNode(y,x,'X');
												vector<int> temppath = _field.getPath();
												_field.setNode(y,x,'O');												

												if ((x<16)&&(_field.getNode(y,x)=='O')&&(temppath.size()>1))
												{
													refresh();

													tower.push_back(Tower(x,y,listtower[0].getNama()));
													playergold -= listtower[0].getPrice();
													_field.setNode(y,x,'X');

													cek = false;
												
													_spriteTowerRed.SetCenter(0,0);
													_spriteTowerRed.SetPosition(x*64, y*64);
													_mainWindow.Draw(_spriteTowerRed);

													_mainWindow.Display();
												}
												else
												{
													x = now.MouseButton.X;
													y = now.MouseButton.Y;	
													if ((x>16*64+20)&&(x<16*64+174)&&(y>550)&&(y<585))
													{
														cek = false;
													}
												}
											}
										}
									}
									break;
								}
								case 2:
								{
									if (playergold>=listtower[1].getPrice())
									{
										_spriteTowerBlue.SetSubRect(sf::IntRect(0,0,64,64));
										
										sf::Event now;
										now.Type = sf::Event::Count;
	
										bool cek = true;
										while (cek)
										{
											_mainWindow.GetEvent(now);
											if (now.Type==sf::Event::Closed)
											{
												_mainWindow.Close();
												return 0;
											}
											if (now.Type==sf::Event::MouseMoved)
											{
												refresh();
												
												int x = now.MouseMove.X;
												int y = now.MouseMove.Y;
												x/=64;
												y/=64;

												if (x<16)
												{
													sf::Sprite temp;
													if (_field.getNode(y,x)=='O')
													{
														_field.setNode(y,x,'X');
														vector<int> temppath = _field.getPath();
														if (temppath.size()<=1)
														{
															temp.SetColor(sf::Color(255,0,0,64));
														}
														else
														{
															temp.SetColor(sf::Color(0,255,0,64));
														}
														_field.setNode(y,x,'O');
													}
													else
													{
														temp.SetColor(sf::Color(255,0,0,64));
													}
													temp.SetScaleX(64);
													temp.SetScaleY(64);
													temp.SetPosition(x*64, y*64);
													_spriteTowerBlue.SetCenter(0,0);
													_spriteTowerBlue.SetPosition(x*64, y*64);
													
													_mainWindow.Draw(temp);
													_mainWindow.Draw(_spriteTowerBlue);
												}

												DrawTowerInformation(1);

												sf::Image img;
												img.LoadFromFile("images/button_cancel.png");
												sf::Sprite temp3;
												temp3.SetImage(img);
												temp3.SetPosition(16*64+20,550);
												_mainWindow.Draw(temp3);

												_mainWindow.Display();
											}
											if (now.Type==sf::Event::MouseButtonReleased)
											{
												int x = now.MouseButton.X;
												int y = now.MouseButton.Y;

												if ((x>16*64+20)&&(x<16*64+174)&&(y>550)&&(y<585))
												{
													cek = false;
												}

												x/=64;
												y/=64;

												_field.setNode(y,x,'X');
												vector<int> temppath = _field.getPath();
												_field.setNode(y,x,'O');

												if ((x<16)&&(_field.getNode(y,x)=='O')&&(temppath.size()>1))
												{
													refresh();

													tower.push_back(Tower(x,y,listtower[1].getNama()));
													playergold -= listtower[1].getPrice();
													_field.setNode(y,x,'X');

													cek = false;
												
													_spriteTowerBlue.SetCenter(0,0);
													_spriteTowerBlue.SetPosition(x*64, y*64);
													_mainWindow.Draw(_spriteTowerBlue);
			
													_mainWindow.Display();
												}
												else
												{
													x = now.MouseButton.X;
													y = now.MouseButton.Y;	
													if ((x>16*64+20)&&(x<16*64+174)&&(y>550)&&(y<585))
													{
														cek = false;
													}
												}
											}
										}
									}
									break;
								}
								case 3:
								{
									if (playergold>=listtower[2].getPrice())
									{
										_spriteTowerGreen.SetSubRect(sf::IntRect(0,0,64,64));
										
										sf::Event now;
										now.Type = sf::Event::Count;
	
										bool cek = true;
										while (cek)
										{
											_mainWindow.GetEvent(now);
											if (now.Type==sf::Event::Closed)
											{
												_mainWindow.Close();
												return 0;
											}
											if (now.Type==sf::Event::MouseMoved)
											{
												refresh();
												
												int x = now.MouseMove.X;
												int y = now.MouseMove.Y;
												x/=64;
												y/=64;

												if (x<16)
												{
													sf::Sprite temp;
													if (_field.getNode(y,x)=='O')
													{
														_field.setNode(y,x,'X');
														vector<int> temppath = _field.getPath();
														if (temppath.size()<=1)
														{
															temp.SetColor(sf::Color(255,0,0,64));
														}
														else
														{
															temp.SetColor(sf::Color(0,255,0,64));
														}
														_field.setNode(y,x,'O');
													}
													else
													{
														temp.SetColor(sf::Color(255,0,0,64));
													}
													temp.SetScaleX(64);
													temp.SetScaleY(64);
													temp.SetPosition(x*64, y*64);
													_spriteTowerGreen.SetCenter(0,0);
													_spriteTowerGreen.SetPosition(x*64, y*64);
													
													_mainWindow.Draw(temp);
													_mainWindow.Draw(_spriteTowerGreen);
												}

												DrawTowerInformation(2);

												sf::Image img;
												img.LoadFromFile("images/button_cancel.png");
												sf::Sprite temp3;
												temp3.SetImage(img);
												temp3.SetPosition(16*64+20,550);
												_mainWindow.Draw(temp3);

												_mainWindow.Display();
											}
											if (now.Type==sf::Event::MouseButtonReleased)
											{
												int x = now.MouseButton.X;
												int y = now.MouseButton.Y;

												x/=64;
												y/=64;

												_field.setNode(y,x,'X');
												vector<int> temppath = _field.getPath();
												_field.setNode(y,x,'O');

												if ((x<16)&&(_field.getNode(y,x)=='O')&&(temppath.size()>1))
												{
													refresh();

													tower.push_back(Tower(x,y,listtower[2].getNama()));
													playergold -= listtower[2].getPrice();
													_field.setNode(y,x,'X');

													cek = false;
												
													_spriteTowerGreen.SetCenter(0,0);
													_spriteTowerGreen.SetPosition(x*64, y*64);
													_mainWindow.Draw(_spriteTowerGreen);
			
													_mainWindow.Display();
												}
												else
												{
													x = now.MouseButton.X;
													y = now.MouseButton.Y;							
													if ((x>16*64+20)&&(x<16*64+174)&&(y>550)&&(y<585))
													{
														cek = false;
													}
												}
											}
										}
									}
									break;
								}
								default:break;
							}
							break;
						}
						case TowerUp:
						{
							// Upgrade tower berdasarkan id
							break;
						}
						default:break;
					}
					
					refresh();
					_mainWindow.Display();
				}

				_spriteButtonStart.SetColor(sf::Color(255, 255, 255, 128));
					
				// greedy musuh di sini
				// berdasarkan kondisi dari field saat ini
				int max=0;
				int felement[3];
				for (int i=0;i<3;++i)
					felement[i] = 0;
				for (int i=0;i<tower.size();++i)
				{
					if (tower[i].getElement()=="Fire")
					{
						if (tower[i].getNama()=="Blaze")
							felement[0]++;
						felement[0]++;
						if (felement[0]>felement[max])
							max = 0;
					}
					else if (tower[i].getElement()=="Water")
					{
						if (tower[i].getNama()=="Torrent")
							felement[1]++;
						felement[1]++;
						if (felement[1]>felement[max])
							max = 1;
					}
					else if (tower[i].getElement()=="Nature")
					{
						if (tower[i].getNama()=="Meadow")
							felement[2]++;
						felement[2]++;
						if (felement[2]>felement[max])
							max = 2;
					}
				}
				string upgrade;
				if (max==0)
				{
					max = 1;
					upgrade = "Lizardman";
				}
				else if (max==1)
				{
					max = 2;
					upgrade = "Mandragora";
				}
				else
				{
					max = 0;
					upgrade = "Salamander";
				}
				for (int i=0;i<musuh.size();++i)
				{
					if ((musuh[i].getName()!="Efreet")&&(musuh[i].getName()!="Undine")&&(musuh[i].getName()!="Dryad")&&(musuh[i].getElement()==listmusuh[max].getElement()))
					{
						if (musuh[i].getUpgradelist(musuh[i].getName())[0].getPrice()<enemygold)
						{
							musuh[i] = musuh[i].Upgrade(musuh[i].getUpgradelist(musuh[i].getName())[0].getName());
							enemygold -= musuh[i].getPrice();
						}
					}
				}
				while (listmusuh[max].getPrice()<enemygold)
				{
					musuh.push_back(Enemy(listmusuh[max].getName()));
					enemygold -= listmusuh[max].getPrice();
					if (musuh[musuh.size()-1].getUpgradelist(musuh[musuh.size()-1].getName())[0].getPrice()<enemygold)
					{
						musuh[musuh.size()-1] = musuh[musuh.size()-1].Upgrade(musuh[musuh.size()-1].getUpgradelist(musuh[musuh.size()-1].getName())[0].getName());
						enemygold -= musuh[musuh.size()-1].getPrice();
					}
				}
			
				// menentukan jalur yang ingin dilalui musuh dengan djikstra
				vector<int> path = _field.getPath();

				int pathsize = path.size();// field.getPath().size;
				for (int j=musuh.size()-1;j>=0;--j)
				{
					// set urutan, darah, kecepatan, posisi musuh dan musuh dapat pemasukan
					musuh[j].setPos(j*-1-1);
					musuh[j].setaHealth(musuh[j].getHealth());
					musuh[j].setaSpeed(musuh[j].getSpeed());
					musuh[j].setX(-1);
					musuh[j].setY(4);
					enemygold += musuh[j].getIncome();
				}
				// 
			
				cout << "Wave Start" << endl;

				cekwave = true;
				while (cekwave)
				{
					// penyerangan
					for (int i=0;i<tower.size();++i)
					{
						bool cekmusuh = true;
						if ((tower[i].getTarget()!=-1)&&(musuh[tower[i].getTarget()].getaHealth()>0)&&(abs(tower[i].getX()-musuh[tower[i].getTarget()].getX())+abs(tower[i].getY()-musuh[tower[i].getTarget()].getY())<=tower[i].getRange()))
						// tower sudah ada target dan musuh masih dalam range
						{
							int j = tower[i].getTarget();
							tower[i].attack(&musuh[j]);

							cout << "Tower " << tower[i].getNama() << "(" << tower[i].getX() << "," << tower[i].getY() << ") menyerang " << musuh[j].getName()<< " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ")" << endl;
							cout << "Darah " << musuh[j].getName() << " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ") tinggal " << musuh[j].getaHealth() << endl;

							if (musuh[j].getaHealth()<=0)
							{
								cout << "Tower "<< tower[i].getNama() << "(" << tower[i].getX() << "," << tower[i].getY() << ") menyerang " << musuh[j].getName()<< " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ")" << endl;
								/*float difX = tower[i].getX() - musuh[j].getX();
								float difY = tower[i].getY() - musuh[j].getY();
								tower[i].setAngle(atan(difX/difY));
								if (tower[i].getNama()=="Splash"){
									if (musuh[j].getY() <= tower[i].getY()){ //musuh di sebelah atas tower
										tower[i].setAngle(atan(difX/difY));
									} else if (musuh[j].getY() > tower[i].getY()){ //musuh di sebelah bawah tower
										tower[i].setAngle(atan(difX/difY) + 180.0);
									}
								} else if (tower[i].getNama()=="Ember"){
									if (musuh[j].getY() <= tower[i].getY()){ //musuh di sebelah atas tower
										_spriteTowerRed.SetRotation(atan(difX/difY));
									} else if (musuh[j].getY() > tower[i].getY()){ //musuh di sebelah bawah tower
										_spriteTowerRed.SetRotation(atan(difX/difY) + 180.0);
									}
								} else if (tower[i].getNama()=="Sprout"){
									if (musuh[j].getY() <= tower[i].getY()){ //musuh di sebelah atas tower
										_spriteTowerRed.SetRotation(atan(difX/difY));
									} else if (musuh[j].getY() > tower[i].getY()){ //musuh di sebelah bawah tower
										_spriteTowerRed.SetRotation(atan(difX/difY) + 180.0);
									}
								}*/

								j = tower[i].getTarget();
								tower[i].attack(&musuh[j]);
								if (musuh[j].getaHealth()<=0)
								{
									// musuh mati dan player dapat uang
									playergold += musuh[j].getReward();
									tower[i].setTarget(-1);
									cout << "Monster " << musuh[j].getName() << " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ")" << " tewas" << endl;
								}
							}
						}
						else
						{	
							int j = 0;
							while ((cekmusuh)&&(j<musuh.size()))
							{
								if ((musuh[j].getaHealth()>0)&&(abs(tower[i].getX()-musuh[j].getX())+abs(tower[i].getY()-musuh[j].getY())<=tower[i].getRange()))
								// jika tower dapat menyerang musuh (dalam jangkauan) dann tower sedang tidak ada target 
								// health musuh berkurang
								{
									tower[i].setTarget(j);
									tower[i].attack(&musuh[j]);
								
									cout << "Tower "<< tower[i].getNama() << "(" << tower[i].getX() << "," << tower[i].getY() << ") menyerang " << musuh[j].getName() << " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ")" << endl;
									cout << "Darah " << musuh[j].getName() << " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ") tinggal " << musuh[j].getaHealth() << endl;

									if (musuh[j].getaHealth()<=0)
									{
										cout << "Tower "<< tower[i].getNama() << "(" << tower[i].getX() << "," << tower[i].getY() << ") menyerang " << musuh[j].getName() << " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ")" << endl;
										/*float difX = tower[i].getX() - musuh[j].getX();
										float difY = tower[i].getY() - musuh[j].getY();
										if (musuh[j].getY() <= tower[i].getY()){ //musuh di sebelah atas tower
											tower[i].setAngle(atan(difY/difX));
										} else if (musuh[j].getY() > tower[i].getY()){ //musuh di sebelah bawah tower
											tower[i].setAngle(atan(difY/difX) + 180.0);
										}*/
										

										tower[i].setTarget(j);
										tower[i].attack(&musuh[j]);
										if (musuh[j].getaHealth()<=0)
										{
											// musuh mati dan player dapat uang
											playergold += musuh[j].getReward();
											tower[i].setTarget(-1);
											cout << "Monster " << musuh[j].getName() << " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ")" << " tewas" << endl;
										}
										cekmusuh = false;
									}
								}						
								j++;
							}
						}
					}
						
					refresh();

					bool cektemp = true;
					bool cektemp2 = true;
					int j=0;
					c++;
					while (j<musuh.size())
					{
						// cek apakah semua musuh telah mati
						if (musuh[j].getaHealth()>0)
							cektemp = false;
						// musuh bergerak
						if ((musuh[j].getaHealth()>0)&&(musuh[j].getPos()>=0)&&(musuh[j].getPos()<pathsize))
						{
							cektemp2 = false;
								
							for (int k=0;k<musuh[j].getaSpeed();++k)
							{
								if (musuh[j].getPos()+k<pathsize)
									musuh[j].move(path[musuh[j].getPos()+k]);								
							}							
								
							cout << musuh[j].getName() << " " << j+1 << " bergerak ke titik (" << musuh[j].getX() << "," << musuh[j].getY() << ")" << endl;
							/**draw enemy**/
							if (c > 5) c = 0; 
							if (musuh[j].getName()=="Lizardman"){
								r = 0;
								_spriteEnemy.SetSubRect(sf::IntRect(c*58, r*64, c*58+58, r*64+64));
							} else if (musuh[j].getName()=="Salamander"){
								r = 1;
								_spriteEnemy.SetSubRect(sf::IntRect(c*58, r*64, c*58+58, r*64+64));
							} else if (musuh[j].getName()=="Mandragora"){
								r = 2;
								_spriteEnemy.SetSubRect(sf::IntRect(c*58, r*64, c*58+58, r*64+64));
							} else if (musuh[j].getName()=="Undine"){
								r = 0;
								_spriteEnemy2.SetSubRect(sf::IntRect(c*128, r*96, c*128+128, r*96+96));
							} else if (musuh[j].getName()=="Efreet"){
								r = 1;
								_spriteEnemy2.SetSubRect(sf::IntRect(c*128, r*96, c*128+128, r*96+96));
							} else if (musuh[j].getName()=="Dryad"){
								r = 2;
								_spriteEnemy2.SetSubRect(sf::IntRect(c*128, r*96, c*128+128, r*96+96));
							}
								

							if ((musuh[j].getName()=="Lizardman") || (musuh[j].getName()=="Salamander") || (musuh[j].getName()=="Mandragora")){
								_spriteEnemy.SetPosition(musuh[j].getX()*64+3,musuh[j].getY()*64);
								_mainWindow.Draw(_spriteEnemy);
							} else if ((musuh[j].getName()=="Undine") || (musuh[j].getName()=="Efreet") || (musuh[j].getName()=="Dryad")){
								_spriteEnemy2.SetPosition(musuh[j].getX()*64-32,musuh[j].getY()*64-32);								
								_mainWindow.Draw(_spriteEnemy2);
							}

							HP = sf::Shape::Rectangle(musuh[j].getX()*64+10,musuh[j].getY()*64,musuh[j].getX()*64+44,musuh[j].getY()*64+5,sf::Color(255,0,0));
							aHP = sf::Shape::Rectangle(musuh[j].getX()*64+10,musuh[j].getY()*64,musuh[j].getX()*64+((double)musuh[j].getaHealth()/(double)musuh[j].getHealth())*44,musuh[j].getY()*64+5,sf::Color(0,255,0));
							
							_mainWindow.Draw(HP);
							_mainWindow.Draw(aHP);
						}
						else if (musuh[j].getPos()<0)
						{
							cektemp2 = false;
						}
							
						if (musuh[j].getaHealth()>0){}
							musuh[j].setPos(musuh[j].getPos()+musuh[j].getaSpeed());
						++j;
					}

					if ((cektemp)||(cektemp2)) // kondisi wave berhenti
					{
						cekwave = false;
					}
						
					_mainWindow.Display();

					float a = 0;
					float b = 0;
					for (int l=0;l<20;l++)
					{
						refresh();

						for (int j=0;j<musuh.size();++j)
						{								
							if ((musuh[j].getaHealth()>0)&&(musuh[j].getPos()>0)&&(musuh[j].getPos()<pathsize))
							{
								// pilih gambar
								if (l == 10){c++;}
								if (c > 5) c = 0; 
								if (musuh[j].getName()=="Lizardman"){
									r = 0;
									_spriteEnemy.SetSubRect(sf::IntRect(c*58, r*64, c*58+58, r*64+64));
								} else if (musuh[j].getName()=="Salamander"){
									r = 1;
									_spriteEnemy.SetSubRect(sf::IntRect(c*58, r*64, c*58+58, r*64+64));
								} else if (musuh[j].getName()=="Mandragora"){
									r = 2;
									_spriteEnemy.SetSubRect(sf::IntRect(c*58, r*64, c*58+58, r*64+64));
								} else if (musuh[j].getName()=="Undine"){
									r = 0;
									_spriteEnemy2.SetSubRect(sf::IntRect(c*128, r*96, c*128+128, r*96+96));
								} else if (musuh[j].getName()=="Efreet"){
									r = 1;
									_spriteEnemy2.SetSubRect(sf::IntRect(c*128, r*96, c*128+128, r*96+96));
								} else if (musuh[j].getName()=="Dryad"){
									r = 2;
									_spriteEnemy2.SetSubRect(sf::IntRect(c*128, r*96, c*128+128, r*96+96));
								}
															
								if (path[musuh[j].getPos()]==0)
								{ //ke atas
									if ((musuh[j].getName()=="Lizardman") || (musuh[j].getName()=="Salamander") || (musuh[j].getName()=="Mandragora")){
										_spriteEnemy.SetPosition(musuh[j].getX()*64+3, musuh[j].getY()*64-a);
										_mainWindow.Draw(_spriteEnemy);
									} else if ((musuh[j].getName()=="Undine") || (musuh[j].getName()=="Efreet") || (musuh[j].getName()=="Dryad")){
										_spriteEnemy2.SetPosition(musuh[j].getX()*64-32, musuh[j].getY()*64-32-b);
										_mainWindow.Draw(_spriteEnemy2);
									}
									HP = sf::Shape::Rectangle(musuh[j].getX()*64+10, /**/musuh[j].getY()*64-a, /**/musuh[j].getX()*64+44, /**/musuh[j].getY()*64+5-a, sf::Color(255, 0, 0));
									aHP = sf::Shape::Rectangle(musuh[j].getX()*64+10, /**/musuh[j].getY()*64-a, /**/musuh[j].getX()*64+ ((double)musuh[j].getaHealth()/(double)musuh[j].getHealth())*44,/**/ musuh[j].getY()*64+5-a, /**/sf::Color(0, 255, 0));
									
								} else 
								if (path[musuh[j].getPos()]==1){ //ke kanan			
									if (facingRight == false)
									{
										_spriteEnemy.FlipX(true);
										_spriteEnemy2.FlipX(true);
										facingRight = true;
									} 
									if ((musuh[j].getName()=="Lizardman") || (musuh[j].getName()=="Salamander") || (musuh[j].getName()=="Mandragora")){
										_spriteEnemy.SetPosition(musuh[j].getX()*64+3+a, musuh[j].getY()*64);
										_mainWindow.Draw(_spriteEnemy);
									} else if ((musuh[j].getName()=="Undine") || (musuh[j].getName()=="Efreet") || (musuh[j].getName()=="Dryad")){
										_spriteEnemy2.SetPosition(musuh[j].getX()*64-32+b, musuh[j].getY()*64-32);
										_mainWindow.Draw(_spriteEnemy2);
									}
									HP = sf::Shape::Rectangle(musuh[j].getX()*64+10+a, musuh[j].getY()*64, musuh[j].getX()*64+44 + a, musuh[j].getY()*64+5, sf::Color(255, 0, 0));
									aHP = sf::Shape::Rectangle(musuh[j].getX()*64+10+a, /**/musuh[j].getY()*64, /**/musuh[j].getX()*64+ ((double)musuh[j].getaHealth()/(double)musuh[j].getHealth())*44 + a,/**/ musuh[j].getY()*64+5, /**/sf::Color(0, 255, 0));
									
								} else
								if (path[musuh[j].getPos()]==2){ //ke bawah
									if ((musuh[j].getName()=="Lizardman") || (musuh[j].getName()=="Salamander") || (musuh[j].getName()=="Mandragora")){
										_spriteEnemy.SetPosition(musuh[j].getX()*64+3, musuh[j].getY()*64+a);
										_mainWindow.Draw(_spriteEnemy);
									} else if ((musuh[j].getName()=="Undine") || (musuh[j].getName()=="Efreet") || (musuh[j].getName()=="Dryad")){
										_spriteEnemy2.SetPosition(musuh[j].getX()*64-32, musuh[j].getY()*64-32+b);
										_mainWindow.Draw(_spriteEnemy2);
									}
									HP = sf::Shape::Rectangle(musuh[j].getX()*64+10, musuh[j].getY()*64+a, musuh[j].getX()*64+44, musuh[j].getY()*64+5 +a, sf::Color(255, 0, 0));
									aHP = sf::Shape::Rectangle(musuh[j].getX()*64+10, /**/musuh[j].getY()*64+a, /**/musuh[j].getX()*64+ ((double)musuh[j].getaHealth()/(double)musuh[j].getHealth())*44,/**/ musuh[j].getY()*64+5 +a, /**/sf::Color(0, 255, 0));
									
								} else
								if (path[musuh[j].getPos()]==3){ //ke kiri
									if (facingRight == true)
									{
										_spriteEnemy.FlipX(true);
										_spriteEnemy2.FlipX(true);
										facingRight = false;
									} 
									if ((musuh[j].getName()=="Lizardman") || (musuh[j].getName()=="Salamander") || (musuh[j].getName()=="Mandragora")){
										_spriteEnemy.SetPosition(musuh[j].getX()*64+3-a, musuh[j].getY()*64);
										_mainWindow.Draw(_spriteEnemy);
									} else if ((musuh[j].getName()=="Undine") || (musuh[j].getName()=="Efreet") || (musuh[j].getName()=="Dryad")){
										_spriteEnemy2.SetPosition(musuh[j].getX()*64-32-b, musuh[j].getY()*64-32);
										_mainWindow.Draw(_spriteEnemy2);
									}
									HP = sf::Shape::Rectangle(musuh[j].getX()*64+10-a, musuh[j].getY()*64, musuh[j].getX()*64+44-a, musuh[j].getY()*64+5, sf::Color(255, 0, 0));
									aHP = sf::Shape::Rectangle(musuh[j].getX()*64+10-a, /**/musuh[j].getY()*64, /**/musuh[j].getX()*64+ ((double)musuh[j].getaHealth()/(double)musuh[j].getHealth())*44 -a,/**/ musuh[j].getY()*64+5, /**/sf::Color(0, 255, 0));
									
								} 
								//draw HP bar
								_mainWindow.Draw(HP); _mainWindow.Draw(aHP);
							}
						}					
						a += 64/20;
						b += 64/20;
						_mainWindow.Display();
					}								
				}			
				// next wave
				_spriteButtonStart.SetColor(sf::Color(255, 255, 255, 255));
				break;
			}
			
			case Help: {
				sf::Event ee;
				int tutorial = 1;
				refresh();
				_mainWindow.Display();

				while (tutorial <= 10) {
					refresh();
					_mainWindow.GetEvent(ee);
					if (tutorial == 1) {
						_imageButtonHelp.LoadFromFile("images/help_1.png");
						_spriteButtonHelp.SetImage(_imageButtonHelp);
						_mainWindow.Draw(_spriteButtonHelp);
						if (ee.Type == sf::Event::MouseButtonPressed) tutorial++;
					}
					else
					if (tutorial == 2) {
						_imageButtonHelp.LoadFromFile("images/help_2.png");
						_spriteButtonHelp.SetImage(_imageButtonHelp);
						_mainWindow.Draw(_spriteButtonHelp);
						if (ee.Type == sf::Event::MouseButtonPressed) tutorial++;
					}
					else
					if (tutorial == 3) {
						_imageButtonHelp.LoadFromFile("images/help_3.png");
						_spriteButtonHelp.SetImage(_imageButtonHelp);
						_mainWindow.Draw(_spriteButtonHelp);
						if (ee.Type == sf::Event::MouseButtonPressed) tutorial++;
					}
					else
					if (tutorial == 4) {
						_imageButtonHelp.LoadFromFile("images/help_4.png");
						_spriteButtonHelp.SetImage(_imageButtonHelp);
						_mainWindow.Draw(_spriteButtonHelp);
						if (ee.Type == sf::Event::MouseButtonPressed) tutorial++;
					}
					else
					if (tutorial == 5) {
						_imageButtonHelp.LoadFromFile("images/help_5.png");
						_spriteButtonHelp.SetImage(_imageButtonHelp);
						_mainWindow.Draw(_spriteButtonHelp);
						if (ee.Type == sf::Event::MouseButtonPressed) tutorial++;				
					}
					else
					if (tutorial == 6) {
						_imageButtonHelp.LoadFromFile("images/help_6.png");
						_spriteButtonHelp.SetImage(_imageButtonHelp);
						_mainWindow.Draw(_spriteButtonHelp);
						if (ee.Type == sf::Event::MouseButtonPressed) tutorial++;
					}
					else
					if (tutorial == 7) {
						_imageButtonHelp.LoadFromFile("images/help_7.png");
						_spriteButtonHelp.SetImage(_imageButtonHelp);
						_mainWindow.Draw(_spriteButtonHelp);
						if (ee.Type == sf::Event::MouseButtonPressed) tutorial++;
					}
					else 
					if (tutorial == 8) {
						_imageButtonHelp.LoadFromFile("images/help_8.png");
						_spriteButtonHelp.SetImage(_imageButtonHelp);
						_mainWindow.Draw(_spriteButtonHelp);
						if (ee.Type == sf::Event::MouseButtonPressed) tutorial++;
					}
					else
					if (tutorial == 9) {
						_imageButtonHelp.LoadFromFile("images/help_9.png");
						_spriteButtonHelp.SetImage(_imageButtonHelp);
						_mainWindow.Draw(_spriteButtonHelp);
						if (ee.Type == sf::Event::MouseButtonPressed) tutorial++;
					}
					else {
						_gameState = ShowingMenu;
						break;
					}
					if (_gameState == ShowingMenu) break;
					_mainWindow.Display();
				}

				break;
			}
			default:break;
		}
	}
	_mainWindow.Close();
	return 0;
}


