#pragma once
#include"Window.h"
#include"PushButton.h"
#include<fstream>
#include"Table.h"
#include"LineEdit.h"
#include"Sights.h"
#include<vector>
using namespace std;

class CampusGuide
{
public:

	enum Operator
	{
		SHOW,
		SEARCH,
		FIND,
		EXIT,
		MENU = 666
	};


	CampusGuide();

	//菜单项
	int menu();
	void run();

	int ShowMap();

	void Showinfo(Sights&s);

	void FindAllRoute();

	void FindShort();

	void DrawArrow();


	void drawbackground();

	void eventLoop();

	void placeSB(string s,int x,int y);

private:
	IMAGE m_bk;
	int flag = 0;//标识背景图片状态，减少加载背景次数，更流畅
	vector<unique_ptr<PushButton>>menu_btns;
	vector<unique_ptr<PushButton>>sight_btns;






};