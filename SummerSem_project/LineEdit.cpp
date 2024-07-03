#include "LineEdit.h"

LineEdit::LineEdit(int x, int y, int w, int h)
	:BasicWidget(x,y,w,h){}

void LineEdit::show()
{
	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 20, 20);

	settextcolor(RGB(222, 130, 218));
	settextstyle(30, 0, "微软雅黑", 0, 0, 880, 0, 0, 0);
	//居中显示文字
	int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	::outtextxy(tx, ty, m_text.c_str());
	//点击自己 弹出对话框
	if (isClicked())
	{
		char buf[128];
		InputBox(buf, 128, nullptr, m_title.data(), m_prompt.data());
		if (buf[0] != '\0')//保证信息不被修改置空
		{
			m_text = buf;
		}
		
	}
}

bool LineEdit::textChanged()
{
	if (m_text.empty())
		return false;
	
	if (m_prevText == m_text)
	{
		return false;
	}
	m_prevText = m_text;
	return true;
}
