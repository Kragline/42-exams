#include "bigint.hpp"

bigint::bigint() : _data("0") {}

bigint::bigint(unsigned int num)
{
	std::stringstream	ss;

	ss << num;
	_data = ss.str();
}

bigint::bigint(const bigint &other) : _data(other._data) {}

bigint::~bigint() {}

bigint	&bigint::operator=(const bigint &other)
{
	if (this != &other)
		_data = other._data;
	return (*this);
}

std::string bigint::getStr() const { return (_data); }

std::string bigint::_reverse(const std::string &str) const
{
	std::string	reversedStr;

	for (size_t i = str.size(); i > 0; i--)
		reversedStr.push_back(str[i - 1]);

	return (reversedStr);
}

std::string	bigint::_addition(const bigint& obj1, const bigint& obj2) const
{
	std::string	result;
	std::string	rev1 = _reverse(obj1._data);
	std::string	rev2 = _reverse(obj2._data);
	size_t		len1 = obj1._data.size();
	size_t		len2 = obj2._data.size();

	if (len1 > len2)
	{
		int	diff = len1 - len2;
		while (diff--)
			rev2.push_back('0');		
	}
	else if (len1 < len2)
	{
		int	diff = len2 - len1;
		while (diff--)
			rev1.push_back('0');		
	}

	int carry = 0;
	for (size_t i = 0; i < len1; i++)
	{
		int res = (rev1[i] - '0') + (rev2[i] - '0') + carry;

		if (res > 9)
		{
			carry = res / 10;
			result.push_back((res % 10) + '0');
		}
		else
			result.push_back(res + '0');
	}
	if (carry)
		result.push_back(carry);
	return (_reverse(result));
}

unsigned int	bigint::_strToUnsignedInt(const std::string &str) const
{
	std::stringstream ss(str);
	unsigned int n;

	ss >> n;
	return (n);
}

bigint	bigint::operator+(const bigint &other) const
{
	bigint	result;
	result._data = _addition(*this, other);

	return (result);
}

bigint	&bigint::operator+=(const bigint &other)
{
	(*this) = (*this) + other;
	return (*this);
}

bigint	&bigint::operator++()
{
	(*this) = (*this) + bigint(1);
	return (*this);
}

bigint	bigint::operator++(int)
{
	bigint	temp = (*this);

	(*this) = (*this) + bigint(1);
	return (temp);
}

bigint	bigint::operator<<(unsigned int num) const
{
	bigint	result = (*this);

	result._data.insert(result._data.end(), num, '0');
	return (result);
}

bigint	bigint::operator>>(unsigned int num) const
{
	bigint	result = (*this);

	if (num >= result._data.size())
		result._data = "0";
	else
		result._data.erase(result._data.size() - num, num);
	return (result);
}

bigint	&bigint::operator<<=(unsigned int num)
{
	(*this) = (*this) << num;
	return (*this);
}

bigint	&bigint::operator>>=(unsigned int num)
{
	(*this) = (*this) >> num;
	return (*this);
}

bigint	bigint::operator<<(const bigint &other) const
{
	return ((*this) << _strToUnsignedInt(other._data));
}

bigint	bigint::operator>>(const bigint &other) const
{
	return ((*this) >> _strToUnsignedInt(other._data));
}

bigint	&bigint::operator<<=(const bigint &other)
{
	(*this) = (*this) << other;
	return (*this);
}

bigint	&bigint::operator>>=(const bigint &other)
{
	(*this) = (*this) >> other;
	return (*this);
}

bool	bigint::operator==(const bigint &other) const
{
	return ((*this)._data == other._data);
}
bool	bigint::operator!=(const bigint &other) const
{
	return ((*this)._data != other._data);
}

bool	bigint::operator>(const bigint &other) const
{
	return ((*this)._data > other._data);
}

bool	bigint::operator<(const bigint &other) const
{
	return ((*this)._data < other._data);
}

bool	bigint::operator>=(const bigint &other) const
{
	return ((*this)._data >= other._data);
}

bool	bigint::operator<=(const bigint &other) const
{
	return ((*this)._data <= other._data);
}

std::ostream	&operator<<(std::ostream &out, const bigint &obj)
{
	out << obj.getStr();
	return (out);
}
