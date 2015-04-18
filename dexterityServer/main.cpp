#include "dexterityserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DexterityServer w;
    w.show();

    return a.exec();
}
