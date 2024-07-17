#include"CampusGuide.h"

CampusGuide::CampusGuide()
{
	readSights();
	int routeCnt=readRoutes();
	M.createMatGraph(RWeight, SightList.size(), routeCnt, SightList);
	//构造
	LOGFONT f;
	gettextstyle(&f);
	f.lfQuality = ANTIALIASED_QUALITY;//文字抗锯齿
	settextstyle(&f);
	::settextstyle(20, 0, "楷体", 0, 0, 100, 0, 0, 0); //settextstyle(120, 60, "黑体", 0, 0, 880, 0, 1, 0);
	::loadimage(&m_bk, "assets/WHU.JPEG", Window::width(), Window::height());

	//主界面按钮初始化
	menu_btns.emplace_back(new PushButton("热门景点速查"));
	menu_btns.emplace_back(new PushButton("查询开放景点"));
	menu_btns.emplace_back(new PushButton("查询可行路线"));
	menu_btns.emplace_back(new PushButton("管理员入口"));
	menu_btns.emplace_back(new PushButton("退出"));
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->setFixedSize(250, 45);
		int bx = (Window::width() - menu_btns[i]->width()) / 2;
		int by = 240 + i * (menu_btns[i]->height() + 20);
		//移动到中间
		menu_btns[i]->move(bx, by);
	}

	//景点按钮初始化
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
	ToiletBtn.reset(new PushButton("附近有厕所景点", 435, 450));
	CafeBtn.reset(new PushButton("附近有餐厅景点", 710,450));
	CafeToiletTable.reset(new Table);

	//查询路线部件初始化
	ShortBtn.reset(new PushButton("显示最短距离路线"));
	ShortBtn->move(755, 3);

	//管理员入口初始化
	LoginBtn.reset(new PushButton("进入", 700, 170));
	LoginEdit.reset(new LineEdit(100, 170, 570, 45));
	LoginEdit->setTitle("请输入密钥");
	subMenu_btns.emplace_back(new PushButton("增加新景点及路线"));
	subMenu_btns.emplace_back(new PushButton("删除景点"));

	for (int i = 0; i < subMenu_btns.size(); i++)
	{
		subMenu_btns[i]->setFixedSize(250, 45);
		int bx = (Window::width() - subMenu_btns[i]->width()) / 2;
		int by = 240 + i * (subMenu_btns[i]->height() + 30);
		//移动到中间
		subMenu_btns[i]->move(bx, by);
	}

	addSightEdit.reset(new LineEdit(100, 200, 570, 45));
	addSightBtn.reset(new PushButton("添加", 700, 200));
	addSightEdit->setTitle("请按照格式输入！");

	//加路输入部件
	weightEdit.reset(new LineEdit(700,3,150,30));
	weightEdit->setTitle("请输入距离（默认单位：m）");
	confirmBtn.reset(new PushButton("确认",855,3,100,30));

	deleteBtn.reset(new PushButton("确认删除", 805, 3, 150, 40));

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

		int start=-1, end=-1;//接收查路线时的起始和结尾

		int routeBuild = -1;//管理员加路径页面转化标识
		bool alreadyAdd = false;//若为真 已经加了一条路线了
		int sightDeleted = -1;//删除的点的id
		bool alreadyDelete = false;//标记是否有点被删

		vector<int>distV;//存放最短路径id

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
						}//信息查询功能子界面

						else if (operationPage!=-1)
						{
							if (operationPage == 2)//选择新景点位置
							{
								operationPage = 0;
								::loadimage(&m_bk, "assets/WHU.JPEG", Window::width(), Window::height());
								flag = 1;
							}
							else if (operationPage == 3)//添加路线
							{
								
								if (routeAdded!=0||alreadyAdd)//有路径加入,意味着成功添加了一个景点
								{
									//sight_btns[routeBuild]->backNorm();
									//routeBuild = -1;
									if (routeBuild!=-1)//被点击了，需要回退到 “继续加路”
									{
										sight_btns[routeBuild]->backNorm();
										routeBuild = -1;
										operationPage = 3;
										if (routeAdded != 0)
										{
											updateMatGraph(routeAdded, 1);//更新route
											routeAdded = 0;
										}
										//sight_btns[SightList.size() - 1]->backNorm();
									}
									else//没有被点击，那么直接退到前面
									{
										if (routeAdded != 0)
										{
											updateMatGraph(routeAdded, 1);//更新route
											routeAdded = 0;
										}
										operationPage = 0;
										alreadyAdd = false;
										sight_btns[SightList.size() - 1]->backNorm();
										addSightEdit->setText("");
										::loadimage(&m_bk, "assets/WHU.JPEG", Window::width(), Window::height());//背景切换
										flag = 1;
										//SightList.pop_back();
										//sight_btns.pop_back();
										//operationPage = 2;
									}
									weightEdit->setText("");
								}
								else//没有路径加入
								{
									if (routeBuild!=-1)//有点击
									{
										sight_btns[routeBuild]->backNorm();
										operationPage = 3;
										routeBuild = -1;

									}
									else //没有加路径
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
							else if (operationPage == 0)
							{
								operationPage = -1;
								addSightEdit->setText("");
							}
							else if (operationPage == 1)
							{
								if (!alreadyDelete)//没有被删
								{
									if (sightDeleted != -1)//选中了
									{
										sight_btns[sightDeleted]->backNorm();
										sightDeleted = -1;
									}
									else //没有选中
									{
										operationPage = -1;
										::loadimage(&m_bk, "assets/WHU.JPEG", Window::width(), Window::height());//背景切换
										flag = 1;
									}
								}
								else //有被删除的
								{
									if (sightDeleted != -1)//选中了
									{
										sight_btns[sightDeleted]->backNorm();
										sightDeleted = -1;
									}
									else
									{
										operationPage = -1;
										sightDeleted = -1;
										alreadyDelete = false;
										::loadimage(&m_bk, "assets/WHU.JPEG", Window::width(), Window::height());//背景切换
										flag = 1;
									}
								}
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
				drawLine(start,end,distV);
				ShowMap();
				break;

			case CampusGuide::MODIFY:
				saySorry2=Administrate(routeBuild,alreadyAdd,sightDeleted,alreadyDelete);
				break;

			case CampusGuide::EXIT:
				//saveFile("assets/flights");
				//saveFile02("assets/customers");
				//fstream fout("assets/sights.txt", ios::out);
				//for (int i = 0; i < sight_btns.size(); i++)
				//{
				//	fout << sight_btns[i]->m_text <<"	" << sight_btns[i]->x() << "	" << sight_btns[i]->y() << "	" << i << endl;
				//}
				saveToFile();
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
			::loadimage(&m_bk, "assets/背景3.JPG", Window::width(), Window::height());
			::loadimage(&LOGO, "assets/LOGO.PNG", 200, 63);

			flag = 3;
		}
		string file = "assets/pics/";
		file += SightList[signal].name + ".JPG";


		if (flag1 != signal)
		{
			ifstream f(file.c_str());
			if (!f.good())
			{
				if (flag1 != 999)
				{
					::loadimage(&sightPic, "assets/pics/default.jpg", 370, 270);
					flag1 = 999;
				}

			}
			else
			{
				::loadimage(&sightPic, file.c_str(), 370, 270);
				flag1 = signal;
			}

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
			putimage(8, 128, 400, 300, &sightPic, 0, 0);//放景点图片

			showSightTable(SightList[signal]);
		}
	}
}

// Floyd 算法
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

// 搜索附近设施
void CampusGuide::searchFacility(MatGraph& g, int page, int id, vector<string>& svec, vector<int>& ivec)
{
	vector<vector<int>> A(MAXV, vector<int>(MAXV, INF));
	vector<vector<int>> path(MAXV, vector<int>(MAXV, INF));
	Floyd(g, A, path);
	if (page == 2)//厕所
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
	else if(page==1)//餐厅
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
	//page标识是厕所页面还是餐厅页面
	CafeToiletTable.reset(new Table);
	CafeToiletTable->setRowCount(5);
	string header = "景点名	距所在地最短距离";
	CafeToiletTable->setHeader(header);
	//接下来就是insert一下，然后就可以show了
	vector<string>nameV; vector<int>distV;
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

// 运用Floyd算法求最短路径，返回含有id的路径vector
int CampusGuide::FindShort(MatGraph& g, int src, int dst, vector<int>& distVec)
{
	vector<vector<int>> A(MAXV, vector<int>(MAXV, INF));
	vector<vector<int>> path(MAXV, vector<int>(MAXV, INF));
	Floyd(g, A, path);
	distVec = Dispath(A, path, g.n, src, dst);
	return A[src][dst];
}

// 寻找i到j的最短路径
vector<int> CampusGuide::Dispath(vector<vector<int>> A, vector<vector<int>> path, int n, int i, int j)
{
	if (A[i][j] != INF && i != j)   // 寻找前一个结点并加入vector
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
		reverse(apath.begin(), apath.end());   // 逆置路径数组
		return apath;
	}
}

void CampusGuide::ShowAllRoute()
{
	setlinestyle(PS_DASHDOT,3);
	setlinecolor(RGB(50, 19, 176));
	//中点坐标为（y+SBheight/2，x+SBwidth/2）
	for(int i=0;i<SightList.size();i++)
		for(int j=0;j<i;j++)
			if (RWeight[i][j] != INF && RWeight[i][j] != 0)
			{
				//画虚线
				int beginX = SightList[i].x + SBwidth / 2;
				int beginY= SightList[i].y + SBheight/ 2;
				int endX = SightList[j].x + SBwidth/ 2;
				int endY = SightList[j].y + SBheight/ 2;
				line(beginX, beginY, endX, endY);
			}



}


int CampusGuide::NavigateHint(string s)
{
	settextcolor(RGB(147, 94, 230));
	settextstyle(40, 0, "微软雅黑", 0, 0, 880, 0, 0, 0);
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
	
		end = NavigateHint("请选择目标景点");
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
			string str = "全程共" + to_string(dist) + "m";
			settextcolor(RGB(147, 94, 230));
			outtextxy(810, 610, str.c_str());
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

bool CampusGuide::Administrate(int& routeBuild,bool& alreadyAdd,int &sightDeleted,bool&alreadyDelete)
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
	else if (state == 1)//进入增删的界面了
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
		case 0://选择添加
		{
			string str1 = "请按<景点名 简介 推荐值(★) 有/无厕所 有/无餐厅>格式输入基本信息";
			string str2 = "ps：中间空格隔开，且只有正确输入格式才能成功添加";
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

		case 1://删除功能
		{
			ShowAllRoute();
			if (sightDeleted == -1)
			{
				if (alreadyDelete)
				{
					string note("点击其他景点可继续删除");
					settextcolor(RGB(147, 94, 230));
					//settextstyle(50, 25, "宋体");
					settextstyle(30, 0, "微软雅黑", 0, 0, 880, 0, 0, 0);
					outtextxy(710, 0, note.c_str());
				}
				else
				{
					string note("请单击选择要删除的景点");
					settextcolor(RGB(147, 94, 230));
					//settextstyle(50, 25, "宋体");
					settextstyle(30, 0, "微软雅黑", 0, 0, 880, 0, 0, 0);
					outtextxy(710, 0, note.c_str());
				}
				sightDeleted = ShowMap();
			}
			else
			{
				sight_btns[sightDeleted]->isChosen();
				ShowMap();
				deleteBtn->show();
				if (deleteBtn->isClicked())
				{
					//调用delete的函数
					deteleSights(sightDeleted);
					operationPage = 1;
					sightDeleted = -1;
					alreadyDelete = true;
				}
			}
			break;
		}
		case 2://选择位置
		{
			int x, y;//坐标
			ShowMap();
			string note("请单击选择新增景点的位置");
			settextcolor(RGB(147, 94, 230));
			//settextstyle(50, 25, "宋体");
			settextstyle(30, 0, "微软雅黑", 0, 0, 880, 0, 0, 0);
			outtextxy(690, 0, note.c_str());
			auto& m_msg = Window::getMsg();
			if (m_msg.message == WM_LBUTTONDOWN)//左键单击
			{
				x = m_msg.x-SBwidth/2; y = m_msg.y-SBheight/2;
				addSights(addSightEdit->text(), x, y);
				placeSB(SightList[SightList.size() - 1].name, SightList[SightList.size() - 1].x, SightList[SightList.size() - 1].y);
				sight_btns[sight_btns.size() - 1]->isChosen();
				operationPage = 3;
			}

			break;
		}

		case 3://加路
		{
			
			if(routeBuild==-1)
			routeBuild=ShowMap();

			if (routeBuild != -1)
			{
				sight_btns[routeBuild]->isChosen();
				string note2 = "请输入该路线距离：";
				settextstyle(30, 0, "微软雅黑", 0, 0, 880, 0, 0, 0);
				settextcolor(RGB(255, 120, 0));
				outtextxy(510, 0, note2.c_str());
				weightEdit->show();
				confirmBtn->show();
				setlinestyle(PS_DASHDOT, 3);
				setlinecolor(RGB(50, 19, 176));
				//中点坐标为（y+SBheight/2，x+SBwidth/2）
				//画虚线
				int a = SightList.size()-1;
				int beginX = SightList[a].x + SBwidth / 2;
				int beginY = SightList[a].y + SBheight / 2;
				int endX = SightList[routeBuild].x + SBwidth / 2;
				int endY = SightList[routeBuild].y + SBheight / 2;
				line(beginX, beginY, endX, endY);
				ShowMap();
				if (weightEdit->text() != "" && confirmBtn->isClicked())//输入权值并添加
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
				if (routeAdded == 0&&!alreadyAdd)//没有路线添加成功
				{

					string note2 = "添加成功！单击其他景点添加路线";
					settextstyle(30, 0, "微软雅黑", 0, 0, 880, 0, 0, 0);
					settextcolor(RGB(147, 94, 230));
					outtextxy(630, 0, note2.c_str());
				}
				else
				{
					alreadyAdd = true;
					string note2 = "路线添加成功！可单击其他景点继续添加";
					settextstyle(30, 0, "微软雅黑", 0, 0, 880, 0, 0, 0);
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
	string file = "assets/pics/" + str + ".JPG";
	ifstream f(file.c_str());
	if(SightSearchBtn->isClicked()&&!str.empty())
	if (str == "樱花城堡"||str=="樱顶")
	{
		::loadimage(&m_bk, "assets/pics/樱花城堡.JPG", Window::width(), Window::height());
	}

	else if (str == "总图书馆"||str=="图书馆")
	{
		::loadimage(&m_bk, "assets/pics/总图书馆.JPG", Window::width(), Window::height());
	}

	else if (str == "九一二操场"||str=="912操场")
	{
		::loadimage(&m_bk, "assets/pics/九一二操场.JPG", Window::width(), Window::height());
	}
	else if (f.good())
	{
		::loadimage(&m_bk, file.c_str(), Window::width(), Window::height());
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

	//if (CafeToiletTable != NULL)
	CafeToiletTable->event();

	ShortBtn->event();

	addSightBtn->event();
	addSightEdit->event();

	weightEdit->event();
	confirmBtn->event();
	deleteBtn->event();
}

void CampusGuide::updateMatGraph(int eCnt, int nCnt)
{
	M.edges = RWeight;
	M.vexs = SightList;
	M.n += nCnt;
	M.e += eCnt;
}

void CampusGuide::placeSB(string s, int x, int y)//画景点按钮
{
	PushButton* p = new PushButton(s);
	sight_btns.emplace_back(p);
	p->setFixedSize(SBwidth, SBheight);
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
	stmp.toilet = (toilet == "有") ? 1 : 0;
	stmp.canteen = (canteen == "有") ? 1 : 0;
	stmp.x = x;
	stmp.y = y;
	stmp.id = SightList.size();
	SightList.push_back(stmp);
}

void CampusGuide::deteleSights(int id)
{
	int eCnt = 0;
	for (int i = id; i < SightList.size() - 1; i++)
	{
		SightList[i] = SightList[i + 1];
		SightList[i].id--;
	}
	SightList.pop_back();
	sight_btns.clear();
	for (int i = 0; i < SightList.size(); i++)
	{
		placeSB(SightList[i].name, SightList[i].x, SightList[i].y);
	}
	for (int j = 0; j < SightList.size(); j++)
	{
		if (RWeight[id][j] != INF && RWeight[id][j] != 0)
		{
			eCnt--;
		}
	}

	for (int i = id; i < SightList.size(); i++)
	{
		RWeight[i] = RWeight[i + 1];
	}
	RWeight[SightList.size()] = vector<int>(MAXV, INF);
	for (int i = 0; i < SightList.size(); i++)
	{
		for (int j = id; j < SightList.size(); j++)
		{
			RWeight[i][j] = RWeight[i][j + 1];
		}
		RWeight[i][SightList.size()] = INF;
	}
	updateMatGraph(eCnt, -1);
}

void CampusGuide::saveToFile()
{
	ofstream fout("assets/sights.txt");
	for (auto sight : SightList)
	{
		fout << sight << endl;
	}
	fout.close();
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
	fout.close();
}


