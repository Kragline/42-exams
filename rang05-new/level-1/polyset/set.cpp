#include "set.hpp"

set::set(searchable_bag &beg) : _bag(beg) {}

set::~set() {}

bool set::has(int value) const
{
	return (_bag.has(value));
}

void set::insert(int value)
{
	if (!has(value))
		_bag.insert(value);
}

void set::insert(int *data, int size)
{
	for (int i = 0; i < size; i++)
		insert(data[i]);
}

void set::print() const
{
	_bag.print();
}

void set::clear()
{
	_bag.clear();
}

const searchable_bag& set::get_bag()
{
	return (_bag);
}
