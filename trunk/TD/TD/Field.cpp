#include "stdafx.h"
#include "Field.h"
#include <queue>
#include <algorithm>

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
vector<int> Field::getPath()
{
	queue<pair<Point,vector<int>>> q;
	vector<int> p,r;
	p.push_back(1);
	q.push(make_pair(Start,p));
	
	bool cek = true;
	bool mat [50][50];

	for (int i=0;i<50;++i)
	{
		for (int j=0;j<50;++j)
		{
			mat[i][j] = true;
		}
	}

	mat[Start.y][Start.x] = false;

	while((cek)&&(!q.empty()))
	{
		pair<Point,vector<int>> temp;
		temp = q.front();

		r = temp.second;

		if ((temp.first.x == Finish.x)&&(temp.first.y == Finish.y))
		{
			p = r;
			cek = false;
		}
		else
		{
			int x = temp.first.x;
			int y = temp.first.y;
			Point Po;

			if ((x+1<width)&&(mat[y][x+1])&&((node[y][x+1].getProperties()=='O')||(node[y][x+1].getProperties()=='F')))
			{
				Po.x = x+1;
				Po.y = y;
				r.push_back(1);
				q.push(make_pair(Po,r));
				r.pop_back();
				mat[y][x+1] = false;
			}
			if ((x-1>=0)&&(mat[y][x-1])&&((node[y][x-1].getProperties()=='O')||(node[y][x-1].getProperties()=='F')))
			{
				Po.x = x-1;
				Po.y = y;
				r.push_back(3);
				q.push(make_pair(Po,r));
				r.pop_back();
				mat[y][x-1] = false;
			}
			if ((y+1<height)&&(mat[y+1][x])&&((node[y+1][x].getProperties()=='O')||(node[y+1][x].getProperties()=='F')))
			{
				Po.x = x;
				Po.y = y+1;
				r.push_back(2);
				q.push(make_pair(Po,r));
				r.pop_back();
				mat[y+1][x] = false;
			}
			if ((y-1>=0)&&(mat[y-1][x])&&((node[y-1][x].getProperties()=='O')||(node[y-1][x].getProperties()=='F')))
			{
				Po.x = x;
				Po.y = y-1;
				r.push_back(0);
				q.push(make_pair(Po,r));
				r.pop_back();
				mat[y-1][x] = false;
			}
		}
		q.pop();
	}

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
						Start.x = j;
						Start.y = i;
						break;
					}
					case 'F' :
					{
						Finish.x = j;
						Finish.y = i;
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
		width = j;
		height = i;
		myfile.close();
	
		_image.LoadFromFile("images/terrain.png");
		_sprite.SetImage(_image);
	}

  else 
	  cout << "Unable to open file"; 
}

void Field::Draw(sf::RenderWindow & renderWindow){
	for (int i=0; i<height; i++){
		for (int j=0; j<width; j++){
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
					_sprite.SetSubRect(sf::IntRect(0, 0, 64, 64));
					_sprite.SetPosition(j*64, i*64);
					renderWindow.Draw(_sprite);
					break;
				}
				case 'F' :
				{
					_sprite.SetSubRect(sf::IntRect(0, 0, 64, 64));
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