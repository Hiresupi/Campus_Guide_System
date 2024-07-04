#pragma once
#include<easyx.h>
class BasicWidget
{
public:
	BasicWidget(int x, int y, int w, int h);
	virtual ~BasicWidget() {}
	int width();
	int height();
	void setFixedSize(int w, int h);

	int x();
	int y();
	void move(int x, int y);

	bool isIn();//�ж�����Ƿ��ڰ�ť��
	bool isClicked();//�ж�����Ƿ���

	virtual void show() = 0;//��������д
	virtual void event() ;

	void setBackgroundColor(COLORREF c);
	void setHoverColor(COLORREF c);


public:
	int m_x;
	int m_y;
	int m_w;
	int m_h;

	COLORREF cur_c = RGB(232, 232, 236);
	COLORREF normal_c = RGB(232, 232, 236);
	COLORREF hover_c = RGB(41, 55, 125);
};

