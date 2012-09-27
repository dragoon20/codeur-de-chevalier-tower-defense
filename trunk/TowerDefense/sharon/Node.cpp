#include "stdafx.h"
#include "Node.h"

	Node::Node(){
		_properties = 'O';
	}
	Node::Node(char c){
		_properties = c;
	}
	Node::~Node(){
	}
	void Node::setProperties(char c){
		_properties = c;
	}
	char Node::getProperties(){
		return _properties;
	}

	Node& Node::operator= (const Node& N) {
		_properties = N._properties;
		Node(_properties);
		return *this;
	}
