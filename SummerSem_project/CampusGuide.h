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

	//�鿴��������/ʳ��:��ť�����
	unique_ptr<PushButton> CafeBtn;
	unique_ptr<PushButton> ToiletBtn;
	unique_ptr<Table>CafeTable;
	unique_ptr<Table>ToiletTable;


	//��ѯ��·
	unique_ptr<PushButton>ShortBtn;


	//����Ա
	unique_ptr<PushButton>LoginBtn;//�ǵ�ȥ��ʼ��һ��
	unique_ptr <LineEdit> LoginEdit;
	string passWord = "boys12138";


};