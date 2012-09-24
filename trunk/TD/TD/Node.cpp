#include "stdafx.h"
#include "Node.h"
using namespace std;
	Node::Node(){
		properties = 'O';
	}
	Node::Node(char c){
		properties = c;
	}
	Node::~Node(){
	}
	void Node::setProperties(char c){
		properties = c;
	}
	char Node::getProperties(){
		return properties;
	}

	void Node::Scale(float sx, float sy){
		GetSprite().SetScale(sx, sy);
	}