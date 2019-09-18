#include "node.h"

bool node::operator<(const node& p) const
{
	const auto p1 = this->parent + this->current;
	const auto p2 = p.parent + p.current;
	return (p1 < p2);
}

node node::operator=(const node& t) const
{
	node node1;
	node1.parent = t.parent;
	node1.current = t.current;
	return node1;
}

bool node::operator==(const node& other) const
{
	return this->parent == other.parent && this->current == other.current;
}
