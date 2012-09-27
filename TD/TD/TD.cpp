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
using namespace std;

/* ---- Bagian Menu Utama ---- */

const static int SCREEN_WIDTH = 1216;
const static int SCREEN_HEIGHT = 768;

enum GameState { Uninitialized, ShowingSplash, Paused, 
        ShowingMenu, Playing, Exiting };
  
static GameState _gameState;
static sf::RenderWindow _mainWindow;
  
static GameObjectManager _gameObjectManager;
static Field _field;

static sf::Image	_imageTower;
static sf::Sprite	_spriteTower;

static sf::Image	_imageEnemy;
static sf::Sprite	_spriteEnemy;

static sf::Image	_imageTile;
static sf::Sprite	_spriteTile;

static sf::Image	_imageButtonStart;
static sf::Sprite	_spriteButtonStart;

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
		case MainMenu::Play:
			_gameState = Playing;
			break;
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
	Field field;
	int enemygold = 10;
	int playergold = 10;
	Enemy * listmusuh = getEnemylist();
	Tower * listtower = getTowerList();
	
	musuh.push_back(listmusuh[0]);
	musuh.push_back(listmusuh[1]);
	musuh.push_back(listmusuh[2]);
	musuh.push_back(listmusuh[2]);
	tower.push_back(Tower(3,3,"Splash"));
	tower.push_back(Tower(3,5,"Splash"));

	bool cekpersiapan;
	bool cekwave;
	
	int mode = 1; // mode player


	if(_gameState != Uninitialized)
		return 0;

	_mainWindow.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32),"La tour de défense");
	_mainWindow.SetFramerateLimit(60);
	_field.Load("example.txt");
	
	_imageTower.LoadFromFile("images/tower.png");
	_spriteTower.SetImage(_imageTower);

	_imageEnemy.LoadFromFile("images/enemy.png");
	_spriteEnemy.SetImage(_imageEnemy);

	//button
	_imageButtonStart.LoadFromFile("images/start.png");
	_spriteButtonStart.SetImage(_imageButtonStart);
	_spriteButtonStart.SetPosition(16*64+10, 10);


	_gameState = ShowingSplash;
  
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
			case ShowingSplash:
			{
				ShowSplashScreen();
				break;
			}
			case Playing:
			{
				_mainWindow.Clear(sf::Color(0,0,0));
				_field.Draw(_mainWindow);
				for (int i=0;i<tower.size();++i){
					_spriteTower.SetPosition(tower[i].getX()*64, tower[i].getY()*64);
					_mainWindow.Draw(_spriteTower);
				}

				_mainWindow.Draw(_spriteButtonStart);
		  
				//_gameObjectManager.UpdateAll();
				//_gameObjectManager.DrawAll(_mainWindow);
		  
				
				if(currentEvent.Type == sf::Event::Closed) {_gameState = Exiting;}
				/*if(currentEvent.Type == sf::Event::KeyPressed)
				{
					if(currentEvent.Key.Code == sf::Key::Escape) ShowMenu();
				}*/

				_mainWindow.Display();

				cekpersiapan = true;
				while (cekpersiapan)
				{
					//Bikin tombol-tombol menu
					MenuItem startButton;
					startButton.rect.Top= 0;
					startButton.rect.Bottom = 38;
					startButton.rect.Left = 16*64;
					startButton.rect.Right = 16*64+153;
					startButton.action = Start;
					_menuItems.push_back(startButton);
					
					MenuItem menuButton;
					menuButton.rect.Top= 145;
					menuButton.rect.Bottom = 380;
					menuButton.rect.Left = 0;
					menuButton.rect.Right = 1023;
					menuButton.action = Menu;
					_menuItems.push_back(menuButton);

					MenuItem exitButton;
					exitButton.rect.Top= 145;
					exitButton.rect.Bottom = 380;
					exitButton.rect.Left = 0;
					exitButton.rect.Right = 1023;
					exitButton.action = Exit;
					_menuItems.push_back(exitButton);

					MenuItem towerButton1;
					towerButton1.rect.Top= 145;
					towerButton1.rect.Bottom = 380;
					towerButton1.rect.Left = 0;
					towerButton1.rect.Right = 1023;
					towerButton1.action = Build;
					towerButton1.id = 1;
					_menuItems.push_back(towerButton1);

					MenuItem towerButton2;
					towerButton2.rect.Top= 145;
					towerButton2.rect.Bottom = 380;
					towerButton2.rect.Left = 0;
					towerButton2.rect.Right = 1023;
					towerButton2.action = Build;
					towerButton2.id = 2;
					_menuItems.push_back(towerButton2);

					MenuItem towerButton3;
					towerButton3.rect.Top= 145;
					towerButton3.rect.Bottom = 380;
					towerButton3.rect.Left = 0;
					towerButton3.rect.Right = 1023;
					towerButton3.action = Build;
					towerButton3.id = 3;
					_menuItems.push_back(towerButton3);

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
				
				if (_gameState==Playing)
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
							if ((tower[i].getTarget()!=-1)&&(abs(tower[i].getX()-musuh[tower[i].getTarget()].getX())+abs(tower[i].getY()-musuh[tower[i].getTarget()].getY())<=tower[i].getRange()))
							// tower sudah ada target dan musuh masih dalam range
							{
								cout << "Tower "<< tower[i].getNama() << "(" << tower[i].getX() << "," << tower[i].getY() << ") menyerang " << musuh[j].getName()<< " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ")" << endl;

								j = tower[i].getTarget();
								tower[i].attack(&musuh[j]);
								if (musuh[j].getaHealth()<=0)
								{
									// musuh mati dan player dapat uang
									playergold += musuh[j].getReward();
									tower[i].setTarget(-1);
									cout << "Monster " << musuh[j].getName() << " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ")" << " tewas" << endl;
									/*musuh[j].setX(-1);
									musuh[j].setY(4);
									musuh[j].setPos(j*-1-1);*/
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

										tower[i].setTarget(j);
										tower[i].attack(&musuh[j]);
										if (musuh[j].getaHealth()<=0)
										{
											// musuh mati dan player dapat uang
											playergold += musuh[j].getReward();
											tower[i].setTarget(-1);
											cout << "Monster " << musuh[j].getName() << " " << j+1 << "(" << musuh[j].getX() << "," << musuh[j].getY() << ")" << " tewas" << endl;
											/*musuh[j].setX(-1);
											musuh[j].setY(4);
											musuh[j].setPos(j*-1-1);*/
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
							_spriteTower.SetPosition(tower[i].getX()*64, tower[i].getY()*64);
							_mainWindow.Draw(_spriteTower);
						}
						_mainWindow.Draw(_spriteButtonStart);

						bool cektemp = true;
						bool cektemp2 = true;
						int j=0;
						while (j<musuh.size())
						{
							// cek apakah semua musuh telah mati
							if (musuh[j].getaHealth()>0)
								cektemp = false;
							// musuh bergerak
							if ((musuh[j].getaHealth()>0)&&(musuh[j].getPos()>=0)&&(musuh[j].getPos()<=pathsize))
							{
								cektemp2 = false;
								
								for (int k=0;k<musuh[j].getaSpeed();++k)
								{
									musuh[j].move(path[musuh[j].getPos()+k]);								
								}
								
								
								cout << musuh[j].getName() << " " << j+1 << " bergerak ke titik (" << musuh[j].getX() << "," << musuh[j].getY() << ")" << endl;
								/**draw enemy**/
								if (musuh[j].getName()=="Lizardman"){
									_spriteEnemy.SetSubRect(sf::IntRect(0, 0, 64, 64));
								} else if (musuh[j].getName()=="Salamander"){
									_spriteEnemy.SetSubRect(sf::IntRect(64, 0, 128, 64));
								} else if (musuh[j].getName()=="Mandragora"){
									_spriteEnemy.SetSubRect(sf::IntRect(128, 0, 192, 64));
								} else if (musuh[j].getName()=="Undine"){
									_spriteEnemy.SetSubRect(sf::IntRect(0, 64, 64, 128));
								} else if (musuh[j].getName()=="Efreet"){
									_spriteEnemy.SetSubRect(sf::IntRect(64, 64, 128, 128));
								} else if (musuh[j].getName()=="Dryad"){
									_spriteEnemy.SetSubRect(sf::IntRect(128, 64, 192, 128));
								}
								_spriteEnemy.SetPosition(musuh[j].getX()*64, musuh[j].getY()*64);
								_mainWindow.Draw(_spriteEnemy);
								
							}
							else if (musuh[j].getPos()<0)
							{
								cektemp2 = false;
							}
							
							if (musuh[j].getaHealth()>0){}
								musuh[j].setPos(musuh[j].getPos()+musuh[j].getaSpeed());
							++j;
						}
						_mainWindow.Display();
						float a = 0;
						for (int l=0;l<20;l++){
							_mainWindow.Clear();
							_field.Draw(_mainWindow);
							for (int i=0;i<tower.size();++i){
								_spriteTower.SetPosition(tower[i].getX()*64, tower[i].getY()*64);
								_mainWindow.Draw(_spriteTower);
							}
							
							for (int j=0;j<musuh.size();++j)
							{								
								if (musuh[j].getaHealth()>0)
								{
									// pilih gambar
									if (musuh[j].getName()=="Lizardman"){
										_spriteEnemy.SetSubRect(sf::IntRect(0, 0, 64, 64));
									} else if (musuh[j].getName()=="Salamander"){
										_spriteEnemy.SetSubRect(sf::IntRect(64, 0, 128, 64));
									} else if (musuh[j].getName()=="Mandragora"){
										_spriteEnemy.SetSubRect(sf::IntRect(128, 0, 192, 64));
									} else if (musuh[j].getName()=="Undine"){
										_spriteEnemy.SetSubRect(sf::IntRect(0, 64, 64, 128));
									} else if (musuh[j].getName()=="Efreet"){
										_spriteEnemy.SetSubRect(sf::IntRect(64, 64, 128, 128));
									} else if (musuh[j].getName()=="Dryad"){
										_spriteEnemy.SetSubRect(sf::IntRect(128, 64, 192, 128));
									}

									if ((musuh[j].getPos() > 0) && (musuh[j].getPos() < pathsize)){
										if (path[musuh[j].getPos()]==0){
											_spriteEnemy.SetRotation(0.0f);
											_spriteEnemy.SetPosition((musuh[j].getX())*64, (musuh[j].getY())*64-a);
											_mainWindow.Draw(_spriteEnemy);
										} else 
										if (path[musuh[j].getPos()]==1){			
											_spriteEnemy.SetRotation(90.0f);
											_spriteEnemy.SetPosition((musuh[j].getX())*64+a, (musuh[j].getY())*64);
											_mainWindow.Draw(_spriteEnemy);
										} else
										if (path[musuh[j].getPos()]==2){
											_spriteEnemy.SetRotation(180.0f);
											_spriteEnemy.SetPosition((musuh[j].getX())*64, (musuh[j].getY())*64+a);
											_mainWindow.Draw(_spriteEnemy);
										} else
										if (path[musuh[j].getPos()]==3){
											_spriteEnemy.SetRotation(270.0f);
											_spriteEnemy.SetPosition((musuh[j].getX())*64-a, (musuh[j].getY())*64);
											_mainWindow.Draw(_spriteEnemy);
										} else {
									
										}
									}
								}								
							}
							
							_mainWindow.Draw(_spriteButtonStart);
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
			default:break;
		}
	}
	_mainWindow.Close();
	
	return 0;
}

