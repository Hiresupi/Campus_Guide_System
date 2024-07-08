#include "Sights.h"

using namespace std;

// 重载输入输出运算符
std::istream& operator>>(std::istream& is, Sights& item)
{
	is >> item.name >> item.x >> item.y
		>> item.id >> item.star >> item.info
		>> item.canteen >> item.toilet;
	if (!is)
	{
		item = Sights();
	}
    return is;
}

std::ostream& operator<<(std::ostream& os, const Sights& item)
{
	os << item.name << item.x << item.y
		<< item.id << item.star << item.info
		<< item.canteen << item.toilet;
    return os;
}
