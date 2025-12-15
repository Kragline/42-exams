#pragma once

#include <iostream>
#include <sstream>

class bigint
{
private:
	std::string	_data;
public:
	bigint();
	bigint(unsigned int num);
	bigint(const bigint &other);

	bigint	&operator=(const bigint &other);

	std::string getStr() const ;

	bigint	operator+(const bigint &other) const ;
	bigint	&operator+=(const bigint &other);

	bigint	&operator++();
	bigint	operator++(int);

	bigint	operator<<(unsigned int num) const ;
	bigint	operator>>(unsigned int num) const ;
	bigint	&operator<<=(unsigned int num);
	bigint	&operator>>=(unsigned int num);

	bigint	operator<<(const bigint &other) const ;
	bigint	operator>>(const bigint &other) const ;
	bigint	&operator<<=(const bigint &other);
	bigint	&operator>>=(const bigint &other);

	bool	operator==(const bigint &other) const ;
	bool	operator!=(const bigint &other) const ;
	bool	operator>(const bigint &other) const ;
	bool	operator<(const bigint &other) const ;
	bool	operator>=(const bigint &other) const ;
	bool	operator<=(const bigint &other) const ;

	~bigint();
private:
	std::string		_addition(const bigint& obj1, const bigint& obj2) const ;
	std::string 	_reverse(const std::string &str) const ;
	unsigned int	_strToUnsignedInt(const std::string &str) const ;
};

std::ostream	&operator<<(std::ostream &out, const bigint &obj);
