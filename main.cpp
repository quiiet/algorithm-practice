#include <QCoreApplication>
#include "VacGraph.h"
#include "VacGraph.cpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CityGraph<int> *c = new CityGraph<int>(105);

    return a.exec();
}
