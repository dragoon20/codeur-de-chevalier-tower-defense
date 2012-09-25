#ifndef TOWER_H
#define TOWER_H

#include <string>
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
		void setTarget(string);
		void setRange(int);
		void setAttack(int);

		int getX();
		int getY();
		int getPrice();
		string getElement();
		string getNama();
		string getTarget();
		int getRange();
		int getAttack();

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
		string Target; // ID musuh
};

Tower* getTowerList();
#endif