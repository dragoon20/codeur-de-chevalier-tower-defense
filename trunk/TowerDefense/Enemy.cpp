#include "StdAfx.h"
#include "Enemy.h"
#include <cstring>

Enemy::Enemy()
{
	// ga mungkin dipanggil
	Speed = 0;
	aSpeed = 0;
	Health = 0;
	aHealth = 0;
	x = 0;
	y = 0;
	Price = 0;
	strcpy(Name,"");
	strcpy(Element,"");
}

Enemy::Enemy(char* Name)
{
	strcpy(this->Name,Name);
	if (strcmp(Name,""))
	{
		x = -1;
		y = -1;
		Speed = 1;
		aSpeed = 1;
		Health = 1;
		aHealth = 1;
		strcpy(Element,"");
	}
	else if (strcmp(Name,""))
	{
		x = -1;
		y = -1;
		Speed = 1;
		aSpeed = 1;
		Health = 1;
		aHealth = 1;
		strcpy(Element,"");
	}
	else if (strcmp(Name,""))
	{
		x = -1;
		y = -1;
		Speed = 1;
		aSpeed = 1;
		Health = 1;
		aHealth = 1;
		strcpy(Element,"");
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
	strcpy(Name,E.Name);
	strcpy(Element,E.Element);
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
	strcpy(Name,E.Name);
	strcpy(Element,E.Element);
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

int Enemy::getx()
{
	return x;
}

int Enemy::gety()
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

char * Enemy::getName()
{
	// masih ragu
	return Name;
}

char * Enemy::getElement()
{
	// masih ragu
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

void Enemy::setx(int x)
{
	this->x = x;
}

void Enemy::sety(int y)
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

void Enemy:setReward(int Reward)
{
	this->Reward = Reward;
}

void Enemy::setName(char* Name)
{
	strcpy(this->Name,Name);
}

void Enemy::setElement(char* Element)
{
	strcpy(this->Element,Element);
}

Enemy Enemy::Upgrade (char* Name)
{
	if ((strcmp(this->Name,"")==0)&&(strcmp(Name,"")==0))
	{
		strcpy(this->Name,Name);
		x = -1;
		y = -1;
		Speed = 1;
		aSpeed = 1;
		Health = 1;
		aHealth = 1;
		strcpy(Element,"");
	}
	else if ((strcmp(this->Name,"")==0)&&(strcmp(Name,"")==0))
	{
		strcpy(this->Name,Name);
		x = -1;
		y = -1;
		Speed = 1;
		aSpeed = 1;
		Health = 1;
		aHealth = 1;
		strcpy(Element,"");
	}
	return *this;
}
