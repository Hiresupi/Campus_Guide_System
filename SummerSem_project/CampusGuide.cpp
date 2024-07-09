#include"CampusGuide.h"


CampusGuide::CampusGuide()
{
	readSights();
	readRoutes();

	//����
	LOGFONT f;
	gettextstyle(&f);
	f.lfQuality = ANTIALIASED_QUALITY;//���ֿ����
	settextstyle(&f);
	::settextstyle(20, 0, "����", 0, 0, 100, 0, 0, 0); //settextstyle(120, 60, "����", 0, 0, 880, 0, 1, 0);
	::loadimage(&m_bk, "assets/WHU3.JPEG", Window::width(), Window::height());

	//�����水ť��ʼ��
	menu_btns.emplace_back(new PushButton("���ž����ٲ�"));
	menu_btns.emplace_back(new PushButton("�����ѯ"));
	menu_btns.emplace_back(new PushButton("·�߲�ѯ"));
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


	ToiletBtn.reset(new PushButton("��������", 435, 450));
	CafeBtn.reset(new PushButton("��������", 710,450));


	//����Ա��ڳ�ʼ��
	LoginBtn.reset(new PushButton("����", 700, 170));
	LoginEdit.reset(new LineEdit(100, 170, 570, 45));
	LoginEdit->setTitle("��������Կ");

	subMenu_btns.emplace_back(new PushButton("�����¾���"));
	subMenu_btns.emplace_back(new PushButton("������·��"));
	subMenu_btns.emplace_back(new PushButton("ɾ������"));
	subMenu_btns.emplace_back(new PushButton("ɾ��·��"));

	for (int i = 0; i < subMenu_btns.size(); i++)
	{
		subMenu_btns[i]->setFixedSize(250, 45);
		int bx = (Window::width() - subMenu_btns[i]->width()) / 2;
		int by = 240 + i * (subMenu_btns[i]->height() + 20);
		//�ƶ����м�
		subMenu_btns[i]->move(bx, by);
	}


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
						if (Page != -1)
						{
							Page = -1;
						}
						else if (signal != -1)
						{
							signal = -1;
						}//��Ϣ��ѯ�����ӽ���
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
				ShowMap();
				break;
			case CampusGuide::MODIFY:
				saySorry2=Administrate();
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

		if (Page == 1)
		{
			CafeToiletTable.reset(new Table);
		}
		else if (Page == 2)
		{

		}
		else
		{
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
	vector<vector<int>> A;
	vector<vector<int>> path;
	Floyd(g, A, path);
	if (page == 1)
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
	else
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

void CampusGuide::showTable(Sights& s, int Page)
{
	CafeToiletTable.reset(new Table);
	CafeToiletTable->setRowCount(5);
	string header = "������	�����ڵ���̾���";
	CafeToiletTable->setHeader(header);
	//����������insertһ�£�Ȼ��Ϳ���show��


}

// ����Floyd�㷨�����·�������غ���id��·��vector
vector<int> CampusGuide::FindShort(MatGraph& g, int src, int dst)
{
	vector<vector<int>> A(MAXV, vector<int>(MAXV, INF));
	vector<vector<int>> path(MAXV, vector<int>(MAXV, INF));
	Floyd(g, A, path);
	vector<int> routeVec = Dispath(A, path, g.n, src, dst);
	return routeVec;
}

// Ѱ��i��j�����·��
vector<int> CampusGuide::Dispath(vector<vector<int>> A, vector<vector<int>> path, int n, int i, int j)
{
	if (A[i][j] != INF && i != j)
	{
		vector <int> apath;
		cout << "length of the shortest route is" << A[i][j];
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


bool CampusGuide::Administrate()
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
	else if (state==1)
	{
		for (int i = 0; i < subMenu_btns.size(); i++)
			subMenu_btns[i]->show();
	}

	if (passWord == LoginEdit->text()&&LoginBtn->isClicked())
	{
		state = 1;	
	}
	else if (LoginBtn->isClicked()&&LoginEdit->text() != "" && passWord != LoginEdit->text())
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

void CampusGuide::DrawArrow()
{
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

}


void CampusGuide::placeSB(string s, int x, int y)//�����㰴ť
{
	PushButton* p = new PushButton(s);
	sight_btns.emplace_back(p);
	p->setFixedSize(SBheight, SBwidth);
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
void CampusGuide::readRoutes()
{
	ifstream fin("assets/routes.txt");
	RWeight = vector<vector<int>>(MAXV, vector<int>(MAXV, INF));
	int i, j;
	int length;
	for (int i = 0; i < MAXV; i++)
	{
		RWeight[i][i] = 0;
	}
	while (fin >> i >> j >> length)
	{
		RWeight[i][j] = length;
		RWeight[j][i] = length;
	}
}


