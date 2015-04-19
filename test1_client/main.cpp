#include "test1_client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Test1_Client w;
    w.show();

    return a.exec();
}
