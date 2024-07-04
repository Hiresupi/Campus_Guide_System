#include "PushButton.h"

PushButton::PushButton(const std::string& text, int x, int y, int w, int h)
	:BasicWidget(x,y,w,h),m_text(text){}

void PushButton::show()
{
	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h,20,20);

	settextcolor(RGB(127, 181, 114));
	settextstyle(30, 0, "微软雅黑",0,0,880,0,0,0);
	//居中显示文字
	int tx = m_x+(m_w - textwidth(m_text.c_str())) / 2;
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	::outtextxy(tx, ty, m_text.c_str());
	
}
void PushButton::show2()//景点用
{
	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 20, 20);

	settextcolor(RGB(250, 105, 18));
	settextstyle(20, 0, "微软雅黑", 0, 0, 880, 0, 0, 0);
	//居中显示文字
	int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	::outtextxy(tx, ty, m_text.c_str());

}