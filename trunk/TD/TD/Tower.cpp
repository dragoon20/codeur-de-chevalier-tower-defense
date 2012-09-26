#include "StdAfx.h"
#include "Tower.h"
#include <cstdlib>

Tower::Tower() {
	x = 0;
	y = 0;
	Price = 0;
	Range = 0;
	Attack = 0;
	Element = "";
	Nama = "";
	Target = -1;
}

Tower::Tower(int basis, int ordinat, string name) {
	x = basis;
	y = ordinat;
	Nama = name;
	if (name == "Ember") { //Fire Level 1 
		Price = 12; 
		Range = 1;
		Attack = 50;
		Element = "Fire";
		Target = -1;
	}
	if (name == "Splash") { //Water Level 1
		Price = 12; 
		Range = 1;
		Attack = 50;
		Element = "Water";
		Target = -1;
	}
	if (name == "Sprout") { //Nature Level 1
		Price = 12; 
		Range = 1;
		Attack = 50;
		Element = "Nature";
		Target = -1;
	}
}

Tower::~Tower() {
}

Tower& Tower::operator= (const Tower& T) {
	x = T.x;
	y = T.y;
	Price = T.Price;
	Range = T.Range;
	Attack = T.Attack;
	Nama = T.Nama;
	Target = T.Target;
	Element = T.Element;
	Tower(x,y, Nama);
	return *this;
}

Tower::Tower(const Tower& T) {
	x = T.x;
	y = T.y;
	Price = T.Price;
	Range = T.Range;
	Attack = T.Attack;
	Nama = T.Nama;
	Target = T.Target;
	Element = T.Element;
}

void Tower::setX(int newX) {
	x = newX;
}

void Tower::setY(int newY) {
	y = newY;
}

void Tower::setPrice(int newPrice) {
	Price = newPrice;
}

void Tower::setElement(string newE) {
	Element = newE;
}

void Tower::setNama(string newNama) {
	Nama = newNama;
}

void Tower::setTarget(int newTarget) {
	Target = newTarget;
}

void Tower::setRange (int newRange) {
	Range = newRange;
}

void Tower::setAttack (int newAttack) {
	Attack = newAttack;
}

int Tower::getX() {
	return x;
}

int Tower::getY() {
	return y;
}

int Tower::getPrice() {
	return Price;
}

string Tower::getElement() {
	return Element;
}

int Tower::getTarget() {
	return Target;
}

string Tower::getNama() {
	return Nama;
}

int Tower::getRange() {
	return Range;
}

int Tower::getAttack() {
	return Attack;
}

void Tower::attack(Enemy* E)
{
	if (((Element=="Fire")&&((*E).getElement()=="Nature"))||
		((Element=="Nature")&&((*E).getElement()=="Water"))||
		((Element=="Water")&&((*E).getElement()=="Fire")))
	{
		// serangan unggul
		(*E).setaHealth((*E).getaHealth()-(Attack*2));
	}
	else
	if (((Element=="Water")&&((*E).getElement()=="Nature"))||
		((Element=="Fire")&&((*E).getElement()=="Water"))||
		((Element=="Nature")&&((*E).getElement()=="Fire")))
	{
		// serangan lemah
		(*E).setaHealth((*E).getaHealth()-(Attack/2));
	}
	else
	{
		// serangan biasa
		(*E).setaHealth((*E).getaHealth()-Attack);
	}									
}

Tower Tower::Upgrade(string NextName) {
	if ( (this->Nama == "Ember") && (NextName == "Blaze") ) {
		Nama = "Blaze";
		Element = "Fire";
		Price = 30; 
		Range = 1;
		Attack = 150;
	}
	else
	if ( (this->Nama == "Splash") && (NextName == "Torrent") ) {
		Nama = "Torrent";
		Element = "Water";
		Price = 30; 
		Range = 2;
		Attack = 100;
	}
	else
	if ( (this->Nama == "Sprout") && (NextName == "Meadow") ) {
		Nama = "Meadow";
		Element = "Nature";
		Price = 30; 
		Range = 3;
		Attack = 50;
	}
	return *this;
}

Tower* Tower::getUpgradelist(string Name) {
	Tower* ar;
	if (Name == "Ember") {
		ar = new Tower[1];
		ar[0].setNama("Blaze");
		ar[0].setElement("Fire");
		ar[0].setRange(1);
		ar[0].setAttack(150);
		ar[0].setPrice(30);
	}
	else 
	if (Name == "Splash") {
		ar = new Tower[1];
		ar[0].setNama("Torrent");
		ar[0].setElement("Water");
		ar[0].setRange(2);
		ar[0].setAttack(100);
		ar[0].setPrice(30);

	}
	else 
	if (Name == "Sprout") {
		ar = new Tower[1];
		ar[0].setNama("Meadow");
		ar[0].setElement("Nature");
		ar[0].setRange(3);
		ar[0].setAttack(50);
		ar[0].setPrice(30);		
	}
	return ar;
}

Tower* getTowerList() {
	Tower* ar;
	ar = new Tower[3];
	
	ar[0].setNama("Ember");
	ar[0].setElement("Fire");
	ar[0].setRange(1);
	ar[0].setAttack(50);
	ar[0].setPrice(12);
	
	ar[1].setNama("Splash");
	ar[1].setElement("Water");
	ar[1].setRange(1);
	ar[1].setAttack(50);
	ar[1].setPrice(12);

	ar[2].setNama("Sprout");
	ar[2].setElement("Nature");
	ar[2].setRange(1);
	ar[2].setAttack(50);
	ar[2].setPrice(12);

	return ar;
}