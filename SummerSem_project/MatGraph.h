#pragma once

#include "Sights.h"
#include <vector>
#include <iomanip>

const int MAXV = 30;
const int INF = 0x3f3f3f3f;

class MatGraph
{
public:
	std::vector<std::vector<int>> edges;  // 邻接矩阵数组
	int n = 0, e = 0;   // 顶点数和边数
	std::vector<Sights> vexs; // 景点信息存储

	MatGraph();

	void createMatGraph(std::vector<std::vector<int>> a, int n, int e, std::vector<Sights> vexs);
	void dispMatGraph();
};

