#pragma once

#include <QtBluetooth/QBluetoothServer>
#include <QtBluetooth/QBluetoothSocket>

class server_unit : public QObject {
    Q_OBJECT

public:
    explicit server_unit( QObject* parent  = 0 );
    ~server_unit();

    void startServer( const QBluetoothAddress &_localAdapter = QBluetoothAddress() );
    void stopServer();

public slots:
    void sendMessage( const QString &_message );

signals:
    void messageReceived( const QString &_sender,
                          const QString _msg );
    void clientConnected( const QString &_name );
    void clientDisconnected( const QString &_name );

private slots:
    void clientConnected();
    void clientDisconnected();
    void readSocket();

private:
    QBluetoothServer *mRfcommServer;
    QBluetoothServiceInfo mServiceInfo;
    QBluetoothSocket* mClientSocket;
};
