#pragma once

#include <QMainWindow>
#include <QBluetoothHostInfo>
#include <QBluetoothLocalDevice>
#include <QTimer>

#include "client_unit.h"

namespace Ui {
class DexterityClient;
}

class DexterityClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit DexterityClient(QWidget *parent = 0);
    ~DexterityClient();
    void showPlainMsg( const QString &_msg );

 signals:
    void sendMsg_signal( const QString &_msg );
    void rcvMsg_signal( const QString &_msg );
    void serverDisconnected();

private slots:
    void connect_slot();
    void sendTestMsg_slot();
    void dbgMsg_slot(const QString &_msg );
    void rcvMsg_slot( const QString &_sender, const QString &_msg );
    void clientDisconnected_slot();

private:
    Ui::DexterityClient *ui;

    client_unit* mClient;
    QString mLocalName;
    QBluetoothLocalDevice* mLocalAdapter;
};
