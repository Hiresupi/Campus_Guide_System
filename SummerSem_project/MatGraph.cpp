#include "MatGraph.h"

using namespace std;

MatGraph::MatGraph()
{
	this->edges = vector<vector<int>>(MAXV, vector<int>(MAXV, INF));
}

void MatGraph::createMatGraph(std::vector<std::vector<int>> a, int n, int e, std::vector<Sights> vexs)
{
	this->n = n;
	this->e = e;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			this->edges[i][j] = a[i][j];
		}
	}
	this->vexs = vexs;
}

void MatGraph::dispMatGraph()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (edges[i][j] == INF)
			{
				cout << "?" << setw(4);
			}
			else
			{
				cout << edges[i][j] << setw(4);
			}
		}
		cout << endl;
	}
}
