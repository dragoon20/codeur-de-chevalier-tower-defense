#ifndef __NODE__
#define __NODE__

class Node {
private :
	char _properties;
public :
	Node();
	Node(char c);
	~Node();
	void setProperties(char c);
	char getProperties();
	Node& Node::operator= (const Node&);
};

#endif