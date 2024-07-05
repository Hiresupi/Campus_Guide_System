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

	//�˵���
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
	int flag = 0;//��ʶ����ͼƬ״̬�����ټ��ر���������������
	vector<unique_ptr<PushButton>>menu_btns;
	vector<unique_ptr<PushButton>>sight_btns;
	int SBheight = 104; int SBwidth = 23;

	//�������
	unique_ptr<PushButton>SightSearchBtn;
	unique_ptr <LineEdit> SightEdit;

	//�鿴��������/ʳ��:��ť�����
	unique_ptr<PushButton> CafeBtn;
	unique_ptr<PushButton> ToiletBtn;
	unique_ptr<Table>CafeTable;
	unique_ptr<Table>ToiletTable;


	//��ѯ��·
	unique_ptr<PushButton>ShortBtn;
	unique_ptr<PushButton>AllBtn;





};