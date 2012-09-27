#ifndef __FIELD__
#define __FIELD__

#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

typedef struct
{
	int *path;
	int pathsize;
} Path;

typedef struct
{
	int x;
	int y;
} Point;

class Field
{
	private :
		int width;
		int height;
		Node node[50][50];
		Point Start;
		Point Finish;

		int start_x; 
		int start_y;
		int finish_x;
		int finish_y;

		sf::Image _image;
		sf::Sprite _sprite;
	public :
		Field();
		Field(int w, int h);
		~Field();
		void setWidth(int w);
		void setHeight(int h);
		void setNode(int x, int y, char c);
		int getWidth();
		int getHeight(); 
		char getNode(int x, int y);
		Path getPath();
		
		void getPath(int, int, int, int*);
		void Load(string inputfile);
		void Draw(sf::RenderWindow & renderWindow);

		void findStartNode();
		void findFinishNode();
};

#endif