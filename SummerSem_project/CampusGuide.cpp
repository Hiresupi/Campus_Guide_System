#include"CampusGuide.h"


CampusGuide::CampusGuide()
{
	readSights();
	int routeCnt=readRoutes();
	M.createMatGraph(RWeight, SightList.size(), routeCnt, SightList);
	//����
	LOGFONT f;
	gettextstyle(&f);
	f.lfQuality = ANTIALIASED_QUALITY;//���ֿ����
	settextstyle(&f);
	::settextstyle(20, 0, "����", 0, 0, 100, 0, 0, 0); //settextstyle(120, 60, "����", 0, 0, 880, 0, 1, 0);
	::loadimage(&m_bk, "assets/WHU.JPEG", Window::width(), Window::height());

	//�����水ť��ʼ��
	menu_btns.emplace_back(new PushButton("���ž����ٲ�"));
	menu_btns.emplace_back(new PushButton("��ѯ���ž���"));
	menu_btns.emplace_back(new PushButton("��ѯ����·��"));
	menu_btns.emplace_back(new PushButton("����Ա���"));
	menu_btns.emplace_back(new PushButton("�˳�"));
	//menu_btns.emplace_back(new PushButton("��Ʊ"));
	//menu_btns.emplace_back(new PushButton("��Ʊ��Ϣ�޸�"));
	//menu_btns.emplace_back(new PushButton("�˳�ϵͳ"));
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->setFixedSize(250, 45);
		int bx = (Window::width() - menu_btns[i]->width()) / 2;
		int by = 240 + i * (menu_btns[i]->height() + 20);
		//�ƶ����м�
		menu_btns[i]->move(bx, by);
	}

	//���㰴ť��ʼ��
	//placeSB("��У�򳵵�1", 20, 180);//0   �������õı���е�����Ϊ��x+SBheight/2��y+SBwidth/2��
	//placeSB("�����ѧԺ", 68, 275);//1
	//placeSB("׿��������", 88, 335);//2
	//placeSB("�人��ѧ�Ʒ�", 90, 560);//3
	//placeSB("���С", 165, 60);//4
	//placeSB("��԰�ٳ�",230 , 300);//5
	//placeSB("��ͼ���", 265, 425);//6
	//placeSB("���ֲ����", 330, 370);//7
	//placeSB("ӣ���Ǳ�", 320, 175);//8
	//placeSB("ӣ�����", 410, 240);//9
	//placeSB("ˮ���о���", 370,80);//10
	//placeSB("������", 390,595);//11
	//placeSB("��һ���ٳ�", 460, 320);//12
	//placeSB("��ѧ��", 550, 60);//13
	//placeSB("����ɽ", 560, 470);//14
	//placeSB("÷԰", 580, 590);//15
	//placeSB("��ѧԺ", 680, 310);//16
	//placeSB("����", 830, 80);//17
	//placeSB("��԰", 800, 340);//18
	//placeSB("��У�򳵵�2", 850, 540);//19 ��20��sights
	for (int i = 0; i < SightList.size(); i++)
	{
		placeSB(SightList[i].name, SightList[i].x, SightList[i].y);
	}


	//��ѯ������ʼ��
	SightSearchBtn.reset(new PushButton("����", 700, 30));
	SightEdit.reset(new LineEdit(100, 30, 570, 45));
	SightEdit->setTitle("�����뾰��ȫ�ƣ��磺�人��ѧ�Ʒ���");
	SightEdit->setPrompt("�人��ѧ�Ʒ�");

	//������Ϣ�鿴��ʼ��


	ToiletBtn.reset(new PushButton("�����в�������", 435, 450));
	CafeBtn.reset(new PushButton("�����в�������", 710,450));
	CafeToiletTable.reset(new Table);

	//��ѯ·�߲�����ʼ��
	ShortBtn.reset(new PushButton("��ʾ��̾���·��"));
	ShortBtn->move(755, 3);

	//����Ա��ڳ�ʼ��
	LoginBtn.reset(new PushButton("����", 700, 170));
	LoginEdit.reset(new LineEdit(100, 170, 570, 45));
	LoginEdit->setTitle("��������Կ");

	subMenu_btns.emplace_back(new PushButton("�����¾��㼰·��"));
	subMenu_btns.emplace_back(new PushButton("ɾ������"));

	for (int i = 0; i < subMenu_btns.size(); i++)
	{
		subMenu_btns[i]->setFixedSize(250, 45);
		int bx = (Window::width() - subMenu_btns[i]->width()) / 2;
		int by = 240 + i * (subMenu_btns[i]->height() + 30);
		//�ƶ����м�
		subMenu_btns[i]->move(bx, by);
	}

	addSightEdit.reset(new LineEdit(100, 200, 570, 45));
	addSightBtn.reset(new PushButton("���", 700, 200));
	addSightEdit->setTitle("�밴�ո�ʽ���룡");

	//��·���벿��
	weightEdit.reset(new LineEdit(700,3,150,30));
	weightEdit->setTitle("��������루Ĭ�ϵ�λ��m��");
	confirmBtn.reset(new PushButton("ȷ��",855,3,100,30));

}




void CampusGuide::run()
{

		//��ȡ�˵��ķ���ֵ
		int op = MENU;
		int choice = 666;
		//const int add = 1;
		//const int amend = 2;
		bool saySorry = false;
		bool saySorry2 = false;
		int signal=-1;//����������ź�

		int start=-1, end=-1;//���ղ�·��ʱ����ʼ�ͽ�β

		int routeBuild = -1;//����Ա��·��ҳ��ת����ʶ
		bool alreadyAdd = false;//�Ѿ�����һ��·����

		vector<int>distV;//������·��id



		while (true)
		{
			//cout << "123" << endl;
			Window::clear();
			Window::beginDraw();
			drawbackground();

			if (Window::hasMsg())
			{
				switch (Window::getMsg().message)
				{
				case WM_KEYDOWN:
					//ESC�˳����� ����������
					if (Window::getMsg().vkcode == VK_ESCAPE)
					{
						if (start!=-1&&end!=-1)
						{
							for (int i = 0; i < distV.size(); i++)
								sight_btns[distV[i]]->backNorm();
							sight_btns[end]->backNorm();
							end = -1;
							curCondition = -1;
						}
						else if (start != -1 && end == -1)
						{
							sight_btns[start]->backNorm();
							start = -1;
						}
						else
						if (Page != -1)
						{
							Page = -1;
						}
						else if (signal != -1)
						{
							signal = -1;
						}//��Ϣ��ѯ�����ӽ���

						else if (operationPage!=-1)
						{
							if (operationPage == 2)//ѡ���¾���λ��
							{
								operationPage = 0;
								::loadimage(&m_bk, "assets/WHU.JPEG", Window::width(), Window::height());
								flag = 1;
							}
							else if (operationPage == 3)//���·��
							{
								
								if (routeAdded!=0||alreadyAdd)//��·������,��ζ�ųɹ������һ������
								{
									//sight_btns[routeBuild]->backNorm();
									//routeBuild = -1;
									if (routeBuild!=-1)//������ˣ���Ҫ���˵� ��������·��
									{
										sight_btns[routeBuild]->backNorm();
										routeBuild = -1;
										operationPage = 3;
										if (routeAdded != 0)
										{
											updateMatGraph(routeAdded);//����route
											routeAdded = 0;
										}
										//sight_btns[SightList.size() - 1]->backNorm();
									}
									else//û�б��������ôֱ���˵�ǰ��
									{
										if (routeAdded != 0)
										{
											updateMatGraph(routeAdded);//����route
											routeAdded = 0;
										}
										operationPage = 0;
										alreadyAdd = false;
										sight_btns[SightList.size() - 1]->backNorm();
										addSightEdit->setText("");
										::loadimage(&m_bk, "assets/WHU.JPEG", Window::width(), Window::height());//�����л�
										flag = 1;
										//SightList.pop_back();
										//sight_btns.pop_back();
										//operationPage = 2;
									}
									weightEdit->setText("");
								}
								else//û��·������
								{
									if (routeBuild!=-1)//�е��
									{
										sight_btns[routeBuild]->backNorm();
										operationPage = 3;
										routeBuild = -1;

									}
									else //û�м�·��
									{
										SightList.pop_back();
										sight_btns.pop_back();
										operationPage = 2;
									}

								}
								//if (twiceBack)
								//{
								//	operationPage = -1;
								//	addSightEdit->setText("");
								//	sight_btns[SightList.size() - 1]->backNorm();
								//	twiceBack = false;
								//	weightEdit->setText("");
								//}
							
								//operationPage = 2;

							}
							else if (operationPage == 1 || operationPage == 0)
							{
								operationPage = -1;
								addSightEdit->setText("");
							}

							
						}
						else if (state==1)
						{
							state = 0;
						}
						else if (state == 0)
						{
						    op = MENU;
							state = -1;
						}
						else op = MENU;

						LoginEdit->setText("");
						SightEdit->setText("");//��֧��һ������
					}
					break;
				default://������
					eventLoop();//ѭ�����¸���������״̬
					break;
				}
			}

			switch (op)
			{

			case CampusGuide::MENU:
				op = menu();
				if (flag!=1)
				{
					flag = 1;
					::loadimage(&m_bk, "assets/WHU.JPEG", Window::width(), Window::height());
				}
				break;
			case CampusGuide::SHOW:
				ShowPic();
				saySorry=searchNshow();
				break;
			case CampusGuide::SEARCH:
				ShowInfo(signal);
				break;
			case CampusGuide::FIND:
				drawLine(start,end,distV);
				ShowMap();
				break;

			case CampusGuide::MODIFY:
				saySorry2=Administrate(routeBuild,alreadyAdd);
				break;

			case CampusGuide::EXIT:
				//saveFile("assets/flights");
				//saveFile02("assets/customers");
				//fstream fout("assets/sights.txt", ios::out);
				//for (int i = 0; i < sight_btns.size(); i++)
				//{
				//	fout << sight_btns[i]->m_text <<"	" << sight_btns[i]->x() << "	" << sight_btns[i]->y() << "	" << i << endl;
				//}
				Window::beginDraw();
				settextcolor(RGB(255, 120, 0));
				settextstyle(80, 40, "Bulter");
				outtextxy(200, 150, "SEE YOU AGAIN!");
				Window::flushDraw();
				Sleep(2000);
				exit(0);
				break;
			}
			Window::flushDraw();
			if (saySorry)
			{
				Sleep(2000);
				saySorry = false;
			}//�ٲ鹦�ܱ�Ǹ
			if (saySorry2)
			{
				Sleep(2000);
				saySorry2 = false;
			}//����Ա���뱧Ǹ

			Window::getMsg().message = 0;
		}

	
}

int CampusGuide::menu()
{
	//������
	settextcolor(RGB(255, 120, 0));
	settextstyle(120, 60, "����", 0, 0, 880, 0, 1, 0);
	char str[] = "���У԰һ��ͨ";
	int tx = (Window::width() - textwidth(str)) / 2;
	int ty = 40;
	outtextxy(tx, ty, str);
	::settextstyle(20, 0, "����", 0, 0, 100, 0, 0, 0);
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->show();
		menu_btns[i]->event();
		if (menu_btns[i]->isClicked())
		{
			return i;
		}
	}
	//���ݲ˵��ĵ�� ���ز���
	return MENU;
}

int CampusGuide::ShowMap()
{
	reminder();
	if (flag != 2)
	{
		::loadimage(&m_bk, "assets/map1.JPEG", Window::width(), Window::height());
		flag = 2;
	}
	//::settextstyle(20, 0, "����", 0, 0, 100, 0, 0, 0);
	for (int i = 0; i < sight_btns.size(); i++)
	{
		sight_btns[i]->show2();
		sight_btns[i]->event();
		if (sight_btns[i]->isClicked())
		{
			//sight_btns[i]->isChosen();
			return i;
		}
	}
	return -1;

}

void CampusGuide::ShowInfo(int &signal)
{
	if (signal == -1)signal = ShowMap();
	else
	{
		reminder();
		if (flag != 3)
		{
			::loadimage(&m_bk, "assets/����3.JPG", Window::width(), Window::height());
			::loadimage(&LOGO, "assets/LOGO.PNG", 200, 63);

			flag = 3;
		}
		string file = "assets/pics/Pic";
		file += to_string(signal) + ".JPG";
		if (flag1 != signal)
		{
			::loadimage(&sightPic, file.c_str(), 370, 270);
			flag1 = signal;
		}
		putimage(380, 570, &LOGO);//��logo

		if (CafeBtn->isClicked())
		{
			Page = 1;


		}
		else if (ToiletBtn->isClicked())
		{
			Page = 2;
		}

		if (Page != -1)
		{
			//CafeToiletTable.reset(new Table);
			if (isChangedFlag != Page)
			{
				showTableSet(SightList[signal], Page);
				isChangedFlag = Page;
			}
			CafeToiletTable->show();
		}
		else 
		{
			isChangedFlag = Page;
			putimage(8, 128, 400, 300, &sightPic, 0, 0);//�ž���ͼƬ

			showSightTable(SightList[signal]);
		}
	}
}

void CampusGuide::Floyd(MatGraph& g, vector<vector<int>>& A, vector<vector<int>>& path)
{
	for (int i = 0; i < g.n; i++)
	{
		for (int j = 0; j < g.n; j++)
		{
			A[i][j] = g.edges[i][j];
			if (i != j && g.edges[i][j] < INF)
			{
				path[i][j] = i;
			}
			else
			{
				path[i][j] = -1;
			}
		}
	}
	for (int k = 0; k < g.n; k++)
	{
		for (int i = 0; i < g.n; i++)
		{
			for (int j = 0; j < g.n; j++)
			{
				if (A[i][j] > A[i][k] + A[k][j])
				{
					A[i][j] = A[i][k] + A[k][j];
					path[i][j] = path[k][j];
				}
			}
		}
	}
}


// ��ʾ������Ϣ
void CampusGuide::showSightTable(Sights& s)
{
	SightTable.reset(new Table);
	SightTable->setRowCount(4);
	string header = "��������	";
	header += s.name;
	SightTable->setHeader02(header);
	string line1 = "���	"; line1 += s.info;
	string line2 = "�Ƽ�ָ��	"; line2 += s.star;
	string line3 = "���޲���	";
	string line4 = "���޲���	";
	if (s.canteen) line3 += "��";
	else line3 += "��";
	if (s.toilet) line4 += "��";
	else line4 += "��";

	SightTable->insertData(line1);
	SightTable->insertData(line2);
	SightTable->insertData(line3);
	SightTable->insertData(line4);

	SightTable->move(SightTable->tempX, SightTable->tempY);//���λ��

	SightTable->show();

	CafeBtn->show();
	ToiletBtn->show();

}

void CampusGuide::searchFacility(MatGraph& g, int page, int id, vector<string>& svec, vector<int>& ivec)
{
	vector<vector<int>> A(MAXV, vector<int>(MAXV, INF));
	vector<vector<int>> path(MAXV, vector<int>(MAXV, INF));
	Floyd(g, A, path);
	if (page == 2)//����
	{
		for (int i = 0; i < g.n; i++)
		{
			if (g.vexs[i].toilet == 1)
			{
				svec.push_back(g.vexs[i].name);
				ivec.push_back(A[id][i]);
			}
		}
	}
	else if(page==1)//����
	{
		for (int i = 0; i < g.n; i++)
		{
			if (g.vexs[i].canteen == 1)
			{
				svec.push_back(g.vexs[i].name);
				ivec.push_back(A[id][i]);
			}
		}
	}
	for (int i = 0; i < ivec.size() - 1; i++)
	{
		for (int j = ivec.size() - 1; j > 0; j--)
		{
			if (ivec[j] < ivec[j - 1])
			{
				int tmp = ivec[j];
				string stmp = svec[j];
				ivec[j] = ivec[j - 1];
				ivec[j - 1] = tmp;
				svec[j] = svec[j - 1];
				svec[j - 1] = stmp;
			}
		}
	}
	return;
}

void CampusGuide::showTableSet(Sights& s, int Page)
{
	//page��ʶ�ǲ���ҳ�滹�ǲ���ҳ��
	CafeToiletTable.reset(new Table);
	CafeToiletTable->setRowCount(5);
	string header = "������	�����ڵ���̾���";
	CafeToiletTable->setHeader(header);
	//����������insertһ�£�Ȼ��Ϳ���show��
	vector<string>nameV; vector<int>distV;
	//updateMatGraph(2);
	searchFacility(M, Page, s.id, nameV, distV);
	string str;
	for (int i = 0; i < nameV.size(); i++)
	{
		str = nameV[i] + "	" + to_string(distV[i]);
		CafeToiletTable->insertData(str);
	}
	CafeToiletTable->move(CafeToiletTable->middlePut, 150);
	//CafeToiletTable->show();
	//CafeToiletTable->event();

}

// ����Floyd�㷨�����·�������غ���id��·��vector
int CampusGuide::FindShort(MatGraph& g, int src, int dst, vector<int>& distVec)
{
	vector<vector<int>> A(MAXV, vector<int>(MAXV, INF));
	vector<vector<int>> path(MAXV, vector<int>(MAXV, INF));
	Floyd(g, A, path);
	distVec = Dispath(A, path, g.n, src, dst);
	return A[src][dst];
}

// Ѱ��i��j�����·��
vector<int> CampusGuide::Dispath(vector<vector<int>> A, vector<vector<int>> path, int n, int i, int j)
{
	if (A[i][j] != INF && i != j)
	{
		vector <int> apath;
		apath.push_back(j);
		int pre = path[i][j];
		while (pre != i)
		{
			apath.push_back(pre);
			pre = path[i][pre];
		}
		apath.push_back(i);
		reverse(apath.begin(), apath.end());
		return apath;
	}
}

void CampusGuide::ShowAllRoute()
{
	setlinestyle(PS_DASHDOT,3);
	setlinecolor(RGB(50, 19, 176));
	//�е�����Ϊ��y+SBheight/2��x+SBwidth/2��
	for(int i=0;i<SightList.size();i++)
		for(int j=0;j<i;j++)
			if (RWeight[i][j] != INF && RWeight[i][j] != 0)
			{
				//������
				int beginX = SightList[i].x + SBwidth / 2;
				int beginY= SightList[i].y + SBheight/ 2;
				int endX = SightList[j].x + SBwidth/ 2;
				int endY = SightList[j].y + SBheight/ 2;
				line(beginX, beginY, endX, endY);
			}



}

//int CampusGuide::NavigateStartHint()
//{
//	settextcolor(RGB(147, 94, 230));
//	settextstyle(40, 0, "΢���ź�", 0, 0, 880, 0, 0, 0);
//	outtextxy(720, 0, "��ѡ���������");
//	for (int i = 0; i < sight_btns.size(); i++)
//		if (sight_btns[i]->isClicked()) return i;
//	return -1;
//}
//
//int CampusGuide::NavigateEndHint()
//{
//	settextcolor(RGB(147, 94, 230));
//	settextstyle(40, 0, "΢���ź�", 0, 0, 880, 0, 0, 0);
//	outtextxy(720, 0, "��ѡ��Ŀ�꾰��");
//	for (int i = 0; i < sight_btns.size(); i++)
//		if (sight_btns[i]->isClicked()) return i;
//
//	return -1;
//}

int CampusGuide::NavigateHint(string s)
{
	settextcolor(RGB(147, 94, 230));
	settextstyle(40, 0, "΢���ź�", 0, 0, 880, 0, 0, 0);
	outtextxy(750, 0,s.c_str());
	for (int i = 0; i < sight_btns.size(); i++)
		if (sight_btns[i]->isClicked()) return i;

	return -1;
}

void CampusGuide::drawLine(int &start, int &end, vector<int>&distV)
{
	if (start == -1)
	{
		ShowAllRoute();
		//ShowMap();
		start = NavigateHint();
	}
	else if ((start != -1 && end == -1)||start==end)
	{
	
		end = NavigateHint("��ѡ��Ŀ�꾰��");
		ShowAllRoute();
		sight_btns[start]->isChosen();
		//ShowMap();
	}
	else
	{
		sight_btns[start]->isChosen();
		sight_btns[end]->isChosen();
		//ShowMap();
		ShortBtn->show();
		if (ShortBtn->isClicked())
		{
			curCondition = 1;

		}
		if (curCondition == 1)
		{
			int dist = FindShort(M, start, end, distV);
			string str = "ȫ�̹�" + to_string(dist) + "m";
			settextcolor(RGB(147, 94, 230));
			outtextxy(820, 610, str.c_str());
			for (int i = 0; i < distV.size()-1; i++)
			{
				if (i > 0) sight_btns[distV[i]]->isChosen();
				setlinestyle(PS_SOLID, 6);
				setlinecolor(RGB(50, 19, 176));
				int beginX = SightList[distV[i]].x + SBwidth / 2;
				int beginY = SightList[distV[i]].y + SBheight / 2;
				int endX = SightList[distV[i+1]].x + SBwidth / 2;
				int endY = SightList[distV[i+1]].y + SBheight / 2;
				line(beginX, beginY, endX, endY);
			}



			//ShowMap();
		}
		else
		{
			ShowAllRoute();

		}
		//ShowMap();

	}

}




bool CampusGuide::Administrate(int& routeBuild,bool& alreadyAdd)
{


	if (state == -1)state = 0;
	reminder();
	if (state == 0)
	{
		string str1("���������Ա������");
		settextcolor(RGB(255, 120, 0));
		settextstyle(56, 28, "Bulter");
		//settextstyle(40, 0, "����", 0, 0, 800, 0, 0, 0);
		outtextxy((Window::width() - textwidth(str1.c_str())) / 2,100, str1.c_str());
		LoginBtn->show();
		LoginEdit->show();
	}
	else if (state == 1)//������ɾ�Ľ�����
	{
		if (operationPage == -1)
		{
			for (int i = 0; i < subMenu_btns.size(); i++)
				subMenu_btns[i]->show();
			for (int i = 0; i < subMenu_btns.size(); i++)
				if (subMenu_btns[i]->isClicked()) operationPage = i;
		}
		switch (operationPage)
		{
		case 0://ѡ�����
		{
			string str1 = "�밴<������ ��� �Ƽ�ֵ(��) ��/�޲��� ��/�޲���>��ʽ���������Ϣ";
			string str2 = "ps���м�ո��������ֻ����ȷ�����ʽ���ܳɹ����";
			outtextxy((Window::width() - textwidth(str1.c_str()))/2, 120, str1.c_str());
			outtextxy((Window::width() - textwidth(str2.c_str()))/2, 160, str2.c_str());
			addSightBtn->show();
			addSightEdit->show();
			if (addSightEdit->isValid(5) && addSightBtn->isClicked())
			{
				operationPage = 2;
			}
			break;
		}

		case 1://ɾ������

			break;
		case 2://ѡ��λ��
		{
			int x, y;//����
			ShowMap();
			string note("�뵥��ѡ�����������λ��");
			settextcolor(RGB(147, 94, 230));
			//settextstyle(50, 25, "����");
			settextstyle(30, 0, "΢���ź�", 0, 0, 880, 0, 0, 0);
			outtextxy(690, 0, note.c_str());
			auto& m_msg = Window::getMsg();
			if (m_msg.message == WM_LBUTTONDOWN)//�������
			{
				x = m_msg.x-SBwidth/2; y = m_msg.y-SBheight/2;
				addSights(addSightEdit->text(), x, y);
				placeSB(SightList[SightList.size() - 1].name, SightList[SightList.size() - 1].x, SightList[SightList.size() - 1].y);
				sight_btns[sight_btns.size() - 1]->isChosen();
				operationPage = 3;
			}

			break;
		}

		case 3://��·
		{
			
			if(routeBuild==-1)
			routeBuild=ShowMap();

			if (routeBuild != -1)
			{
				sight_btns[routeBuild]->isChosen();
				string note2 = "�������·�߾��룺";
				settextstyle(30, 0, "΢���ź�", 0, 0, 880, 0, 0, 0);
				settextcolor(RGB(255, 120, 0));
				outtextxy(510, 0, note2.c_str());
				weightEdit->show();
				confirmBtn->show();
				setlinestyle(PS_DASHDOT, 3);
				setlinecolor(RGB(50, 19, 176));
				//�е�����Ϊ��y+SBheight/2��x+SBwidth/2��
				//������
				int a = SightList.size()-1;
				int beginX = SightList[a].x + SBwidth / 2;
				int beginY = SightList[a].y + SBheight / 2;
				int endX = SightList[routeBuild].x + SBwidth / 2;
				int endY = SightList[routeBuild].y + SBheight / 2;
				line(beginX, beginY, endX, endY);
				ShowMap();
				if (weightEdit->text() != "" && confirmBtn->isClicked())//����Ȩֵ�����
				{
					addRoutes(a, routeBuild, weightEdit->text());
					routeAdded++;
					weightEdit->setText("");
					sight_btns[routeBuild]->backNorm();
					routeBuild = -1;
				}
			}
			else
			{
				if (routeAdded == 0&&!alreadyAdd)//û��·����ӳɹ�
				{

					string note2 = "��ӳɹ������������������·��";
					settextstyle(30, 0, "΢���ź�", 0, 0, 880, 0, 0, 0);
					settextcolor(RGB(147, 94, 230));
					outtextxy(630, 0, note2.c_str());
				}
				else
				{
					alreadyAdd = true;
					string note2 = "·����ӳɹ����ɵ�����������������";
					settextstyle(30, 0, "΢���ź�", 0, 0, 880, 0, 0, 0);
					settextcolor(RGB(147, 94, 230));
					outtextxy(550,0, note2.c_str());
				}

			}
			break;

		}


		}
	}

		if (passWord == LoginEdit->text() && LoginBtn->isClicked())
		{
			state = 1;
		}
		else if (LoginBtn->isClicked() && LoginEdit->text() != "" && passWord != LoginEdit->text())
		{
			string str1("����������������������!");
			settextcolor(RGB(221, 255, 148));
			settextstyle(50, 25, "Bulter");
			//settextstyle(40, 0, "����", 0, 0, 800, 0, 0, 0);
			outtextxy((Window::width() - textwidth(str1.c_str())) / 2,
				(Window::height() - textheight(str1.c_str())) / 2, str1.c_str());
			return true;//��Ǹ��ʾ
		}


		return false;
	
}

void CampusGuide::addRoutes(int src, int dst, string w)
{
	int weight = stoi(w);
	RWeight[src][dst] = weight;
	RWeight[dst][src] = weight;
}




void CampusGuide::ShowPic()
{
	reminder();
	if (flag != 3)
	{
		::loadimage(&m_bk, "assets/WHU1.JPEG", Window::width(), Window::height());
		flag = 3;
	}
}

bool CampusGuide::searchNshow()
{
	SightSearchBtn->show();
	SightEdit->show();
	string str = SightEdit->text();
	if(SightSearchBtn->isClicked()&&!str.empty())
	if (str == "ӣ���Ǳ�"||str=="ӣ��")
	{
		::loadimage(&m_bk, "assets/pics/Pic8.JPG", Window::width(), Window::height());
	}
	else if(str == "ӣ�����")
	{
		::loadimage(&m_bk, "assets/pics/Pic9.JPG", Window::width(), Window::height());
	}
	else if (str == "��ͼ���"||str=="ͼ���")
	{
		::loadimage(&m_bk, "assets/pics/Pic6.JPG", Window::width(), Window::height());
	}
	else if (str == "�����ѧԺ")
	{
		::loadimage(&m_bk, "assets/pics/Pic1.JPG", Window::width(), Window::height());
	}
	else if (str == "���ֲ����")
	{
		::loadimage(&m_bk, "assets/pics/Pic2.JPG", Window::width(), Window::height());
	}
	else if (str == "�人��ѧ�Ʒ�")
	{
		::loadimage(&m_bk, "assets/pics/Pic3.JPG", Window::width(), Window::height());
	}
	else if (str == "��һ���ٳ�"||str=="912�ٳ�")
	{
		::loadimage(&m_bk, "assets/pics/Pic12.JPG", Window::width(), Window::height());
	}
	else if (str == "����")
	{
		::loadimage(&m_bk, "assets/pics/Pic17.JPG", Window::width(), Window::height());
	}
	else if (str == "׿��������")
	{
		::loadimage(&m_bk, "assets/pics/Pic2.JPG", Window::width(), Window::height());
	}
	else if(str!="")
	{
		string str1("��Ǹ�����������ǰ���޸þ�����Ϣ!");
		settextcolor(RGB(221,255,148));
		//settextstyle(60, 30, "Bulter");
		settextstyle(40, 0, "����", 0, 0, 800, 0, 0, 0);
		outtextxy((Window::width() - textwidth(str1.c_str()))/2,
			(Window::height()-textheight(str1.c_str()))/2, str1.c_str());
		return true;
	}
	return false;
}

void CampusGuide::drawbackground()
{
	::putimage(0, 0, &m_bk);
}


void CampusGuide::eventLoop()
{
	//���ø���������event����
	for (int i = 0; i < sight_btns.size(); i++)
	{
		sight_btns[i]->event();
	}
	SightSearchBtn->event();
	SightEdit->event();

	CafeBtn->event();
	ToiletBtn->event();
	//CafeTable->event();
	//ToiletTable->event();


	//ShortBtn->event();
	//AllBtn->event();

	LoginBtn->event();
	LoginEdit->event();
	for (int i = 0; i < subMenu_btns.size(); i++)
		subMenu_btns[i]->event();

	//if (CafeToiletTable != NULL)
	CafeToiletTable->event();

	ShortBtn->event();

	addSightBtn->event();
	addSightEdit->event();

	weightEdit->event();
	confirmBtn->event();
}

void CampusGuide::updateMatGraph(int cnt)
{
	M.edges = RWeight;
	M.vexs = SightList;
	M.n++;
	M.e += cnt;
}


void CampusGuide::placeSB(string s, int x, int y)//�����㰴ť
{
	PushButton* p = new PushButton(s);
	sight_btns.emplace_back(p);
	p->setFixedSize(SBwidth, SBheight);
	p->move(x, y);
}

void CampusGuide::reminder()
{
	settextcolor(RGB(255, 120, 0));
	settextstyle(30, 0, "΢���ź�", 0, 0, 880, 0, 0, 0);
	outtextxy(0, 0, "��Esc��������һ��...");
}

// ���ļ��ж�ȡ������Ϣ
void CampusGuide::readSights()
{
	ifstream fin("assets/sights.txt");
	Sights item;

	while (fin >> item)
	{
		SightList.push_back(item);
	}
	
}

// ���ļ��ж�ȡ·����Ϣ
int CampusGuide::readRoutes()
{
	ifstream fin("assets/routes.txt");
	RWeight = vector<vector<int>>(MAXV, vector<int>(MAXV, INF));
	int i, j;
	int length;
	for (int i = 0; i < MAXV; i++)
	{
		RWeight[i][i] = 0;
	}
	int cnt = 0;
	while (fin >> i >> j >> length)
	{
		cnt++;
		RWeight[i][j] = length;
		RWeight[j][i] = length;
	}
	return cnt;
}

void CampusGuide::addSights(string sightStr,int x,int y)
{
	Sights stmp;
	istringstream strin(sightStr);
	strin >> stmp.name >> stmp.info >> stmp.star;
	string toilet, canteen;
	strin >> toilet >> canteen;
	stmp.toilet = (toilet == "��") ? 1 : 0;
	stmp.canteen = (canteen == "��") ? 1 : 0;
	stmp.x = x;
	stmp.y = y;
	stmp.id = SightList.size();
	SightList.push_back(stmp);
}

void CampusGuide::saveToFile()
{
	ofstream fout("assets/sights.txt");
	for (auto sight : SightList)
	{
		fout << sight << endl;
	}
	fout.open("assets/routes.txt");
	for (int i = 0; i < RWeight.size(); i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (RWeight[i][j] != INF)
			{
				fout << j << "	" << i << "	" << RWeight[i][j] << endl;
			}
		}
	}
}


