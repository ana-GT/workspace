#pragma once

#include <QMainWindow>
#include <QBluetoothHostInfo>
#include <QBluetoothLocalDevice>
#include <QTimer>

#include "server_unit.h"

namespace Ui {
class DexterityServer;
}

class DexterityServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit DexterityServer(QWidget *parent = 0);
    ~DexterityServer();

 signals:
    void sendMsg_signal( const QString &_msg );
    void rcvMsg_signal( const QString &_msg );

  public slots:
    void dbgMsg_slot( const QString &_msg );

private slots:
    void sendMsg_slot();
    void showMsg_slot( const QString &_sender, const QString &_msg );
    void clientConnected_slot( const QString &_name );
    void updateTimeDisplay_slot();

private:
    Ui::DexterityServer *ui;

    server_unit* mServer;
    QString mLocalName;
    QBluetoothLocalDevice* mLocalAdapter;
    QTimer* mTimer;
    int mNumTimeouts;
};
