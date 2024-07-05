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

	void ShowPic();

	bool searchNshow();

	int ShowMap();

	void Showinfo(Sights&s);

	void FindAllRoute();

	void FindShort();

	void DrawArrow();



	void drawbackground();

	void eventLoop();

	void placeSB(string s,int x,int y);

	void reminder();

private:
	IMAGE m_bk;
	int flag = 0;//标识背景图片状态，减少加载背景次数，更流畅
	vector<unique_ptr<PushButton>>menu_btns;
	vector<unique_ptr<PushButton>>sight_btns;
	int SBheight = 104; int SBwidth = 23;

	//景点概览
	unique_ptr<PushButton>SightSearchBtn;
	unique_ptr <LineEdit> SightEdit;

	//查看附近厕所/食堂:按钮、表格
	unique_ptr<PushButton> CafeBtn;
	unique_ptr<PushButton> ToiletBtn;
	unique_ptr<Table>CafeTable;
	unique_ptr<Table>ToiletTable;


	//查询线路
	unique_ptr<PushButton>ShortBtn;
	unique_ptr<PushButton>AllBtn;





};