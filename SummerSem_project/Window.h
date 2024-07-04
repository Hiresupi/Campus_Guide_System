#pragma once
#include"configure.h"
class Window
{
public:
	
	Window(int w, int h, int flag);
	void setWindowTitle(const std::string& title);
	int exec();

	static int width();
	static int height();
	static void clear();
	static void beginDraw();
	static void flushDraw();
	static void endDraw();

	//����������������
	inline static bool hasMsg() 
	{ return ::peekmessage(&m_msg, EX_MOUSE | EX_KEY); }
	inline static ExMessage& getMsg()
	{
		return m_msg;
	}


private:
	HWND m_handle;//���ھ��
	 static ExMessage m_msg;//��Ϣ
};
//ExMessage Window::m_msg;
