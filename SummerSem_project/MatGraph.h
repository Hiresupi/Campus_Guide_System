#pragma once

#include "Sights.h"
#include <vector>
#include <iomanip>

const int MAXV = 30;
const int INF = 0x3f3f3f3f;

class MatGraph
{
public:
	std::vector<std::vector<int>> edges;  // �ڽӾ�������
	int n = 0, e = 0;   // �������ͱ���
	std::vector<Sights> vexs; // ������Ϣ�洢

	MatGraph();

	void createMatGraph(std::vector<std::vector<int>> a, int n, int e, std::vector<Sights> vexs);
	void dispMatGraph();
};

