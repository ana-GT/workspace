#pragma once

#include <QMainWindow>
#include <QBluetoothHostInfo>
#include <QBluetoothLocalDevice>

#include "server_unit.h"

namespace Ui {
class benchmark_server;
}

class benchmark_server : public QMainWindow
{
    Q_OBJECT

public:
    explicit benchmark_server(QWidget *parent = 0);
    ~benchmark_server();

signals:
    void sendMessage( const QString &_msg );

private slots:
        void sendStartMsg();
        void sendStopMsg();
        void showMessage( const QString &_sender, const QString &_message );
        void clientConnected( const QString &_name );


private:

    server_unit* mServer;
    QString mLocalName;

    Ui::benchmark_server *ui;
    QBluetoothLocalDevice* mLocalAdapter;
};

