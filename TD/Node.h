#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include "VisibleGameObject.h"

class Node {
private :
	char _properties;
	//bool _isLoaded;
	//sf::Image _image;
	//sf::Sprite _sprite;
public :
	Node();
	Node(char c);
	~Node();
	void setProperties(char c);
	char getProperties();
	sf::Sprite& GetSprite();

	/*void Load();
	void Draw(sf::RenderWindow &renderWindow);*/
};