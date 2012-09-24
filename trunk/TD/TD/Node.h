#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include "VisibleGameObject.h"

class Node : public VisibleGameObject {
private :
	char properties;
public :
	Node();
	Node(char c);
	~Node();
	void setProperties(char c);
	char getProperties();

	void Scale(float sx, float sy);
};