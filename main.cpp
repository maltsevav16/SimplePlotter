#include <QApplication>
#include "simpleplotterview.h"
#include "simpleplotterscene.h"
#include "simple2dplot.h"
#include<functional>
#include<cmath>
#include "lepton/include/Lepton.h"
int main(int argc, char *argv[])
{
    double a1 = Lepton::Parser::parse("1").evaluate();
	QApplication a(argc, argv);
	SimplePlotterView pv;
	pv.show();
	return a.exec();
}
//Ограничить зум
