#pragma once
#include"BasicWidget.h"
#include"configure.h"
using namespace std;
class LineEdit:public BasicWidget
{
public:
	LineEdit(int x = 0, int y = 0, int w = 150, int h = 30);
	void show()override;
	inline void setTitle(const string& title) { m_title = title; }
	inline void setPrompt(const string& prompt) { m_prompt = prompt; }
	inline const string& text()const { return m_text; }
	inline void clear() { m_text.clear(); }
	inline void setText(const string& text) { m_text = text; }

	bool textChanged();
private:
	string m_prevText;
	string m_text;
	string m_title;
	string m_prompt;
};

