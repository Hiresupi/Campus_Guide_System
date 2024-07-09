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

	//�˵���
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
	int flag = 0;//��ʶ����ͼƬ״̬�����ټ��ر���������������
	// 1��������
	// 2�Ƿ�֧һ�ı���
	//3�Ƿ�֧���ı���
	vector<unique_ptr<PushButton>>menu_btns;
	vector<unique_ptr<PushButton>>sight_btns;
	int SBheight = 104; int SBwidth = 23;

	//�������
	unique_ptr<PushButton>SightSearchBtn;
	unique_ptr <LineEdit> SightEdit;

	//������Ϣ
	IMAGE sightPic;
	IMAGE LOGO;
	unique_ptr<Table>SightTable;
	int flag1=-1;//����ͼƬ��־

	//�鿴��������/ʳ��:��ť�����
	unique_ptr<PushButton> CafeBtn;
	unique_ptr<PushButton> ToiletBtn;
	unique_ptr<Table>CafeToiletTable;
	int Page = -1;//��ʶ��ǰҳ��(��Ϣ��ѯ) һ��������
	int isChangedFlag=-1;


	//��ѯ��·
	unique_ptr<PushButton>ShortBtn;


	//����Ա
	unique_ptr<PushButton>LoginBtn;//�ǵ�ȥ��ʼ��һ��
	unique_ptr <LineEdit> LoginEdit;
	string passWord = "boys12138";
	int state=-1;
	vector<unique_ptr<PushButton>>subMenu_btns;


};