#ifndef __TOWER__
#define __TOWER__

#include <string>
#include "Enemy.h"
using namespace std;

class Tower {
	public:
		Tower();
		Tower(int,int,string); //Tower(x,y,Element)
		~Tower();
		Tower(const Tower&);
		Tower& operator= (const Tower&);

		void setX(int);
		void setY(int);
		void setPrice(int);
		void setElement(string);
		void setNama(string);
		void setTarget(int);
		void setRange(int);
		void setAttack(int);

		int getX();
		int getY();
		int getPrice();
		string getElement();
		string getNama();
		int getTarget();
		int getRange();
		int getAttack();

		void attack(Enemy*);

		Tower Upgrade(string);
		Tower* getUpgradelist(string);
	
	private:
		int x; //absis
		int y; //ordinat
		int Price; //harga beli tower
		int Range; //jarak tembakan
		int Attack;
		string Element;
		string Nama;
		int Target; // nomor urut musuh pada array di controller
};

Tower* getTowerList();
#endif