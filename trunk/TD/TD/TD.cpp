// TD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Enemy.h"
#include "Tower.h"
#include "Field.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "GameObjectManager.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

const static int SCREEN_WIDTH = 1024;
const static int SCREEN_HEIGHT = 768;

enum GameState { Uninitialized, ShowingSplash, Paused, 
        ShowingMenu, Playing, Exiting };
  
static GameState _gameState;
static sf::RenderWindow _mainWindow;
  
static GameObjectManager _gameObjectManager;
static Field _field;

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

int main()
{
	// variabel
	vector<Enemy> musuh;
	vector<Tower> tower;
	Field field;
	int enemygold = 10;
	int playergold = 10;
	musuh.push_back(Enemy("Salamander"));
	tower.push_back(Tower(2,4,"Splash"));
	tower.push_back(Tower(2,3,"Splash"));
	tower.push_back(Tower(3,4,"Splash"));
	tower.push_back(Tower(3,3,"Splash"));
	Enemy * listmusuh = getEnemylist();
	Tower * listtower = getTowerList();

	bool cekpersiapan;
	bool cekwave;
	
	int mode = 1; // mode player


	if(_gameState != Uninitialized)
		return 0;

	_mainWindow.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32),"La tour de défense");
	_field.Load("example.txt");
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
		  
				_gameObjectManager.UpdateAll();
				_gameObjectManager.DrawAll(_mainWindow);
		  
				if(currentEvent.Type == sf::Event::Closed) _gameState = Exiting;

				if(currentEvent.Type == sf::Event::KeyPressed)
				{
					if(currentEvent.Key.Code == sf::Key::Escape) ShowMenu();
				}

				/*cekpersiapan = true;
				while (cekpersiapan)
				{
					if () // kondisi persiapan selesai
					{
						cekpersiapan = false;
					}
				}*/
			
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
					musuh[j].setPos(musuh.size()*-1-1);
					musuh[j].setaHealth(musuh[j].getHealth());
					musuh[j].setaSpeed(musuh[j].getSpeed());
					musuh[j].setX(-1);
					musuh[j].setY(5);
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
							j = tower[i].getTarget();
							if (((tower[i].getElement()=="Fire")&&(musuh[j].getElement()=="Nature"))||
								((tower[i].getElement()=="Nature")&&(musuh[j].getElement()=="Water"))||
								((tower[i].getElement()=="Water")&&(musuh[j].getElement()=="Fire")))
							{
								// serangan unggul
								musuh[j].setaHealth(musuh[j].getaHealth()-(tower[i].getAttack()*2));
							}
							else
							if (((tower[i].getElement()=="Water")&&(musuh[j].getElement()=="Nature"))||
								((tower[i].getElement()=="Fire")&&(musuh[j].getElement()=="Water"))||
								((tower[i].getElement()=="Nature")&&(musuh[j].getElement()=="Fire")))
							{
								// serangan lemah
								musuh[j].setaHealth(musuh[j].getaHealth()-(tower[i].getAttack()/2));
							}
							else
							{
								// serangan biasa
								musuh[j].setaHealth(musuh[j].getaHealth()-tower[i].getAttack());
							}
							if (musuh[j].getaHealth()<=0)
							{
								// musuh mati dan player dapat uang
								playergold += musuh[j].getReward();
								tower[i].setTarget(-1);
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
									tower[i].setTarget(j);
									if (((tower[i].getElement()=="Fire")&&(musuh[j].getElement()=="Nature"))||
										((tower[i].getElement()=="Nature")&&(musuh[j].getElement()=="Water"))||
										((tower[i].getElement()=="Water")&&(musuh[j].getElement()=="Fire")))
									{
										// serangan unggul
										musuh[j].setaHealth(musuh[j].getaHealth()-(tower[i].getAttack()*2));
									}
									else
									if (((tower[i].getElement()=="Water")&&(musuh[j].getElement()=="Nature"))||
										((tower[i].getElement()=="Fire")&&(musuh[j].getElement()=="Water"))||
										((tower[i].getElement()=="Nature")&&(musuh[j].getElement()=="Fire")))
									{
										// serangan lemah
										musuh[j].setaHealth(musuh[j].getaHealth()-(tower[i].getAttack()/2));
									}
									else
									{
										// serangan biasa
										musuh[j].setaHealth(musuh[j].getaHealth()-tower[i].getAttack());
									}
									if (musuh[j].getaHealth()<=0)
									{
										// musuh mati dan player dapat uang
										playergold += musuh[j].getReward();
										tower[i].setTarget(-1);
									}
								
									cekmusuh = false;
								}
								j++;
							}
						
						}
					}
			
					bool cektemp = true;
					bool cektemp2 = true;
					int j=0;
					while (j<musuh.size())
					{
						// cek apakah semua musuh telah mati
						if (musuh[j].getaHealth()>0)
							cektemp = false;
						// musuh bergerak
						if ((musuh[j].getPos()>=0)&&(musuh[j].getPos()<=pathsize))
						{
							cektemp2 = false;
							for (int k=0;k<musuh[j].getaSpeed();++k)
							{
								switch(path[musuh[j].getPos()+k])
								{
									case 0: // ke atas
									{
										musuh[j].setY(musuh[j].getY()-1);
										break;
									}
									case 1: // ke kanan
									{
										musuh[j].setX(musuh[j].getX()+1);
										break;
									}
									case 2: // ke bawah
									{
										musuh[j].setY(musuh[j].getY()+1);
										break;
									}
									case 3: // ke kiri
									{
										musuh[j].setX(musuh[j].getX()-1);
										break;
									}
								}
							}
						}
						else if (musuh[j].getPos()<0)
						{
							cektemp2 = false;
						}
						musuh[j].setPos(musuh[j].getPos()+musuh[j].getaSpeed());
						cout << musuh[j].getX() << " " << musuh[j].getY() << endl;
						++j;
					}
				
					if ((cektemp)||(cektemp2)) // kondisi wave berhenti
					{
						cekwave = false;
					}
				}
				// next wave

				_mainWindow.Display();
				break;
			}
		}
	}
	_mainWindow.Close();
	
	return 0;
}

