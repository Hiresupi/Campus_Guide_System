#pragma once

#include "Window.h"
#include "PushButton.h"
#include <fstream>
#include <algorithm>
#include "Table.h"
#include "LineEdit.h"
#include "MatGraph.h"
#include <sstream>
#include <vector>
#include <filesystem>


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

	// *
	CampusGuide();

	//菜单项
	int menu();

	// *
	void run();

	void placeSB(string s, int x, int y);

	void ShowPic();

	// 热门景点速查
	bool searchNshow();

	// 展示地图
	int ShowMap();

	// 展示景点信息表格
	void showSightTable(Sights& s);

	// 展示设施列表
	void showTableSet(Sights& s, int Page);

	// 搜索设施算法
	void searchFacility(MatGraph& g, int page, int id, vector<string>& svec, vector<int>& ivec);

	// 展示景点信息
	void ShowInfo(int &signal);


	// *Floyd算法
	void Floyd(MatGraph& g, vector<vector<int>>& A, vector<vector<int>>& path);

	// 最短路径查询
	int FindShort(MatGraph& g, int src, int dst, vector<int>& distVec);

	// 生成路径
	vector<int> Dispath(vector<vector<int>> A, vector<vector<int>> path, int n, int i, int j);

	// 展示所有路径
	void ShowAllRoute();

	// 操作提示
	int  NavigateHint(string s="请选择出发景点");

	// 画最短路线
	void drawLine(int &start, int &end, vector<int>& distV);

	// 管理员入口
	bool Administrate(int & routeBuild,bool & alreadyAdd,int &sightDeleted,bool &alreadyDelete);

	void drawbackground();

	// 部件状态循环
	void eventLoop();

	// 更新图状态
	void updateMatGraph(int eCnt, int nCnt);

	void reminder();

	// 读取景点
	void readSights();

	// 读取路线
	int readRoutes();

	// 增加景点
	void addSights(string sightStr,int x,int y);

	// 增加路线
	void addRoutes(int src, int dst, string w);

	// 删除景点
	void deteleSights(int id);

	// 将数据保存到文件
	void saveToFile();

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
	int SBheight = 23; int SBwidth = 104;

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
	int curCondition=-1;


	//管理员
	unique_ptr<PushButton>LoginBtn;//记得去初始化一下
	unique_ptr <LineEdit> LoginEdit;
	string passWord = "katyperry143";
	int state=-1;
	vector<unique_ptr<PushButton>>subMenu_btns;
	int operationPage = -1;//标识不同操作的页面
	unique_ptr <LineEdit> addSightEdit;
	unique_ptr<PushButton>addSightBtn;
	int routeAdded = 0;//标记有没有加路径
	unique_ptr <LineEdit> weightEdit;
	unique_ptr<PushButton>confirmBtn;

	unique_ptr<PushButton>deleteBtn;


};