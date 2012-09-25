#include "stdafx.h"
#include "Node.h"
using namespace std;
	Node::Node(){
		_properties = 'O';
		_isLoaded = false;
	}
	Node::Node(char c){
		_properties = c;
		_isLoaded = false;
	}
	Node::~Node(){
	}
	void Node::setProperties(char c){
		_properties = c;
	}
	char Node::getProperties(){
		return _properties;
	}

	sf::Sprite& Node::GetSprite()
	{
		return _sprite;
	}
	/*void Node::Scale(float sx, float sy){
		GetSprite().SetScale(sx, sy);
	}*/

	void Node::Load(){
		switch (_properties){
			case 'O' :
				{
					if (_image.LoadFromFile("images/O.png")==true)
					{
						_sprite.SetImage(_image);
						_isLoaded = true;
					}
					break;
				}
			case 'X' :
				{
					if (_image.LoadFromFile("images/X.png")==true)
					{
						_sprite.SetImage(_image);
						_isLoaded = true;
					}
					break;
				}
			case 'S' :
				{
					if (_image.LoadFromFile("images/X.png")==true)
					{
						_sprite.SetImage(_image);
						_isLoaded = true;
					}
					break;
				}
			case 'F' :
				{
					if (_image.LoadFromFile("images/X.png")==true)
					{
						_sprite.SetImage(_image);
						_isLoaded = true;
					}
					break;
				}
			default :
				{break;}
		}
		/*	currentFrame = 0;
			currentPose = 0;
			elapseTime = 0;
			maxFrame = 0;
			frameChangeTime = 20;*/
	}
	void Node::Draw(sf::RenderWindow &renderWindow){
		if (_isLoaded){
			renderWindow.Draw(_sprite);
		}
	}