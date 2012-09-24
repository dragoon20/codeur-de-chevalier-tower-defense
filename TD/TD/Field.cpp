#include "stdafx.h"
#include "Field.h"

	Field::Field(){
		width = 50;
		height = 50;
		for (int i=0; i<width; i++){
			for (int j=0; j<height; j++){
				node[i][j].setProperties('X'); 
			}
		}
	}
	Field::Field(int w, int h){
		width = w;
		height = h;
		for (int i=0; i<width; i++){
			for (int j=0; j<height; j++){
				node[i][j].setProperties('O'); 
			}
		}
	}
	Field::~Field(){
	}
	void Field::setWidth(int w){
		width = w;
	}
	void Field::setHeight(int h){
		height = h;
	}
	int Field::getWidth(){
		return width;
	}
	int Field::getHeight(){
		return height;
	}
	Node Field::getNode(int i, int j){
		return node[i][j];
	}

	Node& Field::getNode2(int i, int j){
		return node[i][j];
	}

	void Field::Load(string inputfile){
		string line[50];
		int i, j;
		cout << "Generating map . . ." << endl;
		ifstream myfile (inputfile);
		if (myfile.is_open())
		{
			i = 0;
			while ( myfile.good() )
			{
				getline (myfile,line[i]);
				j = 0;
				while ( j < line[i].length() ) {
					node[i][j].setProperties(line[i][j]);
					cout << node[i][j].getProperties();
					j++;
				}
				cout<<endl;
				i++;
			}
		width = i;
		height = j;
		myfile.close();
	  
		for (int i=0; i<width; i++){
			for (int j=0; j<height; j++){
				switch (node[i][j].getProperties()){
					case 'X' :
						{
						node[i][j].Load("images/X.png");
						break;}
					case 'O' :
						{
						node[i][j].Load("images/O.png"); 
						break;}
				}
				node[i][j].Scale(2.0f, 2.0f);
				node[i][j].SetPosition(j*64, i*64);
			}
		}
	 }

	  else 
		  cout << "Unable to open file"; 
	}

	void Field::Draw(sf::RenderWindow & renderWindow){
		for (int i=0; i<width; i++){
			for (int j=0; j<height; j++){
				switch (node[i][j].getProperties()){
					case 'X' :
						{node[i][j].Draw(renderWindow); break;}
					case 'O' :
						{node[i][j].Draw(renderWindow); break;}
				}
			}
		}
	}