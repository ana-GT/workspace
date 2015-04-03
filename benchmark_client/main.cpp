#include "benchmark_client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    benchmark_client w;
    w.show();

    return a.exec();
}
