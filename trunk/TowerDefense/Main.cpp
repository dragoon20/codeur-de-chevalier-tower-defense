#include "Enemy.h"
#include "Tower.h"
#include "Field.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

int main()
{
	vector<Enemy> musuh;
	vector<Tower> tower;
	Field field;
	int enemygold = 10;
	int playergold = 10;
	
	Enemy * listmusuh = getEnemylist();
	Tower * listtower = getTowerList();

	bool cekpersiapan;
	bool cekwave;
	
	int mode = 1; // mode player
	
	if (mode==1)
	{
		while(true)
		{
			cekpersiapan = true;
			while (cekpersiapan)
			{
				if () // kondisi persiapan selesai
				{
					cekpersiapan = false;
				}
			}
			
			// greedy musuh di sini
			// berdasarkan kondisi dari field saat ini
			
			
			// menentukan jalur yang ingin dilalui musuh dengan djikstra
			int* path = field.getPath().path;
			int pathsize = field.getPath().size;
			for (int j=musuh.size()-1;j>=0;--j)
			{
				// set urutan, darah, kecepatan, posisi musuh dan musuh dapat pemasukan
				musuh[j].setPos(musuh.size()*-1-1);
				musuh[j].setaHealth(musuh[j].getHealth());
				musuh[j].setaSpeed(musuh[j].getSpeed());
				musuh[j].setX(-1);
				musuh[j].setY(-1);
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
						if (((tower[i].getElement=="Fire")&&(musuh[j].getElement=="Nature"))||
							((tower[i].getElement=="Nature")&&(musuh[j].getElement=="Water"))||
							((tower[i].getElement=="Water")&&(musuh[j].getElement=="Fire")))
						{
							// serangan unggul
							musuh[j].setaHealth(musuh[j].getaHealth()-(tower[i].getAttack()*2));
						}
						else
						if (((tower[i].getElement=="Water")&&(musuh[j].getElement=="Nature"))||
							((tower[i].getElement=="Fire")&&(musuh[j].getElement=="Water"))||
							((tower[i].getElement=="Nature")&&(musuh[j].getElement=="Fire")))
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
							if ((musuh[j].getaHealth>0)&&(abs(tower[i].getX()-musuh[j].getX())+abs(tower[i].getY()-musuh[j].getY())<=tower[i].getRange()))
							// jika tower dapat menyerang musuh (dalam jangkauan) dann tower sedang tidak ada target 
							// health musuh berkurang
							{
								tower[i].setTarget(j);
								if (((tower[i].getElement=="Fire")&&(musuh[j].getElement=="Nature"))||
									((tower[i].getElement=="Nature")&&(musuh[j].getElement=="Water"))||
									((tower[i].getElement=="Water")&&(musuh[j].getElement=="Fire")))
								{
									// serangan unggul
									musuh[j].setaHealth(musuh[j].getaHealth()-(tower[i].getAttack()*2));
								}
								else
								if (((tower[i].getElement=="Water")&&(musuh[j].getElement=="Nature"))||
									((tower[i].getElement=="Fire")&&(musuh[j].getElement=="Water"))||
									((tower[i].getElement=="Nature")&&(musuh[j].getElement=="Fire")))
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
				int j=0;
				while (j<musuh.size())
				{
					// cek apakah semua musuh telah mati
					if (musuh[j].getaHealth>0)
						cektemp = false;
					// musuh bergerak
					++j;
				}
				
				if (cektemp) // kondisi wave berhenti
				{
					cekwave = false;
				}
			}
			// next wave
		}
	}
	else
	{
		cekpersiapan = true;
		while (cekpersiapan)
		{
			if () // kondisi persiapan selesai
			{
				cekpersiapan = false;
			}
		}
		cekwave = true;
		while (cekwave)
		{
			if () // kondisi wave berhenti
			{
				cekwave = false;
			}
		}
	}

	return 0;
}