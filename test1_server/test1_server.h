#pragma once

#include <QMainWindow>
#include <QBluetoothHostInfo>
#include <QBluetoothLocalDevice>
#include "server_unit.h"

namespace Ui {
class Test1_Server;
}

class Test1_Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit Test1_Server(QWidget *parent = 0);
    ~Test1_Server();

signals:
   void sendMsg_signal( const QString &_msg );
   void rcvMsg_signal( const QString &_msg );

 public slots:
   void dbgMsg_slot( const QString &_msg );

private slots:
   void sendMsg_slot();
   void showMsg_slot( const QString &_sender, const QString &_msg );
   void clientConnected_slot( const QString &_name );
   void clientDisconnected_slot( const QString &_name );
   void stopComm_slot();

private:
   Ui::Test1_Server *ui;

   server_unit* mServer;
   QString mLocalName;
   QBluetoothLocalDevice* mLocalAdapter;
   QTimer* mTimer;

};
