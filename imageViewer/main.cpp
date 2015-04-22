#include "imageviewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName( ImageViewer::tr("Robot See") );

    ImageViewer imageViewer;
    imageViewer.show();

    return app.exec();
}
