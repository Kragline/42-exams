#pragma once

#include <iostream>

class vect2
{
private:
	int	_x;
	int	_y;
public:
	vect2();
	vect2(int x, int y);
	vect2(const vect2 &other);

	vect2 &operator=(const vect2 &other);

	int	&operator[](int index);
	int	operator[](int index) const ;
	
	vect2	operator+(const vect2 &other) const ;
	vect2	operator-(const vect2 &other) const ;
	vect2	operator-() const ;

	vect2	&operator+=(const vect2 &other);
	vect2	&operator-=(const vect2 &other);

	vect2	operator*(int num) const ;
	vect2	&operator*=(int num);

	vect2	&operator++();
	vect2	operator++(int);
	vect2	&operator--();
	vect2	operator--(int);

	bool	operator==(const vect2 &other) const ;
	bool	operator!=(const vect2 &other) const ;

	~vect2();
};

std::ostream	&operator<<(std::ostream &out, const vect2 &obj);
vect2			operator*(int num, const vect2 &obj);
