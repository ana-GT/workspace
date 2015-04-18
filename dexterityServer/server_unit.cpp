
#include "server_unit.h"
static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c8");
/**
 * @brief server_unit::server_unit
 * @param parent
 */
server_unit::server_unit( QObject* parent ) :
 QObject(parent), mRfcommServer(0) {

}

/**
 * @brief server_unit::~server_unit
 * @param
 */
server_unit::~server_unit() {
    stopServer();
}

/**
 * @brief server_unit::start
 * @param _localAdapter
 */
void server_unit::startServer( const QBluetoothAddress &_localAdapter ) {
    if( mRfcommServer ) {
        return;
    }

   // Create the server
    mRfcommServer = new QBluetoothServer( QBluetoothServiceInfo::RfcommProtocol, this );
    this->connect( mRfcommServer, SIGNAL(newConnection()),
                   this, SLOT(clientConnected_slot()) );
    bool result = mRfcommServer->listen( _localAdapter );
    if( !result ) {
        emit dbgMsg_signal("[SU] Cannot bind RFCOMM server to local adapter \n");
    }


    // Set service info
    mServiceInfo.setAttribute(QBluetoothServiceInfo::ServiceName, tr("Crichton Server"));
    mServiceInfo.setAttribute(QBluetoothServiceInfo::ServiceDescription, tr("Control machine service"));
    mServiceInfo.setAttribute(QBluetoothServiceInfo::ServiceProvider, tr("golems.org"));
    QBluetoothServiceInfo::Sequence publicBrowse;
    publicBrowse << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::PublicBrowseGroup));
    mServiceInfo.setAttribute(QBluetoothServiceInfo::BrowseGroupList, publicBrowse);

    QBluetoothServiceInfo::Sequence classId;

    classId << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::SerialPort));
    //mServiceInfo.setAttribute(QBluetoothServiceInfo::BluetoothProfileDescriptorList,
     //                        classId);

    classId.prepend(QVariant::fromValue(QBluetoothUuid(serviceUuid)));

    mServiceInfo.setAttribute(QBluetoothServiceInfo::ServiceClassIds, classId);
    mServiceInfo.setAttribute(QBluetoothServiceInfo::BluetoothProfileDescriptorList,classId);

    mServiceInfo.setServiceUuid(QBluetoothUuid(serviceUuid));


    QBluetoothServiceInfo::Sequence protocolDescriptorList;
    QBluetoothServiceInfo::Sequence protocol;
    protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::Rfcomm))
             << QVariant::fromValue(quint8(mRfcommServer->serverPort()));
    protocolDescriptorList.append(QVariant::fromValue(protocol));
    mServiceInfo.setAttribute(QBluetoothServiceInfo::ProtocolDescriptorList,
                             protocolDescriptorList);

    mServiceInfo.registerService( _localAdapter );

}

/**
 * @function stopServer
 */
void server_unit::stopServer() {
    // Unregister service
    mServiceInfo.unregisterService();
    // Close Sockets
    mClientSocket->close();
    // Close server
    delete mRfcommServer;
    mRfcommServer = 0;
}

/**
 * @brief server_unit::sendMessage
 * @param _msg
 */
void server_unit::sendMsg_slot( const QString &_msg ) {
    QByteArray text = _msg.toUtf8() + '\n';

    if( mClientSocket->write( text ) < 0 ) {
        emit dbgMsg_signal("SERVER UNIT: ERROR WRITING TO SOCKET");
    }
}

/**
 * @function clientConnected
 */
void server_unit::clientConnected_slot() {

    mClientSocket = mRfcommServer->nextPendingConnection();
    if( !mClientSocket ) { return; }

    QObject::connect( mClientSocket, SIGNAL(readyRead), this, SLOT(readSocket_slot()) );
    QObject::connect( mClientSocket, SIGNAL(disconnected), this, SLOT(clientDisconnected_slot()) );

    emit clientConnected_signal( mClientSocket->peerName() );
}

/**
 * @brief server_unit::clientDisconnected
 */
void server_unit::clientDisconnected_slot() {

        QBluetoothSocket* socket = qobject_cast<QBluetoothSocket*>( sender() );
        if( !socket ) { return; }

        emit clientDisconnected_signal( socket->peerName() );
        socket->deleteLater();

}

/**
 * @brief server_unit::readSocket
 */
void server_unit::readSocket_slot() {

        // In our case we only have one socket mSocket, so this is not really necessary
       QBluetoothSocket* socket = qobject_cast<QBluetoothSocket*>( sender() );
        if( !socket ) { return; }

        while( socket->canReadLine() ) {
            QByteArray line = socket->readLine().trimmed();
            emit rcvMsg_signal( socket->peerName(),
                                QString::fromUtf8(line.constData(), line.length()));
        }

}
