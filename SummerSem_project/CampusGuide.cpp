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
	menu_btns.emplace_back(new PushButton("热门景点速查"));
	menu_btns.emplace_back(new PushButton("景点查询"));
	menu_btns.emplace_back(new PushButton("路线查询"));
	menu_btns.emplace_back(new PushButton("管理员入口"));
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
	placeSB("离校打车点1", 20, 180);//0   画线条用的标记中点坐标为（x+SBheight/2，y+SBwidth/2）
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


	//查询部件初始化
	SightSearchBtn.reset(new PushButton("搜索", 700, 30));
	SightEdit.reset(new LineEdit(100, 30, 600, 45));
	SightEdit->setTitle("请输入景点全称（如：武汉大学牌坊）");
	SightEdit->setPrompt("武汉大学牌坊");


}




void CampusGuide::run()
{
		//获取菜单的返回值
		int op = MENU;
		int choice = 666;
		//const int add = 1;
		//const int amend = 2;
		bool saySorry = false;

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
						SightEdit->setText("");
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
					::loadimage(&m_bk, "assets/WHU.JPEG", Window::width(), Window::height());
				}
				break;
			case CampusGuide::SHOW:
				ShowPic();
				saySorry=searchNshow();
				break;
			case CampusGuide::SEARCH:
				ShowMap();
				break;
			case CampusGuide::FIND:
				ShowMap();
				break;
			case CampusGuide::MODIFY:
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

// 显示景点信息
void CampusGuide::ShowInfo(Sights& s)
{
	cout << s.address << s.info << s.canteen << s.toilet;
}

// 运用Floyd算法求最短路径，返回含有id的路径vector
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
 
// 寻找i到j的最短路径
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
	auto str = SightEdit->text();
	if(SightSearchBtn->isClicked()&&!str.empty())
	if (str == "樱花城堡"||str=="樱顶")
	{
		::loadimage(&m_bk, "assets/pics/樱花城堡.JPG", Window::width(), Window::height());
	}
	else if(str == "樱花大道")
	{
		::loadimage(&m_bk, "assets/pics/樱花大道.JPG", Window::width(), Window::height());
	}
	else if (str == "总图书馆"||str=="图书馆")
	{
		::loadimage(&m_bk, "assets/pics/总图书馆.JPG", Window::width(), Window::height());
	}
	else if (str == "计算机学院")
	{
		::loadimage(&m_bk, "assets/pics/计算机学院.JPG", Window::width(), Window::height());
	}
	else if (str == "万林博物馆")
	{
		::loadimage(&m_bk, "assets/pics/万林博物馆.JPG", Window::width(), Window::height());
	}
	else if (str == "武汉大学牌坊")
	{
		::loadimage(&m_bk, "assets/pics/牌坊.JPG", Window::width(), Window::height());
	}
	else if (str == "九一二操场"||str=="912操场")
	{
		::loadimage(&m_bk, "assets/pics/912.JPG", Window::width(), Window::height());
	}
	else if (str == "东湖")
	{
		::loadimage(&m_bk, "assets/pics/东湖.JPG", Window::width(), Window::height());
	}
	else if (str == "卓尔体育馆")
	{
		::loadimage(&m_bk, "assets/pics/卓尔体育馆.JPG", Window::width(), Window::height());
	}
	else if(str!="")
	{
		string str1("抱歉，请检查输入或当前暂无该景点信息!");
		settextcolor(RGB(221,255,148));
		settextstyle(40, 0, "宋体", 0, 0, 800, 0, 0, 0);
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
	//调用各个部件的event函数
	for (int i = 0; i < sight_btns.size(); i++)
	{
		sight_btns[i]->event();
	}
	SightSearchBtn->event();
	SightEdit->event();

	//CafeBtn->event();
	//ToiletBtn->event();
	//CafeTable->event();
	//ToiletTable->event();


	//ShortBtn->event();
	//AllBtn->event();
}


void CampusGuide::placeSB(string s, int x, int y)//画景点按钮
{
	PushButton* p = new PushButton(s);
	sight_btns.emplace_back(p);
	p->setFixedSize(SBheight, SBwidth);
	p->move(x, y);
}

void CampusGuide::reminder()
{
	settextcolor(RGB(0, 176,32));
	settextstyle(30, 0, "微软雅黑", 0, 0, 880, 0, 0, 0);
	outtextxy(0, 0, "按Esc键返回上一级...");
}

// 从文件中读取景点信息
vector<Sights> CampusGuide::readSights()
{
	ifstream fin("assets/sights.txt");
	Sights item;
	vector<Sights> svec;
	while (fin >> item)
	{
		svec.push_back(item);
	}
	return svec;
}

// 从文件中读取路径信息
vector<vector<int>> CampusGuide::readRoutes()
{
	ifstream fin("assets/routes.txt");
	vector<vector<int>> a(MAXV, vector<int>(MAXV, INF));
	int i, j;
	int length;
	for (int i = 0; i < MAXV; i++)
	{
		a[i][i] = 0;
	}
	while (fin >> i >> j >> length)
	{
		a[i][j] = length;
		a[j][i] = length;
	}
	return a;
}
