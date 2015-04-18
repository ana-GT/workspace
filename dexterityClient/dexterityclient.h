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
    void sendMessage( const QString &_msg );
    void receiveMessage( const QString &_msg );

private slots:
    void connect();
    void disconnect();
    void sendMsg( const QString &_msg );
    void showMsg( const QString &_sender, const QString &_msg );
    void receiveMsg( const QString &_sender, const QString &_msg );
    void clientDisconnected();

private:
    Ui::DexterityClient *ui;

    client_unit* mClient;
    QString mLocalName;
    QBluetoothLocalDevice* mLocalAdapter;
};
