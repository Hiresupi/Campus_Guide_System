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

	void ShowInfo(int &signal);

	void Floyd(MatGraph& g, vector<vector<int>>& A, vector<vector<int>>& path);

	vector<int> FindShort(MatGraph& g, int src, int dst);

	vector<int> Dispath(vector<vector<int>> A, vector<vector<int>> path, int n, int i, int j);

	bool Administrate();

	void DrawArrow();

	void drawbackground();

	void eventLoop();

	void placeSB(string s,int x,int y);

	void reminder();

	void readSights();

	int readRoutes();

	void showSightTable(Sights &s);

	void showTableSet(Sights &s,int Page);

	void searchFacility(MatGraph& g, int page, int id, vector<string>& svec, vector<int>& ivec);

private:

	MatGraph M;
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
	int flag1=-1;//景点图片标志

	//查看附近厕所/食堂:按钮、表格
	unique_ptr<PushButton> CafeBtn;
	unique_ptr<PushButton> ToiletBtn;
	unique_ptr<Table>CafeToiletTable;
	int Page = -1;//标识当前页面(信息查询) 一共有三层
	int isChangedFlag=-1;


	//查询线路
	unique_ptr<PushButton>ShortBtn;


	//管理员
	unique_ptr<PushButton>LoginBtn;//记得去初始化一下
	unique_ptr <LineEdit> LoginEdit;
	string passWord = "boys12138";
	int state=-1;
	vector<unique_ptr<PushButton>>subMenu_btns;


};