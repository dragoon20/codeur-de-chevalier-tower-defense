#ifndef TOWER_H
#define TOWER_H

class Tower {
	public:
		Tower();
		Tower(int,int,char*); //Tower(x,y,Element)
		~Tower();
		Tower(const Tower&);
		Tower& operator= (const Tower&);

		void setX(int);
		void setY(int);
		void setPrice(int);
		void setElement(char*);
		void setNama(char*);
		void setTarget(char*);
		void setRange(int);
		void setAttack(int);

		int getX();
		int getY();
		int getPrice();
		char* getElement();
		char* getNama();
		char* getTarget();
		int getRange();
		int getAttack();

		Tower Upgrade(char* Name);
		
	private:
		int x; //absis
		int y; //ordinat
		int Price; //harga beli tower
		int Range; //jarak tembakan
		int Attack;
		char* Element;
		char* Nama;
		char* Target; // ID musuh
};
#endif