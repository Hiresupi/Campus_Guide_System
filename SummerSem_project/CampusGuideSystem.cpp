#include "CampusGuide.h"
//#include "CampusGuide.cpp"
using namespace std;



int main()
{
	Window w(960, 640, EX_SHOWCONSOLE);
	w.setWindowTitle("WHUУ԰һ��ͨ");

	CampusGuide cg;
	cg.run();

	return w.exec();

}