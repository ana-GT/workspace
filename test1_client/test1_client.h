#pragma once
#include <QMainWindow>
#include <QBluetoothHostInfo>
#include <QBluetoothLocalDevice>
#include <QTimer>
#include "client_unit.h"

namespace Ui {
    class Test1_Client;
}

class Test1_Client : public QMainWindow {

    Q_OBJECT

public:
    explicit Test1_Client(QWidget *parent = 0);
    ~Test1_Client();

    void showPlainMsg( const QString &_msg );

signals:
    void sendMsg_signal( const QString &_msg );
    void rcvMsg_signal( const QString &_msg );
    void serverDisconnected();

private slots:
    void connect_slot();
    void sendMsg_slot();
    void dbgMsg_slot(const QString &_msg );
    void rcvMsg_slot( const QString &_sender, const QString &_msg );
    void clientDisconnected_slot();
    void updateTimeDisplay_slot();

private:
    Ui::Test1_Client *ui;
    client_unit* mClient;
    QString mLocalName;
    QBluetoothLocalDevice* mLocalAdapter;

    QTimer* mTimer;
    int mNumTimeouts;
};
