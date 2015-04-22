#pragma once

#include <QDialog>
#include <QLabel>

namespace Ui {
class ImageViewer;
}


class ImgLabel : public QLabel {
    Q_OBJECT
public:
    ImgLabel( QWidget* parent = 0, Qt::WindowFlags f = 0 );
    ~ImgLabel();
    int getXclicked() { return mX; }
    int getYclicked() { return mY; }

signals:
    void clicked();

protected:
    void mousePressEvent( QMouseEvent* _event );
    int mX;
    int mY;
};


/**
 * @class ImageViewer
 */
class ImageViewer : public QDialog
{
    Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent = 0);
    ~ImageViewer();
    bool loadFile( const QString &_filename );


public slots:
    void openFile(const QString &_filename );
    void imageClicked();

private:


    double mScaleFactor;
    ImgLabel* mLabel;
    int mX, mY;
    int mPx, mPy;
    Ui::ImageViewer *ui;
};
