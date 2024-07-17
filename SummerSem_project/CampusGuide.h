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

	//�˵���
	int menu();

	// *
	void run();

	void placeSB(string s, int x, int y);

	void ShowPic();

	// ���ž����ٲ�
	bool searchNshow();

	// չʾ��ͼ
	int ShowMap();

	// չʾ������Ϣ���
	void showSightTable(Sights& s);

	// չʾ��ʩ�б�
	void showTableSet(Sights& s, int Page);

	// ������ʩ�㷨
	void searchFacility(MatGraph& g, int page, int id, vector<string>& svec, vector<int>& ivec);

	// չʾ������Ϣ
	void ShowInfo(int &signal);


	// *Floyd�㷨
	void Floyd(MatGraph& g, vector<vector<int>>& A, vector<vector<int>>& path);

	// ���·����ѯ
	int FindShort(MatGraph& g, int src, int dst, vector<int>& distVec);

	// ����·��
	vector<int> Dispath(vector<vector<int>> A, vector<vector<int>> path, int n, int i, int j);

	// չʾ����·��
	void ShowAllRoute();

	// ������ʾ
	int  NavigateHint(string s="��ѡ���������");

	// �����·��
	void drawLine(int &start, int &end, vector<int>& distV);

	// ����Ա���
	bool Administrate(int & routeBuild,bool & alreadyAdd,int &sightDeleted,bool &alreadyDelete);

	void drawbackground();

	// ����״̬ѭ��
	void eventLoop();

	// ����ͼ״̬
	void updateMatGraph(int eCnt, int nCnt);

	void reminder();

	// ��ȡ����
	void readSights();

	// ��ȡ·��
	int readRoutes();

	// ���Ӿ���
	void addSights(string sightStr,int x,int y);

	// ����·��
	void addRoutes(int src, int dst, string w);

	// ɾ������
	void deteleSights(int id);

	// �����ݱ��浽�ļ�
	void saveToFile();

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
	int SBheight = 23; int SBwidth = 104;

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
	int curCondition=-1;


	//����Ա
	unique_ptr<PushButton>LoginBtn;//�ǵ�ȥ��ʼ��һ��
	unique_ptr <LineEdit> LoginEdit;
	string passWord = "katyperry143";
	int state=-1;
	vector<unique_ptr<PushButton>>subMenu_btns;
	int operationPage = -1;//��ʶ��ͬ������ҳ��
	unique_ptr <LineEdit> addSightEdit;
	unique_ptr<PushButton>addSightBtn;
	int routeAdded = 0;//�����û�м�·��
	unique_ptr <LineEdit> weightEdit;
	unique_ptr<PushButton>confirmBtn;

	unique_ptr<PushButton>deleteBtn;


};