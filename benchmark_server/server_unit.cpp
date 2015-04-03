
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
 */
server_unit::~server_unit() {
    stop();
}

/**
 * @brief server_unit::start
 * @param _localAdapter
 */
void server_unit::start( const QBluetoothAddress &_localAdapter ) {
    if( mRfcommServer ) {
        return; // Already server service is ON
    }
    qDebug()<< "Starting server... ";
    // Create the server
    mRfcommServer = new QBluetoothServer( QBluetoothServiceInfo::RfcommProtocol, this );
    this->connect( mRfcommServer, SIGNAL(newConnection()), this, SLOT(clientConnected()) );
    bool result = mRfcommServer->listen( _localAdapter );
    if( !result ) {
        qDebug() << "Cannot bind RFCOMM server to local adapter";
    }

    // Set service info
    mServiceInfo.setAttribute(QBluetoothServiceInfo::ServiceName, tr("Crichton Server"));
    mServiceInfo.setAttribute(QBluetoothServiceInfo::ServiceDescription, tr("Crichton control machine listening"));
    mServiceInfo.setAttribute(QBluetoothServiceInfo::ServiceProvider, tr("golems.org"));
    QBluetoothServiceInfo::Sequence publicBrowse;
    publicBrowse << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::PublicBrowseGroup));
    mServiceInfo.setAttribute(QBluetoothServiceInfo::BrowseGroupList, publicBrowse);

    QBluetoothServiceInfo::Sequence classId;

    classId << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::SerialPort));
    mServiceInfo.setAttribute(QBluetoothServiceInfo::BluetoothProfileDescriptorList,
                             classId);

    classId.prepend(QVariant::fromValue(QBluetoothUuid(serviceUuid)));

    mServiceInfo.setAttribute(QBluetoothServiceInfo::ServiceClassIds, classId);
    mServiceInfo.setAttribute(QBluetoothServiceInfo::BluetoothProfileDescriptorList,classId);

    mServiceInfo.setServiceUuid(QBluetoothUuid(serviceUuid));


    QBluetoothServiceInfo::Sequence protocolDescriptorList;
    QBluetoothServiceInfo::Sequence protocol;
    protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::L2cap));
    protocolDescriptorList.append(QVariant::fromValue(protocol));
    protocol.clear();
    protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::Rfcomm))
             << QVariant::fromValue(quint8(mRfcommServer->serverPort()));
    protocolDescriptorList.append(QVariant::fromValue(protocol));
    mServiceInfo.setAttribute(QBluetoothServiceInfo::ProtocolDescriptorList,
                             protocolDescriptorList);


    mServiceInfo.registerService( _localAdapter );
    qDebug()<<"Finished setting up server" ;
}

void server_unit::stop() {
    // Unregister service
    mServiceInfo.unregisterService();
    // Close Sockets
    qDeleteAll( mClientSockets );
    // Close server
    delete mRfcommServer;
    mRfcommServer = 0;
}

void server_unit::sendFeedback() {

}

void server_unit::clientConnected() {

}

void server_unit::clientDisconnected() {

}

void server_unit::readSocket() {

}
