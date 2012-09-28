#include "stdafx.h"
#include "Field.h"

Field::Field(){
	width = 50;
	height = 50;
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			node[i][j].setProperties('O'); 
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
void Field::setNode(int y, int x, char c)
{
	node[y][x].setProperties(c);
}
int Field::getWidth(){
	return width;
}
int Field::getHeight(){
	return height;
}
char Field::getNode(int y, int x)
{
	return node[y][x].getProperties();
}
Path Field::getPath()
{
	Path p;
	return p;
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
				switch (line[i][j]){
					case 'S' :
					{
						Start.x = i;
						Start.y = j;
						break;
					}
					case 'F' :
					{
						Finish.x = i;
						Finish.y = j;
						break;
					}
					default :
					{
						break;
					}

				}
				j++;
			}
			cout<<endl;
			i++;
		}
	width = i;
	height = j;
	myfile.close();
	
	_image.LoadFromFile("images/terrain.png");
	_sprite.SetImage(_image);
}

  else 
	  cout << "Unable to open file"; 
}

void Field::Draw(sf::RenderWindow & renderWindow){
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			switch (node[i][j].getProperties()){
				case 'X' :
				{
					_sprite.SetSubRect(sf::IntRect(0, 0, 64, 64));
					_sprite.SetPosition(j*64, i*64);
					renderWindow.Draw(_sprite);
					break;
				}
				case 'O' :
				{
					_sprite.SetSubRect(sf::IntRect(64, 0, 128, 64));
					_sprite.SetPosition(j*64, i*64);
					renderWindow.Draw(_sprite);
					break;
				}
				case 'S' :
				{
					_sprite.SetSubRect(sf::IntRect(64, 0, 128, 64));
					_sprite.SetPosition(j*64, i*64);
					renderWindow.Draw(_sprite);
					break;
				}
				case 'F' :
				{
					_sprite.SetSubRect(sf::IntRect(64, 0, 128, 64));
					_sprite.SetPosition(j*64, i*64);
					renderWindow.Draw(_sprite);
					break;
				}
				default :{break;}
			}
		}
	}
}

void Field::searchPath(int, int, int, int*) {
}