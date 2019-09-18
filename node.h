#ifndef NODE_H
#define NODE_H
#include<string>

using namespace std;

class node final
{
public:
	string parent;
	string current;

	bool operator<(const node & p) const;
	node operator=(const node & t) const;
	bool operator==(const node & other) const;
};
#endif

