#include "Table.h"
#include<iostream>
using namespace std;

Table::Table(int row, int col)
	:BasicWidget(0,0,0,0),m_rows(row),m_cols(col)
	,m_curPage(0),m_maxPage(0),m_extraData(0)
{
	m_preBtn = new PushButton("��һҳ");
	m_nextBtn = new PushButton("��һҳ");
	m_firstBtn = new PushButton("��ҳ");
	m_lastBtn = new PushButton("βҳ");
}

Table::~Table()
{
	delete m_preBtn;
	delete m_nextBtn;
	delete m_firstBtn;
	delete m_lastBtn;
}

void Table::setRowCount(int row)
{
	m_rows = row;
}

void Table::setColCount(int col)
{
	m_cols = col;
}

void Table::setHeader(const std::string& header)
{
	m_header = header;
	//std::cout << "header:" << header << std::endl;
	m_cols=std::count(m_header.begin(), m_header.end(), '\t')+1;
	
	//���ֵĿ�ȸ߶�
	m_tw = ::textwidth("12��12��12:12");
	m_th = ::textheight("m_header.c_str()");

	WidthSupply = 2;
	m_gridW=::textwidth("12��12��12:12")+WidthSupply;//���ӿ��
	HeightSupply = 40;
	m_gridH=::textheight("m_header.c_str()")+HeightSupply;//���Ӹ߶�,40�Ƕ������ߵģ��������õ�

	m_w = m_gridW * m_cols;
	m_h = m_gridH *( m_rows);

	middlePut = (Window::width() - m_gridW * m_cols) / 2;//��ľ���x����

}

void Table::insertData(const std::string& data)//��m_datas���������
{
	m_datas.push_back(data);
	updatePage();
}

void Table::show()
{
	//outtextxy(0, 0, "��Esc������������...");
	updatePage();
	drawTableGrid();
	drawTableData();
	drawHeader();
}
void Table::drawTableGrid()
{
	//������
	setlinecolor(RGB(222, 93, 93));
	for (int i = 0; i < m_rows + 1; i++)
	{
		line(m_x, m_y + i * m_gridH, m_x + m_cols * m_gridW , m_y + i * m_gridH);
	}
	//������
	for (size_t i = 0; i < m_cols + 1; i++) 
	{
		line(m_x + i * m_gridW, m_y, m_x + i * m_gridW, m_y + m_rows * m_gridH);
	}
	if (m_maxPage > 0)
	{
		drawTableBottom();
	}
}

void Table::drawTableBottom()
{
	static bool flag = false;
	if (!flag)
	{
		m_preBtn->move(m_x, m_h + m_y+10);
		m_nextBtn->move(m_preBtn->x() + m_preBtn->width(), m_preBtn->y());
		m_firstBtn->move(m_nextBtn->x() + m_nextBtn->width(), m_nextBtn->y());
		m_lastBtn->move(m_firstBtn->x() + m_firstBtn->width(), m_firstBtn->y());
		//flag = true;
	}
	

	m_preBtn->show();
	m_nextBtn->show();
	m_firstBtn->show();
	m_lastBtn->show();
	
	char str[30] = { 0 };
	sprintf_s(str, "��%dҳ/��%dҳ", m_curPage + 1, m_maxPage + 1);
	outtextxy(m_lastBtn->x() + m_lastBtn->width()+4, m_lastBtn->y()+8, str);
}

void Table::drawTableData()
{
	::settextcolor(RGB(222, 95, 50));
	::settextstyle(20, 0, "����", 0, 0, 800, 0, 0, 0);

	//��ֹԽ��
	if (m_rows > m_datas.size() && m_datas.size() != 0)
	{
		m_rows = m_datas.size();
	}
	//if (m_rows == 0 && !m_datas.empty())
		//m_rows = m_datas.size();
	
	int beginPos=m_curPage*m_rows; //���ݿ�ʼ��λ��
	int endPos = m_curPage * m_rows + m_rows;//���ݽ���λ��
	//��������һ�� ��ֻ����ʣ�µ�����
	if (m_curPage == m_maxPage)
	{
		endPos = beginPos + m_extraData;
	}
	for (size_t i = beginPos, r = 0;i<endPos;i++,r++)//��
	{
		const auto& line_data = split(m_datas[i]);
		for (size_t k = 0; k < line_data.size(); k++) //��
		{
			int tx = m_x + k * m_gridW+(m_gridW-::textwidth(line_data[k].c_str()))/2 ;
			int ty = m_y +r* m_gridH+HeightSupply/2;//40��һ��
			outtextxy(tx, ty, line_data[k].c_str());
		}
	}
}
void Table::drawHeader() 
{
	setlinestyle(PS_SOLID, 2);
	rectangle(m_x, m_y - m_gridH, m_x + m_w, m_y);
	for (size_t i = 0; i < m_cols; i++)
	{
		line(m_x + i * m_gridW, m_y - m_gridH, m_x + i * m_gridW, m_y);
	}
	setlinestyle(PS_SOLID, 1);
	//�ָ��ͷ
	auto headers = split(m_header);
	for (size_t i = 0; i < headers.size(); i++)
	{
		int spaceH = (m_gridW - textwidth(headers[i].c_str())) / 2;
		int spaceV = (m_gridH - textheight(headers[i].c_str())) / 2;
		outtextxy(m_x + i * m_gridW + spaceH, m_y - m_gridH + spaceV, headers[i].c_str());
	}
}

std::vector<std::string> Table::split(std::string str, char separator1)//Ĭ�Ϸָ���Ϊ�Ʊ��
{
	
	std::vector<std::string> res;

	for (size_t pos = 0; pos<100;)
	{
		////����ָ���ָ��ַ���λ�� 1=�Ʊ�� 2=�հ�
		//int pos1 = str.find(separator1);
		//int pos2 = str.find(separator2);
		//if (pos2 != -1&&pos1!=-1)
		//{
		//	pos = min(pos1, pos2);
		//}
		//else pos = max(pos1,pos2);
		//ȡ���ַ���0-pos
		pos = str.find(separator1);
		res.push_back(str.substr(0, pos));
		//��ʣ�µ��ַ������浽str
		str = std::string(str.c_str()+pos+1);
		
	}
	return res;

}

void Table::updatePage()
{
	if (m_rows == 0 && !m_datas.empty())
	{m_rows = m_datas.size();}
	
	if (m_cols==0&& !m_datas.empty())
	{
		m_cols = m_datas.front().find("\t") + 1;
	
	}
	//trial 17������
	if (m_rows >= m_datas.size())
	{
		m_maxPage = 0;
		m_extraData = m_datas.size();
	}
	else
	{
		m_maxPage = m_datas.size() / m_rows;
		m_extraData = m_datas.size() % m_rows;
	}
}

void Table::event()
{
	//BasicWidget::event();
	m_preBtn->event();
	m_nextBtn->event();
	m_firstBtn->event();
	m_lastBtn->event();

	if (m_preBtn->isClicked())
	{
		if (m_curPage != 0)
		{
			m_curPage--;
		}
	}
	if (m_nextBtn->isClicked())
	{
		if(m_curPage!=m_maxPage)
		m_curPage++;
	}
	if (m_firstBtn->isClicked())
	{
		m_curPage = 0;
	}
	if (m_lastBtn->isClicked())
	{
		m_curPage = m_maxPage;//Խ���ˣ�
	}
}
