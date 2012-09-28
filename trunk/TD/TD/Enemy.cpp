#include "StdAfx.h"
#include "Enemy.h"
#include <cstdlib>

Enemy::Enemy()
{
	Speed = 0;
	aSpeed = 0;
	Health = 0;
	aHealth = 0;
	x = -1;
	y = -1;
	Price = 0;
	Income = 0;
	Reward = 0;
	Name = "";
	Element = "";
}

Enemy::Enemy(string Name)
{
	this->Name = Name;
	if (Name=="Salamander")
	{
		x = -1;
		y = -1;
		Speed = 1;
		aSpeed = 1;
		Health = 75;
		aHealth = 75;
		Price = 2;
		Income = 1;
		Reward = 1;
		Element = "Fire";
	}
	else if (Name=="Lizardman")
	{
		x = -1;
		y = -1;
		Speed = 1;
		aSpeed = 1;
		Health = 75;
		aHealth = 75;
		Price = 2;
		Income = 1;
		Reward = 1;
		Element = "Water";
	}
	else if (Name=="Mandragora")
	{
		x = -1;
		y = -1;
		Speed = 1;
		aSpeed = 1;
		Health = 75;
		aHealth = 75;
		Price = 2;
		Income = 1;
		Reward = 1;
		Element = "Nature";
	}
}

Enemy::~Enemy()
{
}

Enemy::Enemy(const Enemy& E)
{
	x = E.x;
	y = E.y;
	Speed = E.Speed;
	aSpeed = E.aSpeed;
	Health = E.Health;
	aHealth = E.aHealth;
	Price = E.Price;
	Income = E.Income;
	Reward = E.Reward;
	Name = E.Name;
	Element = E.Element;
}

Enemy& Enemy::operator = (const Enemy& E)
{
	x = E.x;
	y = E.y;
	Speed = E.Speed;
	aSpeed = E.aSpeed;
	Health = E.Health;
	aHealth = E.aHealth;
	Price = E.Price;
	Income = E.Income;
	Reward = E.Reward;
	Name = E.Name;
	Element = E.Element;
	return *this;
}

int Enemy::getSpeed()
{
	return Speed;
}

int Enemy::getaSpeed()
{
	return aSpeed;
}

int Enemy::getHealth()
{
	return Health;
}

int Enemy::getaHealth()
{
	return aHealth;
}

int Enemy::getX()
{
	return x;
}

int Enemy::getY()
{
	return y;
}

int Enemy::getPrice()
{
	return Price;
}

int Enemy::getIncome()
{
	return Income;
}

int Enemy::getReward()
{
	return Reward;
}

int Enemy::getPos()
{
	return Pos;
}

string Enemy::getName()
{
	// sudah yakin
	return Name;
}

string Enemy::getElement()
{
	// sudah yakin
	return Element;
}

void Enemy::setSpeed(int Speed)
{
	this->Speed = Speed;
}

void Enemy::setaSpeed(int aSpeed)
{
	this->aSpeed = aSpeed;
}

void Enemy::setHealth(int Health)
{
	this->Health = Health;
}

void Enemy::setaHealth(int aHealth)
{
	this->aHealth = aHealth;
}

void Enemy::setX(int x)
{
	this->x = x;
}

void Enemy::setY(int y)
{
	this->y = y;
}

void Enemy::setPrice(int Price)
{
	this->Price = Price;
}

void Enemy::setIncome(int Income)
{
	this->Income = Income;
}

void Enemy::setReward(int Reward)
{
	this->Reward = Reward;
}

void Enemy::setPos(int Pos)
{
	this->Pos = Pos;
}

void Enemy::setName(string Name)
{
	this->Name = Name;
}

void Enemy::setElement(string Element)
{
	this->Element = Element;
}

void Enemy::move(int flag)
{
	switch(flag)
	{
		case 0: // ke atas
		{
			y-=1;
			break;
		}
		case 1: // ke kanan
		{
			x+=1;
			break;
		}
		case 2: // ke bawah
		{
			y+=1;
			break;
		}
		case 3: // ke kiri
		{
			x-=1;
			break;
		}
	}
}

Enemy* getEnemylist ()
{
	static Enemy* pointer;
	pointer = new Enemy[3];
	
	pointer[0].setName("Salamander");
	pointer[0].setSpeed(1);
	pointer[0].setHealth(75);
	pointer[0].setPrice(2);
	pointer[0].setIncome(1);
	pointer[0].setReward(1);
	pointer[0].setElement("Fire");
	
	pointer[1].setName("Lizardman");
	pointer[1].setSpeed(1);
	pointer[1].setHealth(75);
	pointer[1].setPrice(2);
	pointer[1].setIncome(1);
	pointer[1].setReward(1);
	pointer[1].setElement("Water");
	
	pointer[2].setName("Mandragora");
	pointer[2].setSpeed(1);
	pointer[2].setHealth(75);
	pointer[2].setPrice(2);
	pointer[2].setIncome(1);
	pointer[2].setReward(1);
	pointer[2].setElement("Nature");

	return pointer;
}

Enemy Enemy::Upgrade (string Name)
{
	if ((this->Name=="Salamander")&&(Name=="Efreet"))
	{
		this->Name = Name;
		x = -1;
		y = -1;
		Speed = 1;
		aSpeed = 1;
		Health = 225;
		aHealth = 225;
		Price = 30;
		Income = 5;
		Reward = 5;
		Element = "Fire";
	}
	else if ((this->Name=="Lizardman")&&(Name=="Undine"))
	{
		this->Name = Name;
		x = -1;
		y = -1;
		Speed = 1;
		aSpeed = 1;
		Health = 150;
		aHealth = 150;
		Price = 30;
		Income = 5;
		Reward = 5;
		Element = "Water";
	}
	else if ((this->Name=="Mandragora")&&(Name=="Dryad"))
	{
		this->Name = Name;
		x = -1;
		y = -1;
		Speed = 1;
		aSpeed = 1;
		Health = 300;
		aHealth = 300;
		Price = 30;
		Income = 5;
		Reward = 5;
		Element = "Nature";
	}
	return *this;
}

Enemy* Enemy::getUpgradelist (string Name)
{
	Enemy* pointer;
	if (Name=="Salamander")
	{
		pointer = new Enemy[1];
		pointer[0].setName("Efreet");
		pointer[0].setSpeed(1);
		pointer[0].setHealth(225);
		pointer[0].setPrice(30);
		pointer[0].setIncome(5);
		pointer[0].setElement("Fire");
	}
	else if (this->Name=="Lizardman")
	{
		pointer = new Enemy[1];
		pointer[0].setName("Undine");
		pointer[0].setSpeed(1);
		pointer[0].setHealth(150);
		pointer[0].setPrice(30);
		pointer[0].setIncome(5);
		pointer[0].setElement("Water");
	}
	else if (this->Name=="Mandragora")
	{
		pointer = new Enemy[1];
		pointer[0].setName("Undine");
		pointer[0].setSpeed(1);
		pointer[0].setHealth(300);
		pointer[0].setPrice(30);
		pointer[0].setIncome(5);
		pointer[0].setElement("Nature");
	}
	return pointer;
}