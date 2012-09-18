#ifndef TOWER_H
#define TOWER_H
class Tower {
	public:
		Tower();
		Tower(int,int,char); //Tower(x,y,Element)
		~Tower();
		Tower(const Tower&);
		Tower& operartor= (const Tower&);

		void setX(int);
		void setY(int);
		void setPrice(int);
		void setElement(char);
		void setArah(int);
		void setRange(int);
		void setAttack(int);

		int getX();
		int getY();
		int getPrice();
		char getElement();
		int getArah();
		int getRange();
		int getAttack();

		Tower Upgrade();
	private:
		int x; //absis
		int y; //ordinat
		int Price; //harga beli tower
		int Range; //jarak tembakan
		int Arah; //Arah 0-8 dimulai dari utara, putar searah jarum jam
		int Attack;
		char Element;
};
#endif