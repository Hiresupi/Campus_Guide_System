#pragma once
#include "BasicWidget.h"
#include"configure.h"
#include"Window.h"
#include<vector>
#include<iostream>
#include"PushButton.h"
class Table :
    public BasicWidget
{
public:
    Table(int row = 0, int col = 0);
    ~Table();
    void setRowCount(int row);
    void setColCount(int col);
    int rowCount()const { return m_datas.size(); }
    int colCount()const { return m_cols; }
    void setHeader(const std::string& header);
    void insertData(const std::string& data);

    void show();
    
    void drawTableGrid();
    void drawTableBottom();
    void drawTableData();
    void drawHeader();
    //把读到的一行数据进行切割
    static std::vector<std::string> split(std::string sstr, char separator1 = '\t');
    
    //分页
    void updatePage();
    void event()override;

    inline void clear() { m_datas.clear(); }
 


public:
    //格子宽度和高度
    int m_gridW;
    int m_gridH;
    //文字的宽度和高度
    int m_tw;
    int m_th;
    int middlePut;//居中显示表格

    int m_rows=15;
    int m_cols;
    
private:
    std::string m_header;
    std::vector<std::string>m_datas;

    int HeightSupply;
    int WidthSupply;

    //分页处理数据
    int m_curPage;
    int m_maxPage;
    int m_extraData;//最后一页多出来的数据

    PushButton* m_preBtn;
    PushButton* m_nextBtn;
    PushButton* m_firstBtn;
    PushButton* m_lastBtn;
   
};

