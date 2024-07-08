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


	ToiletBtn.reset(new PushButton("��������", 360, 480));
	CafeBtn.reset(new PushButton("��������", 610,480));


	//����Ա��ڳ�ʼ��
	LoginBtn.reset(new PushButton("����", 700, 170));
	LoginEdit.reset(new LineEdit(100, 170, 570, 45));
	LoginEdit->setTitle("��������Կ");


}




void CampusGuide::run()
{

		//��ȡ�˵��ķ���ֵ
		int op = MENU;
		int choice = 666;
		//const int add = 1;
		//const int amend = 2;
		bool saySorry = false;
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
						if (signal != -1)
						{
							signal = -1;
						}
						else op = MENU;

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
				if (signal == -1)signal = ShowMap();
				else
				{
					if (flag != 3)
					{
						::loadimage(&m_bk, "assets/����3.JPG", Window::width(), Window::height());
						flag = 3;
					}
					string file = "assets/pics1/Pic";
					file += to_string(signal)+".JPG";
					::loadimage(&sightPic, file.c_str(), 370, 270);
					putimage(12, 122,400,300,  &sightPic,0,0);
					showSightTable(SightList[signal]);

					::loadimage(&LOGO, "assets/LOGO.PNG",200,63);
					putimage(380, 570, &LOGO);
				}

				break;
			case CampusGuide::FIND:
				ShowMap();
				break;
			case CampusGuide::MODIFY:
				Administrate();
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
			}
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

// ����Floyd�㷨�����·�������غ���id��·��vector
vector<int> CampusGuide::FindShort(MatGraph& g, int src, int dst)
{
	vector<vector<int>> A(MAXV, vector<int>(MAXV, INF));
	vector<vector<int>> path(MAXV, vector<int>(MAXV, INF));
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
	LoginBtn->show();
	LoginEdit->show();
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
		::loadimage(&m_bk, "assets/pics/ӣ���Ǳ�.JPG", Window::width(), Window::height());
	}
	else if(str == "ӣ�����")
	{
		::loadimage(&m_bk, "assets/pics/ӣ�����.JPG", Window::width(), Window::height());
	}
	else if (str == "��ͼ���"||str=="ͼ���")
	{
		::loadimage(&m_bk, "assets/pics/��ͼ���.JPG", Window::width(), Window::height());
	}
	else if (str == "�����ѧԺ")
	{
		::loadimage(&m_bk, "assets/pics/�����ѧԺ.JPG", Window::width(), Window::height());
	}
	else if (str == "���ֲ����")
	{
		::loadimage(&m_bk, "assets/pics/���ֲ����.JPG", Window::width(), Window::height());
	}
	else if (str == "�人��ѧ�Ʒ�")
	{
		::loadimage(&m_bk, "assets/pics/�Ʒ�.JPG", Window::width(), Window::height());
	}
	else if (str == "��һ���ٳ�"||str=="912�ٳ�")
	{
		::loadimage(&m_bk, "assets/pics/912.JPG", Window::width(), Window::height());
	}
	else if (str == "����")
	{
		::loadimage(&m_bk, "assets/pics/����.JPG", Window::width(), Window::height());
	}
	else if (str == "׿��������")
	{
		::loadimage(&m_bk, "assets/pics/׿��������.JPG", Window::width(), Window::height());
	}
	else if(str!="")
	{
		string str1("��Ǹ�����������ǰ���޸þ�����Ϣ!");
		settextcolor(RGB(221,255,148));
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


