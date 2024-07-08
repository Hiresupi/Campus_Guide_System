#pragma once

#include "Window.h"
#include "PushButton.h"
#include <fstream>
#include <algorithm>
#include "Table.h"
#include "LineEdit.h"
#include "MatGraph.h"
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
		MODIFY,
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

	void ShowInfo(Sights& s);

	vector<int> FindShort(MatGraph& g, int src, int dst);

	vector<int> Dispath(vector<vector<int>> A, vector<vector<int>> path, int n, int i, int j);

	bool Administrate();

	void DrawArrow();

	void drawbackground();

	void eventLoop();

	void placeSB(string s,int x,int y);

	void reminder();

	void readSights();

	void readRoutes();

	void showSightTable(Sights &s);

private:

	vector<Sights> SightList;
	vector<vector<int>> RWeight;

	IMAGE m_bk;
	int flag = 0;//标识背景图片状态，减少加载背景次数，更流畅
	// 1是主背景
	// 2是分支一的背景
	//3是分支二的背景
	vector<unique_ptr<PushButton>>menu_btns;
	vector<unique_ptr<PushButton>>sight_btns;
	int SBheight = 104; int SBwidth = 23;

	//景点概览
	unique_ptr<PushButton>SightSearchBtn;
	unique_ptr <LineEdit> SightEdit;

	//景点信息
	IMAGE sightPic;
	IMAGE LOGO;
	unique_ptr<Table>SightTable;

	//查看附近厕所/食堂:按钮、表格
	unique_ptr<PushButton> CafeBtn;
	unique_ptr<PushButton> ToiletBtn;
	unique_ptr<Table>CafeTable;
	unique_ptr<Table>ToiletTable;


	//查询线路
	unique_ptr<PushButton>ShortBtn;


	//管理员
	unique_ptr<PushButton>LoginBtn;//记得去初始化一下
	unique_ptr <LineEdit> LoginEdit;
	string passWord = "boys12138";


};