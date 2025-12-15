#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() {}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &other) : tree_bag(other) {}

searchable_tree_bag	&searchable_tree_bag::operator=(const searchable_tree_bag &other)
{
	if (this != &other)
		tree_bag::operator=(other);
	return (*this);
}

searchable_tree_bag::~searchable_tree_bag() {}

bool	searchable_tree_bag::_search(node *node, int value) const
{
	if (node == nullptr)
		return (false);
	if (node->value == value)
		return (true);
	else if (value < node->value)
		return (_search(node->l, value));
	return (_search(node->r, value));
}

bool searchable_tree_bag::has(int value) const
{
	return (_search(tree, value));
}
