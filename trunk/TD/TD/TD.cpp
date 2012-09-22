// TD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
/*#include "Field.h"
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>*/
using namespace std;


int main()
{
	Game::Start();
		
	
		/*ofstream myfile ("example.txt");
	  if (myfile.is_open())
	  {
		myfile << "This is a line.\n";
		myfile << "This is another line.\n";
		myfile.close();
	  }
	  else cout << "Unable to open file";*/
	  
	  /*Field field;
	    
	  string line[50];
	  int i, j;
	  ifstream myfile ("example.txt");
	  if (myfile.is_open())
	  {
		i = 0;
		while ( myfile.good() )
		{
			getline (myfile,line[i]);
			j = 0;
			while ( j < line[i].length() ) {
				field.getNode2(i,j).setProperties(line[i][j]);
				cout << field.getNode2(i,j).getProperties();
				j++;
			}
			cout<<endl;
			i++;
		}
		field.setWidth(i);
		field.setHeight(j);
		myfile.close();
	  }

	  else cout << "Unable to open file"; 
	  getchar();*/
	return 0;
}

