#include "test2_client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Test2_Client w;
    w.show();

    return a.exec();
}
