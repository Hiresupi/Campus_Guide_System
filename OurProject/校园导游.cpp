#include"CampusGuide.h"
using namespace std;



int main()
{
	Window w(960, 640, EX_SHOWCONSOLE);
	w.setWindowTitle("WHU校园一导通");

	CampusGuide cg;
	cg.run();

	return w.exec();


}