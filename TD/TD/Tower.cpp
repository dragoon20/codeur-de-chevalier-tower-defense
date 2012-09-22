#include "Tower.h"
#include <stdio.h>
#include <string.h>
using namespace std;

Tower::Tower() {
	x = 0;
	y = 0;
	Price = 0;
	Range = 0;
	Attack = 0;
	Element = NULL;
	Nama = NULL;
	Target = NULL;
}

Tower::Tower(int basis, int ordinat, char* name) {
	x = basis;
	y = ordinat;
	if (strcmp(name,"Tower_Batu") == 0) { //Batu
		Price = 1500; 
		Range = 1;
		Attack = 5;
		strcpy(Element, "Batu");
		Target = NULL;
		strcpy(Nama, name);
	}
	if (strcmp(name, "Tower_Gunting") == 0) { //Gunting
		Price = 1250; 
		Range = 1;
		Attack = 5;
		strcpy(Element,"Gunting");
		Target = NULL;
		strcpy(Nama, name);
	}
	if (strcmp(name, "Tower_Kertas") == 0) { //Kertas
		Price = 1000; 
		Range = 1;
		Attack = 5;
		strcpy(Element,"Kertas");
		Target = NULL;
		strcpy(Nama, name);
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
	strcpy(Nama, T.Nama);
	strcpy(Target, T.Target);
	strcpy(Element, T.Element);
	Tower(x,y, Nama);
	return *this;
}

Tower::Tower(const Tower& T) {
	x = T.x;
	y = T.y;
	Price = T.Price;
	Range = T.Range;
	Attack = T.Attack;
	strcpy(Nama, T.Nama);
	strcpy(Target, T.Target);
	strcpy(Element, T.Element);
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

void Tower::setElement(char* newE) {
	strcpy(Element, newE);
}

void Tower::setNama(char* newNama) {
	strcpy(Nama, newNama);
}

void Tower::setTarget(char* newTarget) {
	strcpy(Target, newTarget);
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

char* Tower::getElement() {
	return Element;
}

char* Tower::getTarget() {
	return Target;
}

char* Tower::getNama() {
	return Nama;
}

int Tower::getRange() {
	return Range;
}

int Tower::getAttack() {
	return Attack;
}

Tower Tower::Upgrade(char* Name) {
	
}