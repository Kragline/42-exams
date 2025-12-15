#pragma once

#include "searchable_bag.hpp"

class set
{
private:
	searchable_bag	&_bag;
public:
	set() = delete;
	set(searchable_bag &bag);
	set(const set &other) = delete ;

	set	&operator=(const set &other) = delete ;

	bool has(int) const ;
	void insert(int);
	void insert(int *, int);
	void print() const;
	void clear();

	const searchable_bag& get_bag();

	~set();
};


