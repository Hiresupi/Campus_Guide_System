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
    //�Ѷ�����һ�����ݽ����и�
    static std::vector<std::string> split(std::string sstr, char separator1 = '\t');
    
    //��ҳ
    void updatePage();
    void event()override;

    inline void clear() { m_datas.clear(); }
 


public:
    //���ӿ�Ⱥ͸߶�
    int m_gridW;
    int m_gridH;
    //���ֵĿ�Ⱥ͸߶�
    int m_tw;
    int m_th;
    int middlePut;//������ʾ���

    int m_rows=15;
    int m_cols;
    
private:
    std::string m_header;
    std::vector<std::string>m_datas;

    int HeightSupply;
    int WidthSupply;

    //��ҳ��������
    int m_curPage;
    int m_maxPage;
    int m_extraData;//���һҳ�����������

    PushButton* m_preBtn;
    PushButton* m_nextBtn;
    PushButton* m_firstBtn;
    PushButton* m_lastBtn;
   
};

