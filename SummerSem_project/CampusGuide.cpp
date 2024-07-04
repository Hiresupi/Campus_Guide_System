#include"CampusGuide.h"


CampusGuide::CampusGuide()
{

	//����
	LOGFONT f;
	gettextstyle(&f);
	f.lfQuality = ANTIALIASED_QUALITY;//���ֿ����
	settextstyle(&f);
	::settextstyle(20, 0, "����", 0, 0, 100, 0, 0, 0); //settextstyle(120, 60, "����", 0, 0, 880, 0, 1, 0);
	::loadimage(&m_bk, "assets/WHU3.JPEG", Window::width(), Window::height());

	//�����水ť��ʼ��
	menu_btns.emplace_back(new PushButton("У԰ȫòһ��"));
	menu_btns.emplace_back(new PushButton("�����ѯ"));
	menu_btns.emplace_back(new PushButton("·�߲�ѯ"));
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
	placeSB("��У�򳵵�1", 20, 180);//0   ����е㣨x+52��y+10��
	placeSB("�����ѧԺ", 68, 275);//1
	placeSB("׿��������", 88, 335);//2
	placeSB("�人��ѧ�Ʒ�", 90, 560);//3
	placeSB("���С", 165, 60);//4
	placeSB("��԰�ٳ�",230 , 300);//5
	placeSB("��ͼ���", 265, 425);//6
	placeSB("���ֲ����", 330, 370);//7
	placeSB("ӣ���Ǳ�", 320, 175);//8
	placeSB("ӣ�����", 410, 240);//9
	placeSB("ˮ���о���", 370,80);//10
	placeSB("������", 390,595);//11
	placeSB("��һ���ٳ�", 460, 320);//12
	placeSB("��ѧ��", 550, 60);//13
	placeSB("����ɽ", 560, 470);//14
	placeSB("÷԰", 580, 590);//15
	placeSB("��ѧԺ", 680, 310);//16
	placeSB("����", 830, 80);//17
	placeSB("��԰", 800, 340);//18
	placeSB("��У�򳵵�2", 850, 540);//19 ��20��sights


}




void CampusGuide::run()
{
		//��ȡ�˵��ķ���ֵ
		int op = MENU;
		int choice = 666;
		//const int add = 1;
		//const int amend = 2;

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
						op = MENU;
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
					::loadimage(&m_bk, "assets/WHU3.JPEG", Window::width(), Window::height());
				}
				break;
			case CampusGuide::SHOW:
				ShowPic();
				break;
			case CampusGuide::SEARCH:
				ShowMap();
				break;
			case CampusGuide::FIND:
				ShowMap();
				break;
			case CampusGuide::EXIT:
				//saveFile("assets/flights");
				//saveFile02("assets/customers");
				//fstream fout("assets/sights.txt", ios::out);
				//for (int i = 0; i < sight_btns.size(); i++)
				//{
				//	fout << sight_btns[i]->m_text << " " << sight_btns[i]->x() << " " << sight_btns[i]->y() <<" "<<i<< endl;
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






void CampusGuide::ShowPic()
{
	reminder();
	if (flag != 3)
	{
		::loadimage(&m_bk, "assets/overview.JPEG", Window::width(), Window::height());
		flag = 3;
	}
}

void CampusGuide::drawbackground()
{
	::putimage(0, 0, &m_bk);
}


void CampusGuide::eventLoop()
{
	for (int i = 0; i < sight_btns.size(); i++)
	{
		sight_btns[i]->event();
	}
	//����event()����
}


void CampusGuide::placeSB(string s, int x, int y)//�����㰴ť
{
	PushButton* p = new PushButton(s);
	sight_btns.emplace_back(p);
	p->setFixedSize(104, 23);
	p->move(x, y);
}

void CampusGuide::reminder()
{
	settextcolor(RGB(255, 120, 0));
	settextstyle(30, 0, "΢���ź�", 0, 0, 880, 0, 0, 0);
	outtextxy(0, 0, "��Esc��������һ��...");
}
