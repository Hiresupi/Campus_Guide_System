#pragma once
#include "BasicWidget.h"
#include"configure.h"
#include"Window.h"

class PushButton :
    public BasicWidget
{
public:
    PushButton(const std::string& text="BUTTON",int x = 0, int y = 0, int w = 200, int h = 45);
    void show() override;
    void show2();
    void isChosen();
    void backNorm();


    std::string m_text;
};

