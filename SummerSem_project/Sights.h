#pragma once

#include <string>
#include <iostream>
#include <vector>

class Sights
{
public:
	int id = 0;   // 编号
	std::string name = "无";   // 名字
	int x = 0;   // x坐标
	int y = 0;   // y坐标  
	std::string star = "★"; // 推荐指数
	std::string info = "无";   // 信息
	bool canteen = 0;
	bool toilet = 0;


	// 构造函数
	Sights() = default;
	Sights(int id, const std::string name, int x,
		int y, const std::string star, const std::string address, 
		const std::string info, bool canteen, bool toilet) :
		id(id), name(name), x(x), y(y), star(star), info(info), canteen(canteen), toilet(toilet) {}

};

// 重载输入输出运算符
std::istream& operator>>(std::istream& is, Sights& item);
std::ostream& operator<<(std::ostream& os, const Sights& item);