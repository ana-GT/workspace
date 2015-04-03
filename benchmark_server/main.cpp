#include "benchmark_server.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    benchmark_server w;
    w.show();

    return a.exec();
}
