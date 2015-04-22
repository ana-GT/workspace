#include <QMouseEvent>
#include <QMessageBox>
#include <QDir>
#include <QDebug>

#include "imageviewer.h"
#include "ui_imageviewer.h"


ImgLabel::ImgLabel( QWidget* parent, Qt::WindowFlags f ) :
QLabel( parent, f ) {

}

ImgLabel::~ImgLabel() {

}

void ImgLabel::mousePressEvent( QMouseEvent* _event ) {
    mX = _event->pos().x();
    mY = _event->pos().y();

    emit clicked();
}


////////////////////////////////////////////////


ImageViewer::ImageViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageViewer)
{
    ui->setupUi(this);

    // Create Label properties
    mLabel = new ImgLabel( ui->img_frame );
    mLabel->setBackgroundRole( QPalette::Base );
    mLabel->setScaledContents(true);

    // Buttons
    QObject::connect( mLabel, SIGNAL(clicked()),
                      this, SLOT(imageClicked()) );

    // Call slot
    QString name("what");
    this->openFile(name);
}



/**
 * @function ~ImageViewer
 */
ImageViewer::~ImageViewer()
{
    delete ui;
}


/**
 * @function loadFile
 */
bool ImageViewer::loadFile( const QString &_filename ) {

    QImage image( _filename );

    if( image.isNull() ) {
       QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                tr("Could not load %1.").arg(QDir::toNativeSeparators(_filename)));
       setWindowFilePath(QString());
       mLabel->setPixmap( QPixmap());
       mLabel->adjustSize();
       return false;
    }

    QImage scaledImg;
    mScaleFactor = 0.5;
    scaledImg = image.scaled( QSize(320,240), Qt::KeepAspectRatio, Qt::FastTransformation );

    mLabel->setPixmap( QPixmap::fromImage(scaledImg) );

    mLabel->adjustSize();

    setWindowFilePath( _filename );

    return true;
}

/**
 * @brief openFile
 */
void ImageViewer::openFile( const QString &_filename ) {

//    loadFile( QString("/home/ana/Pictures/grab_monster.png") );
    loadFile( QString("/storage/emulated/0/Bluetooth/Crq.png") );
}

void ImageViewer::imageClicked() {

    int x, y;
    x = (int) ( mLabel->getXclicked() / mScaleFactor );
    y = (int) ( mLabel->getYclicked() / mScaleFactor );
    QString sx = QString::number(x);
    QString sy = QString::number(y);
    QString msg; msg = QString("Pixel picked: %1 %2").arg( sx, sy );
    ui->msg_label->setText( msg );
}



