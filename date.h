#ifndef DATE_H
#define DATE_H
#include <iostream>
using namespace std;
class Date
{
private:
	int y, m, d, h, min;
public:
	Date(int y = 1970, int m = 1, int d = 1, int h = 0, int min = 0)
	{
		this->y = y;
		this->m = m;
		this->d = d;
		this->h = h;
		this->min = min;
	}
	Date(const Date& da)
	{
		y = da.y;
		m = da.m;
		d = da.d;
		h = da.h;
		min = da.min;
	}
	friend ostream& operator<<(ostream& os, const Date& da)
	{
		os << da.y << ' ' << da.m << ' ' << da.d << "   " << da.h << ' ' << da.min;
		return os;
	}
	friend istream& operator>>(istream& is, Date& da)
	{
		is >> da.y >> da.m >> da.d >> da.h >> da.min;
		return is;
	}
};
#endif // !DATE_H