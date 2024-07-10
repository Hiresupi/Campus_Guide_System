#include "PushButton.h"

PushButton::PushButton(const std::string& text, int x, int y, int w, int h)
	:BasicWidget(x,y,w,h),m_text(text){}

void PushButton::show()
{
	setlinecolor(RGB(222, 93, 93));
	setlinestyle(PS_SOLID, 3);
	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h,20,20);

	settextcolor(RGB(127, 181, 114));
	settextstyle(30, 0, "Î¢ÈíÑÅºÚ",0,0,880,0,0,0);
	//¾ÓÖÐÏÔÊ¾ÎÄ×Ö
	int tx = m_x+(m_w - textwidth(m_text.c_str())) / 2;
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	::outtextxy(tx, ty, m_text.c_str());
	
}
void PushButton::show2()//¾°µãÓÃ
{
	setlinecolor(RGB(222, 93, 93));
	setlinestyle(PS_SOLID, 3);
	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 20, 20);

	settextcolor(RGB(250, 105, 18));
	settextstyle(20, 0, "Î¢ÈíÑÅºÚ", 0, 0, 880, 0, 0, 0);
	//¾ÓÖÐÏÔÊ¾ÎÄ×Ö
	int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	::outtextxy(tx, ty, m_text.c_str());

}

void PushButton::isChosen()
{
	this->normal_c= RGB(147, 94, 230);
}

void PushButton::backNorm()
{
	this->normal_c= RGB(232, 232, 236);
}
