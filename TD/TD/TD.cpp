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
        ShowingMenu, Playing1, Playing2, Exiting, Help };
  
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
static sf::Sprite	_spriteEnemy;

static sf::Image	_imageTile;
static sf::Sprite	_spriteTile;

static sf::Image	_imageButtonStart;
static sf::Sprite	_spriteButtonStart;

static sf::Image	_imageButtonExit;
static sf::Sprite	_spriteButtonExit;

static sf::Image	_imageButtonHelp;
static sf::Sprite	_spriteButtonHelp;

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
				MenuItem temp;
				temp.action = Exit;
				return temp;
			}
		}
	}
}

/* ---- Bagian Persiapan ---- */

/* Program Utama */

int main()
{
	// variabel
	vector<Enemy> musuh;
	vector<Tower> tower;
	vector<sf::String> kata2;
	vector<sf::Sprite> stower;

	Field field;
	int enemygold = 10;
	int playergold = 10;
	Enemy * listmusuh = getEnemylist();
	Tower * listtower = getTowerList();

	musuh.push_back(Enemy(listmusuh[0].getName()));
	musuh.push_back(Enemy(listmusuh[1].getName()));
	musuh.push_back(Enemy(listmusuh[2].getName()));
	musuh.push_back(Enemy(listmusuh[2].getName()));
	tower.push_back(Tower(3,3,"Splash"));
	tower.push_back(Tower(3,5,"Splash"));

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
			case Playing1:
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
					}
				}

				_mainWindow.Draw(_spriteButtonStart);
				_mainWindow.Draw(_spriteButtonExit);

				cekpersiapan = true;

				//Bikin text-text yang ingin ditampilkan
				sf::String tPlayerM ;
				tPlayerM.SetText("Player Money: ");
				tPlayerM.SetSize(20);
				tPlayerM.SetColor(sf::Color(255,255,255));
				tPlayerM.SetPosition(16*64+20,155);
				kata2.push_back(tPlayerM);

				sf::String tEnemyM ;
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

				stringstream convert;

				convert << enemygold;

				sf::String tMoneyE;
				tMoneyE.SetText(convert.str());
				tMoneyE.SetSize(20);
				tMoneyE.SetColor(sf::Color(255,255,255));
				tMoneyE.SetPosition(16*64+40,230);
				_mainWindow.Draw(tMoneyE);

				convert.str("");
				convert << playergold;

				sf::String tMoneyP;
				tMoneyP.SetText(convert.str());
				tMoneyP.SetSize(20);
				tMoneyP.SetColor(sf::Color(255,255,255));
				tMoneyP.SetPosition(16*64+40,180);
				_mainWindow.Draw(tMoneyP);

				for (int i=0;i<kata2.size();++i)
				{
					_mainWindow.Draw(kata2[i]);
				}

				for (int i=0;i<stower.size();++i)
				{
					_mainWindow.Draw(stower[i]);
				}

				_mainWindow.Display();

				while (cekpersiapan)
				{
					_mainWindow.GetEvent(currentEvent);
					if (currentEvent.Type == sf::Event::Closed)
					{
						_gameState = Exiting;
						cekpersiapan = false;
					}

					if (_gameState==Playing1)
					{
						MenuItem result = GetMenuResponse(_mainWindow);
						
						switch(result.action)
						{
							case Start:
							{
								cekpersiapan = false;
								break;
							}
							case Menu:
							{
								_gameState = ShowingMenu;
								break;
							}
							case Exit:
							{
								_gameState = Exiting;
								cekpersiapan = false;
								break;
							}
							case Build:
							{
								// Bikin tower di sini berdasarkan id
								switch(result.id)
								{
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
					}
				}

				if (_gameState==Playing1)
				{
					_spriteButtonStart.SetColor(sf::Color(255, 255, 255, 128));
					
					// greedy musuh di sini
					// berdasarkan kondisi dari field saat ini
			
			
					// menentukan jalur yang ingin dilalui musuh dengan djikstra
					int* path = (int*) malloc (25*sizeof(int));// field.getPath().path;
						path[0] = 1; path[1] = 1; path[2] = 1; path[3] = 1; path[4] = 1; path[5] = 1; path[6] = 1; 
						path[7] = 2; path[8] = 2; path[9] = 2;
						path[10] = 1; path[11] = 1; path[12] = 1;
						path[13] = 0; path[14] = 0;
						path[15] = 1; path[16] = 1; path[17] = 1;
						path[18] = 2; path[19] = 2; path[20] = 2; path[21] = 2;
						path[22] = 1; path[23] = 1; path[24] = 1;

					int pathsize = 25;// field.getPath().size;
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
			
					cekwave = true;
					while (cekwave)
					{
						// penyerangan
						for (int i=0;i<tower.size();++i)
						{
							bool cekmusuh = true;
							int j = 0;
							if ((tower[i].getTarget()!=-1)&&(musuh[tower[i].getTarget()].getaHealth()>0)&&(abs(tower[i].getX()-musuh[tower[i].getTarget()].getX())+abs(tower[i].getY()-musuh[tower[i].getTarget()].getY())<=tower[i].getRange()))
							// tower sudah ada target dan musuh masih dalam range
							{
								cout << "Tower "<< tower[i].getNama() << "(" << tower[i].getX() << "," << tower[i].getY() << ") menyerang " << musuh[j].getName()<< " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ")" << endl;
								float difX = tower[i].getX() - musuh[j].getX();
								float difY = tower[i].getY() - musuh[j].getY();
								if (tower[i].getNama()=="Splash"){
									cout << "SPLASH" << endl;
									if (musuh[j].getY() <= tower[i].getY()){ //musuh di sebelah atas tower
										_spriteTowerBlue.SetRotation(atan(difX/difY));
										cout << "tower " << i << endl;
									} else if (musuh[j].getY() > tower[i].getY()){ //musuh di sebelah bawah tower
										_spriteTowerBlue.SetRotation(atan(difX/difY) + 180.0);
										cout << "tower " << i << endl;
									}
								} else if (tower[i].getNama()=="Ember"){
									cout << "EMBER" << endl;
									if (musuh[j].getY() <= tower[i].getY()){ //musuh di sebelah atas tower
										_spriteTowerRed.SetRotation(atan(difX/difY));
									} else if (musuh[j].getY() > tower[i].getY()){ //musuh di sebelah bawah tower
										_spriteTowerRed.SetRotation(atan(difX/difY) + 180.0);
									}
								} else if (tower[i].getNama()=="Sprout"){
									cout << "SPROUT" << endl;
									if (musuh[j].getY() <= tower[i].getY()){ //musuh di sebelah atas tower
										_spriteTowerRed.SetRotation(atan(difX/difY));
									} else if (musuh[j].getY() > tower[i].getY()){ //musuh di sebelah bawah tower
										_spriteTowerRed.SetRotation(atan(difX/difY) + 180.0);
									}
								}

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
							else
							{
								
								while ((cekmusuh)&&(j<musuh.size()))
								{
									if ((musuh[j].getaHealth()>0)&&(abs(tower[i].getX()-musuh[j].getX())+abs(tower[i].getY()-musuh[j].getY())<=tower[i].getRange()))
									// jika tower dapat menyerang musuh (dalam jangkauan) dann tower sedang tidak ada target 
									// health musuh berkurang
									{
										cout << "Tower "<< tower[i].getNama() << "(" << tower[i].getX() << "," << tower[i].getY() << ") menyerang " << musuh[j].getName() << " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ")" << endl;

										float difX = tower[i].getX() - musuh[j].getX();
										float difY = tower[i].getY() - musuh[j].getY();
										if (tower[i].getNama()=="Splash"){
											cout << "SPLASH" << endl;
											if (musuh[j].getY() <= tower[i].getY()){ //musuh di sebelah atas tower
												_spriteTowerBlue.SetRotation(atan(difX/difY));
												cout << "tower " << i << endl;
											} else if (musuh[j].getY() > tower[i].getY()){ //musuh di sebelah bawah tower
												_spriteTowerBlue.SetRotation(atan(difX/difY) + 180.0);
												cout << "tower " << i << endl;
											}
										} else if (tower[i].getNama()=="Ember"){
											cout << "EMBER" << endl;
											if (musuh[j].getY() <= tower[i].getY()){ //musuh di sebelah atas tower
												_spriteTowerRed.SetRotation(atan(difX/difY));
											} else if (musuh[j].getY() > tower[i].getY()){ //musuh di sebelah bawah tower
												_spriteTowerRed.SetRotation(atan(difX/difY) + 180.0);
											}
										} else if (tower[i].getNama()=="Sprout"){
											cout << "SPROUT" << endl;
											if (musuh[j].getY() <= tower[i].getY()){ //musuh di sebelah atas tower
												_spriteTowerRed.SetRotation(atan(difX/difY));
											} else if (musuh[j].getY() > tower[i].getY()){ //musuh di sebelah bawah tower
												_spriteTowerRed.SetRotation(atan(difX/difY) + 180.0);
											}
										}
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
									j++;
								}
						
							}
						}
						
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
							}
						}
						for (int i=0;i<kata2.size();++i)
						{
							_mainWindow.Draw(kata2[i]);
						}
						for (int i=0;i<stower.size();++i)
						{
							_mainWindow.Draw(stower[i]);
						}
						_mainWindow.Draw(_spriteButtonStart);
						_mainWindow.Draw(_spriteButtonExit);

						bool cektemp = true;
						bool cektemp2 = true;
						int j=0;
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
									musuh[j].move(path[musuh[j].getPos()+k]);								
								}
								
								
								cout << musuh[j].getName() << " " << j+1 << " bergerak ke titik (" << musuh[j].getX() << "," << musuh[j].getY() << ")" << endl;
								/**draw enemy**/
								c++;
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
									_spriteEnemy.SetSubRect(sf::IntRect(c*58, r*64, c*58+58, r*64+64));
								} else if (musuh[j].getName()=="Efreet"){
									r = 1;
									_spriteEnemy.SetSubRect(sf::IntRect(c*58, r*64, c*58+58, r*64+64));
								} else if (musuh[j].getName()=="Dryad"){
									r = 2;
									_spriteEnemy.SetSubRect(sf::IntRect(c*58, r*64, c*58+58, r*64+64));
								}
								
								_spriteEnemy.SetPosition(musuh[j].getX()*64+3, musuh[j].getY()*64);
								_mainWindow.Draw(_spriteEnemy);
								HP = sf::Shape::Rectangle(musuh[j].getX()*64+10, /**/musuh[j].getY()*64, /**/musuh[j].getX()*64+54, /**/musuh[j].getY()*64+5, sf::Color(255, 0, 0));
								aHP = sf::Shape::Rectangle(musuh[j].getX()*64+10, /**/musuh[j].getY()*64, /**/musuh[j].getX()*64+ (musuh[j].getaHealth()/musuh[j].getHealth())*44,/**/ musuh[j].getY()*64+5, /**/sf::Color(0, 255, 0));
								_mainWindow.Draw(HP); _mainWindow.Draw(aHP);
								
							}
							else if (musuh[j].getPos()<0)
							{
								cektemp2 = false;
							}
							
							if (musuh[j].getaHealth()>0){}
								musuh[j].setPos(musuh[j].getPos()+musuh[j].getaSpeed());
							++j;
						}

						convert.str("");
						convert << enemygold;

						tMoneyE.SetText(convert.str());
						_mainWindow.Draw(tMoneyE);

						convert.str("");
						convert << playergold;

						tMoneyP.SetText(convert.str());
						_mainWindow.Draw(tMoneyP);

						_mainWindow.Display();


						float a = 0;
						for (int l=0;l<20;l++){
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
								}
							}
							for (int i=0;i<kata2.size();++i)
							{
								_mainWindow.Draw(kata2[i]);
							}
							for (int i=0;i<stower.size();++i)
							{
								_mainWindow.Draw(stower[i]);
							}
							for (int j=0;j<musuh.size();++j)
							{								
								if ((musuh[j].getaHealth()>0)&&(musuh[j].getPos()>=0)&&(musuh[j].getPos()<pathsize))
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
										_spriteEnemy.SetSubRect(sf::IntRect(c*58, r*64, c*58+58, r*64+64));
									} else if (musuh[j].getName()=="Efreet"){
										r = 1;
										_spriteEnemy.SetSubRect(sf::IntRect(c*58, r*64, c*58+58, r*64+64));
									} else if (musuh[j].getName()=="Dryad"){
										r = 2;
										_spriteEnemy.SetSubRect(sf::IntRect(c*58, r*64, c*58+58, r*64+64));
									}
									if ((musuh[j].getPos() > 0) && (musuh[j].getPos() < pathsize)){
										if (path[musuh[j].getPos()]==0){ //ke atas
											_spriteEnemy.SetPosition(musuh[j].getX()*64+3, musuh[j].getY()*64-a);
											_mainWindow.Draw(_spriteEnemy);
											HP = sf::Shape::Rectangle(musuh[j].getX()*64+10, /**/musuh[j].getY()*64-a, /**/musuh[j].getX()*64+54, /**/musuh[j].getY()*64+5-a, sf::Color(255, 0, 0));
											aHP = sf::Shape::Rectangle(musuh[j].getX()*64+10, /**/musuh[j].getY()*64-a, /**/musuh[j].getX()*64+ (musuh[j].getaHealth()/musuh[j].getHealth())*44,/**/ musuh[j].getY()*64+5-a, /**/sf::Color(0, 255, 0));
									
										} else 
										if (path[musuh[j].getPos()]==1){ //ke kanan			
											if (facingRight == false)
											{
												_spriteEnemy.FlipX(true);
												facingRight = true;
											} 
											_spriteEnemy.SetPosition(musuh[j].getX()*64+3+a, musuh[j].getY()*64);
											_mainWindow.Draw(_spriteEnemy);
											HP = sf::Shape::Rectangle(musuh[j].getX()*64+10+a, musuh[j].getY()*64, musuh[j].getX()*64+54 + a, musuh[j].getY()*64+5, sf::Color(255, 0, 0));
											aHP = sf::Shape::Rectangle(musuh[j].getX()*64+10+a, /**/musuh[j].getY()*64, /**/musuh[j].getX()*64+ (musuh[j].getaHealth()/musuh[j].getHealth())*44 + a,/**/ musuh[j].getY()*64+5, /**/sf::Color(0, 255, 0));
									
										} else
										if (path[musuh[j].getPos()]==2){ //ke bawah
											_spriteEnemy.SetPosition(musuh[j].getX()*64+3, musuh[j].getY()*64+a);
											_mainWindow.Draw(_spriteEnemy);
											HP = sf::Shape::Rectangle(musuh[j].getX()*64+10, musuh[j].getY()*64+a, musuh[j].getX()*64+54, musuh[j].getY()*64+5 +a, sf::Color(255, 0, 0));
											aHP = sf::Shape::Rectangle(musuh[j].getX()*64+10, /**/musuh[j].getY()*64+a, /**/musuh[j].getX()*64+ (musuh[j].getaHealth()/musuh[j].getHealth())*44,/**/ musuh[j].getY()*64+5 +a, /**/sf::Color(0, 255, 0));
									
										} else
										if (path[musuh[j].getPos()]==3){ //ke kiri
											if (facingRight == true)
											{
												_spriteEnemy.FlipX(true);
												facingRight = false;
											} 
											_spriteEnemy.SetPosition(musuh[j].getX()*64+3-a, musuh[j].getY()*64);
											_mainWindow.Draw(_spriteEnemy);
											HP = sf::Shape::Rectangle(musuh[j].getX()*64+10-a, musuh[j].getY()*64, musuh[j].getX()*64+54-a, musuh[j].getY()*64+5, sf::Color(255, 0, 0));
											aHP = sf::Shape::Rectangle(musuh[j].getX()*64+10-a, /**/musuh[j].getY()*64, /**/musuh[j].getX()*64+ (musuh[j].getaHealth()/musuh[j].getHealth())*44 -a,/**/ musuh[j].getY()*64+5, /**/sf::Color(0, 255, 0));
									
										} else {
									
										}
									}
									
									//draw HP bar
									_mainWindow.Draw(HP); _mainWindow.Draw(aHP);
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

							_mainWindow.Display();
							a += 64/20;

						}
						if ((cektemp)||(cektemp2)) // kondisi wave berhenti
						{
							cekwave = false;
						}
					}
					// next wave
					_spriteButtonStart.SetColor(sf::Color(255, 255, 255, 255));
				}
				break;	
			}

			case Help: {
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
					}
				}

				_imageButtonHelp.LoadFromFile("images/HelpScreen_1.png");
				_spriteButtonHelp.SetImage(_imageButtonHelp);
				_spriteButtonHelp.SetPosition(6*64+10, 180);

				_mainWindow.Draw(_spriteButtonHelp);
				_mainWindow.Draw(_spriteButtonStart);
				_mainWindow.Draw(_spriteButtonExit);

				//Bikin text-text yang ingin ditampilkan
				sf::String tPlayerM ;
				tPlayerM.SetText("Player Money: ");
				tPlayerM.SetSize(20);
				tPlayerM.SetColor(sf::Color(255,255,255));
				tPlayerM.SetPosition(16*64+20,155);
				kata2.push_back(tPlayerM);

				sf::String tEnemyM ;
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

				stringstream convert;

				convert << enemygold;

				sf::String tMoneyE;
				tMoneyE.SetText(convert.str());
				tMoneyE.SetSize(20);
				tMoneyE.SetColor(sf::Color(255,255,255));
				tMoneyE.SetPosition(16*64+40,230);
				_mainWindow.Draw(tMoneyE);

				convert.str("");
				convert << playergold;

				sf::String tMoneyP;
				tMoneyP.SetText(convert.str());
				tMoneyP.SetSize(20);
				tMoneyP.SetColor(sf::Color(255,255,255));
				tMoneyP.SetPosition(16*64+40,180);
				_mainWindow.Draw(tMoneyP);

				for (int i=0;i<kata2.size();++i)
				{
					_mainWindow.Draw(kata2[i]);
				}

				for (int i=0;i<stower.size();++i)
				{
					_mainWindow.Draw(stower[i]);
				}

				_mainWindow.Display();
				break;
			}
			default:break;
		}
	}
	_mainWindow.Close();
	
	return 0;
}

