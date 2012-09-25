#ifndef __FIELD__
#define __FIELD__

#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

class Field
{
	private :
		int width;
		int height;
		Node node[50][50];
		Node Start;
		Node Finish;
		sf::Image _image;
		sf::Sprite _sprite;
	public :
		Field();
		Field(int w, int h);
		~Field();
		void setWidth(int w);
		void setHeight(int h);
		int getWidth();
		int getHeight(); 
	
		void Load(string inputfile);
		void Draw(sf::RenderWindow & renderWindow);
};

#endif