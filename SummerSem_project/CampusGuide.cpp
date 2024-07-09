#include"CampusGuide.h"


CampusGuide::CampusGuide()
{
	readSights();
	readRoutes();

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
	//placeSB("离校打车点1", 20, 180);//0   画线条用的标记中点坐标为（x+SBheight/2，y+SBwidth/2）
	//placeSB("计算机学院", 68, 275);//1
	//placeSB("卓尔体育馆", 88, 335);//2
	//placeSB("武汉大学牌坊", 90, 560);//3
	//placeSB("武大附小", 165, 60);//4
	//placeSB("桂园操场",230 , 300);//5
	//placeSB("总图书馆", 265, 425);//6
	//placeSB("万林博物馆", 330, 370);//7
	//placeSB("樱花城堡", 320, 175);//8
	//placeSB("樱花大道", 410, 240);//9
	//placeSB("水生研究所", 370,80);//10
	//placeSB("居民区", 390,595);//11
	//placeSB("九一二操场", 460, 320);//12
	//placeSB("工学部", 550, 60);//13
	//placeSB("珞珈山", 560, 470);//14
	//placeSB("梅园", 580, 590);//15
	//placeSB("法学院", 680, 310);//16
	//placeSB("东湖", 830, 80);//17
	//placeSB("枫园", 800, 340);//18
	//placeSB("离校打车点2", 850, 540);//19 共20个sights
	for (int i = 0; i < SightList.size(); i++)
	{
		placeSB(SightList[i].name, SightList[i].x, SightList[i].y);
	}


	//查询部件初始化
	SightSearchBtn.reset(new PushButton("搜索", 700, 30));
	SightEdit.reset(new LineEdit(100, 30, 570, 45));
	SightEdit->setTitle("请输入景点全称（如：武汉大学牌坊）");
	SightEdit->setPrompt("武汉大学牌坊");

	//景点信息查看初始化


	ToiletBtn.reset(new PushButton("附近厕所", 435, 450));
	CafeBtn.reset(new PushButton("附近餐厅", 710,450));


	//管理员入口初始化
	LoginBtn.reset(new PushButton("进入", 700, 170));
	LoginEdit.reset(new LineEdit(100, 170, 570, 45));
	LoginEdit->setTitle("请输入密钥");

	subMenu_btns.emplace_back(new PushButton("增加新景点"));
	subMenu_btns.emplace_back(new PushButton("增加新路线"));
	subMenu_btns.emplace_back(new PushButton("删除景点"));
	subMenu_btns.emplace_back(new PushButton("删除路线"));

	for (int i = 0; i < subMenu_btns.size(); i++)
	{
		subMenu_btns[i]->setFixedSize(250, 45);
		int bx = (Window::width() - subMenu_btns[i]->width()) / 2;
		int by = 240 + i * (subMenu_btns[i]->height() + 20);
		//移动到中间
		subMenu_btns[i]->move(bx, by);
	}


}




void CampusGuide::run()
{

		//获取菜单的返回值
		int op = MENU;
		int choice = 666;
		//const int add = 1;
		//const int amend = 2;
		bool saySorry = false;
		bool saySorry2 = false;
		int signal=-1;//接收鼠标点击信号


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
						if (Page != -1)
						{
							Page = -1;
						}
						else if (signal != -1)
						{
							signal = -1;
						}//信息查询功能子界面
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
						SightEdit->setText("");//分支点一的清理
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
			}//速查功能抱歉
			if (saySorry2)
			{
				Sleep(2000);
				saySorry2 = false;
			}//管理员密码抱歉

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

void CampusGuide::ShowInfo(int &signal)
{
	if (signal == -1)signal = ShowMap();
	else
	{
		reminder();
		if (flag != 3)
		{
			::loadimage(&m_bk, "assets/背景3.JPG", Window::width(), Window::height());
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
		putimage(380, 570, &LOGO);//放logo

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
			putimage(8, 128, 400, 300, &sightPic, 0, 0);//放景点图片

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


// 显示景点信息
void CampusGuide::showSightTable(Sights& s)
{
	SightTable.reset(new Table);
	SightTable->setRowCount(4);
	string header = "景点名称	";
	header += s.name;
	SightTable->setHeader02(header);
	string line1 = "简介	"; line1 += s.info;
	string line2 = "推荐指数	"; line2 += s.star;
	string line3 = "有无餐厅	";
	string line4 = "有无厕所	";
	if (s.canteen) line3 += "有";
	else line3 += "无";
	if (s.toilet) line4 += "有";
	else line4 += "无";

	SightTable->insertData(line1);
	SightTable->insertData(line2);
	SightTable->insertData(line3);
	SightTable->insertData(line4);

	SightTable->move(SightTable->tempX, SightTable->tempY);//表格位置

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
	string header = "景点名	距所在地最短距离";
	CafeToiletTable->setHeader(header);
	//接下来就是insert一下，然后就可以show了


}

// 运用Floyd算法求最短路径，返回含有id的路径vector
vector<int> CampusGuide::FindShort(MatGraph& g, int src, int dst)
{
	vector<vector<int>> A(MAXV, vector<int>(MAXV, INF));
	vector<vector<int>> path(MAXV, vector<int>(MAXV, INF));
	Floyd(g, A, path);
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


bool CampusGuide::Administrate()
{
	if (state == -1)state = 0;
	reminder();
	if (state == 0)
	{
		string str1("请输入管理员序列码");
		settextcolor(RGB(255, 120, 0));
		settextstyle(56, 28, "Bulter");
		//settextstyle(40, 0, "宋体", 0, 0, 800, 0, 0, 0);
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
		string str1("序列码错误，请检查后重新输入!");
		settextcolor(RGB(221, 255, 148));
		settextstyle(50, 25, "Bulter");
		//settextstyle(40, 0, "宋体", 0, 0, 800, 0, 0, 0);
		outtextxy((Window::width() - textwidth(str1.c_str())) / 2,
			(Window::height() - textheight(str1.c_str())) / 2, str1.c_str());
		return true;//抱歉提示
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
	if (str == "樱花城堡"||str=="樱顶")
	{
		::loadimage(&m_bk, "assets/pics/Pic8.JPG", Window::width(), Window::height());
	}
	else if(str == "樱花大道")
	{
		::loadimage(&m_bk, "assets/pics/Pic9.JPG", Window::width(), Window::height());
	}
	else if (str == "总图书馆"||str=="图书馆")
	{
		::loadimage(&m_bk, "assets/pics/Pic6.JPG", Window::width(), Window::height());
	}
	else if (str == "计算机学院")
	{
		::loadimage(&m_bk, "assets/pics/Pic1.JPG", Window::width(), Window::height());
	}
	else if (str == "万林博物馆")
	{
		::loadimage(&m_bk, "assets/pics/Pic2.JPG", Window::width(), Window::height());
	}
	else if (str == "武汉大学牌坊")
	{
		::loadimage(&m_bk, "assets/pics/Pic3.JPG", Window::width(), Window::height());
	}
	else if (str == "九一二操场"||str=="912操场")
	{
		::loadimage(&m_bk, "assets/pics/Pic12.JPG", Window::width(), Window::height());
	}
	else if (str == "东湖")
	{
		::loadimage(&m_bk, "assets/pics/Pic17.JPG", Window::width(), Window::height());
	}
	else if (str == "卓尔体育馆")
	{
		::loadimage(&m_bk, "assets/pics/Pic2.JPG", Window::width(), Window::height());
	}
	else if(str!="")
	{
		string str1("抱歉，请检查输入或当前暂无该景点信息!");
		settextcolor(RGB(221,255,148));
		//settextstyle(60, 30, "Bulter");
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


void CampusGuide::placeSB(string s, int x, int y)//画景点按钮
{
	PushButton* p = new PushButton(s);
	sight_btns.emplace_back(p);
	p->setFixedSize(SBheight, SBwidth);
	p->move(x, y);
}

void CampusGuide::reminder()
{
	settextcolor(RGB(255, 120, 0));
	settextstyle(30, 0, "微软雅黑", 0, 0, 880, 0, 0, 0);
	outtextxy(0, 0, "按Esc键返回上一级...");
}

// 从文件中读取景点信息
void CampusGuide::readSights()
{
	ifstream fin("assets/sights.txt");
	Sights item;

	while (fin >> item)
	{
		SightList.push_back(item);
	}
	
}

// 从文件中读取路径信息
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


