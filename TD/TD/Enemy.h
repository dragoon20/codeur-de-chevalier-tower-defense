#ifndef __ENEMY__
#define __ENEMY__

#include <string>

using namespace std;

class Enemy
{
	private:
		int Speed;
		int aSpeed;
		int Health;
		int aHealth;
		int x;
		int y;
		int Price;
		int Income;
		int Reward;
		int Pos;
		string Name;
		string Element;
	public:
		Enemy();
		Enemy(string);
		~Enemy();
		Enemy(const Enemy&);
		Enemy& operator = (const Enemy&);
		
		int getSpeed();
		int getaSpeed();
		int getHealth();
		int getaHealth();
		int getX();
		int getY();
		int getPrice();
		int getIncome();
		int getReward();
		int getPos();
		string getName();
		string getElement();
		
		void setSpeed(int);
		void setaSpeed(int);
		void setHealth(int);
		void setaHealth(int);
		void setX(int);
		void setY(int);
		void setPrice(int);
		void setIncome(int);
		void setReward(int);
		void setPos(int);
		void setName(string);
		void setElement(string);
		
		Enemy Upgrade (string);
		Enemy* getUpgradelist (string);
};

Enemy* getEnemylist ();

#endif