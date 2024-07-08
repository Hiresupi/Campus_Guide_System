#pragma once

#include <string>
#include <iostream>
#include <vector>

class Sights
{
public:
	int id = 0;   // ���
	std::string name = "";   // ����
	int x = 0;   // x����
	int y = 0;   // y����  
	std::string star = ""; // �Ƽ�ָ��
	std::string info = "";   // ��Ϣ
	bool canteen = 0;
	bool toilet = 0;


	// ���캯��
	Sights() = default;
	Sights(int id, const std::string name, int x,
		int y, const std::string star, const std::string address, 
		const std::string info, bool canteen, bool toilet) :
		id(id), name(name), x(x), y(y), star(star), info(info), canteen(canteen), toilet(toilet) {}

};

// ����������������
std::istream& operator>>(std::istream& is, Sights& item);
std::ostream& operator<<(std::ostream& os, const Sights& item);