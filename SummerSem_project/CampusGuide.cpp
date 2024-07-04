#include"CampusGuide.h"


CampusGuide::CampusGuide()
{

	//构造
	LOGFONT f;
	gettextstyle(&f);
	f.lfQuality = ANTIALIASED_QUALITY;//文字抗锯齿
	settextstyle(&f);
	::settextstyle(20, 0, "楷体", 0, 0, 100, 0, 0, 0); //settextstyle(120, 60, "黑体", 0, 0, 880, 0, 1, 0);
	::loadimage(&m_bk, "assets/WHU3.JPEG", Window::width(), Window::height());

	//主界面按钮初始化
	menu_btns.emplace_back(new PushButton("校园全貌一览"));
	menu_btns.emplace_back(new PushButton("景点查询"));
	menu_btns.emplace_back(new PushButton("路线查询"));
	menu_btns.emplace_back(new PushButton("退出"));
	//menu_btns.emplace_back(new PushButton("退票"));
	//menu_btns.emplace_back(new PushButton("订票信息修改"));
	//menu_btns.emplace_back(new PushButton("退出系统"));
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->setFixedSize(250, 45);
		int bx = (Window::width() - menu_btns[i]->width()) / 2;
		int by = 240 + i * (menu_btns[i]->height() + 20);
		//移动到中间
		menu_btns[i]->move(bx, by);
	}

	//景点按钮初始化
	placeSB("离校打车点1", 20, 180);//0   标记中点（x+52，y+10）
	placeSB("计算机学院", 68, 275);//1
	placeSB("卓尔体育馆", 88, 335);//2
	placeSB("武汉大学牌坊", 90, 560);//3
	placeSB("武大附小", 165, 60);//4
	placeSB("桂园操场",230 , 300);//5
	placeSB("总图书馆", 265, 425);//6
	placeSB("万林博物馆", 330, 370);//7
	placeSB("樱花城堡", 320, 175);//8
	placeSB("樱花大道", 410, 240);//9
	placeSB("水生研究所", 370,80);//10
	placeSB("居民区", 390,595);//11
	placeSB("九一二操场", 460, 320);//12
	placeSB("工学部", 550, 60);//13
	placeSB("珞珈山", 560, 470);//14
	placeSB("梅园", 580, 590);//15
	placeSB("法学院", 680, 310);//16
	placeSB("东湖", 830, 80);//17
	placeSB("枫园", 800, 340);//18
	placeSB("离校打车点2", 850, 540);//19 共20个sights


}




void CampusGuide::run()
{
		//获取菜单的返回值
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
					//ESC退出操作 返回主界面
					if (Window::getMsg().vkcode == VK_ESCAPE)
					{
						op = MENU;
					}
					break;
				default://鼠标操作
					eventLoop();//循环更新各个部件的状态
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
	//画标题
	settextcolor(RGB(255, 120, 0));
	settextstyle(120, 60, "黑体", 0, 0, 880, 0, 1, 0);
	char str[] = "武大校园一导通";
	int tx = (Window::width() - textwidth(str)) / 2;
	int ty = 40;
	outtextxy(tx, ty, str);
	::settextstyle(20, 0, "楷体", 0, 0, 100, 0, 0, 0);
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->show();
		menu_btns[i]->event();
		if (menu_btns[i]->isClicked())
		{
			return i;
		}
	}
	//根据菜单的点击 返回操作
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
	//::settextstyle(20, 0, "楷体", 0, 0, 100, 0, 0, 0);
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
	//调用event()函数
}


void CampusGuide::placeSB(string s, int x, int y)//画景点按钮
{
	PushButton* p = new PushButton(s);
	sight_btns.emplace_back(p);
	p->setFixedSize(104, 23);
	p->move(x, y);
}

void CampusGuide::reminder()
{
	settextcolor(RGB(255, 120, 0));
	settextstyle(30, 0, "微软雅黑", 0, 0, 880, 0, 0, 0);
	outtextxy(0, 0, "按Esc键返回上一级...");
}
