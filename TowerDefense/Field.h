//#include "stdafx.h"
#include <fstream>
#include <iostream>
//#include "SFML/Graphics.hpp"
#include "Node.h"
//#include "VisibleGameObject.h"
using namespace std;

class Field
{
	private :
		int width;
		int height;
		Node node[50][50];
	public :
		Field();
		Field(int w, int h);
		~Field();
		void setWidth(int w);
		void setHeight(int h);
		int getWidth();
		int getHeight();
		Node getNode(int i, int j);
		Node& getNode2(int i, int j); 
		int * getPath();
		
		//void Load(string inputfile);
		//void Draw(sf::RenderWindow & renderWindow);
};