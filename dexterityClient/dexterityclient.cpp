#include "dexterityclient.h"
#include "ui_dexterityclient.h"
#include <iostream>

#include "connectDialog.h"

/**
 * @brief Constructor
 * @param parent
 */
DexterityClient::DexterityClient(QWidget *parent) :
    QMainWindow(parent),
    mLocalAdapter(0),
    mClient(0),
    ui(new Ui::DexterityClient) {
    ui->setupUi(this);

    // Setting buttons initial state
    ui->disconnect_pushButton->setEnabled(false);

    // Button messages
    QObject::connect( ui->connect_pushButton, SIGNAL(clicked()),
                      this, SLOT(connect()) );
    QObject::connect( ui->disconnect_pushButton, SIGNAL(clicked()),
                      this, SLOT(disconnect()) );

    // Get local device
    QList<QBluetoothHostInfo>  adapters = QBluetoothLocalDevice::allDevices();
    if ( adapters.count() < 1) {
        ui->connect_pushButton->setEnabled(false);
        new QListWidgetItem( "[!] No local adapter found", ui->msgs_listWidget );
        return;
    }

    mLocalAdapter = new QBluetoothLocalDevice( adapters.at(0).address() );
    mLocalAdapter->setHostMode( QBluetoothLocalDevice::HostDiscoverable);

}

/**
 * @brief Destructor
 * @param parent
 */
DexterityClient::~DexterityClient() {

}

/**
 * @function connect
 */
void DexterityClient::connect(){

  connectDialog mCd( mLocalAdapter->address(), this );

  if( mCd.exec() == QDialog::Accepted ) {
     qDebug() << "Accepted cd!! \n";
    QBluetoothServiceInfo service = mCd.service();
    mClient = new client_unit(this);
     qDebug() << "Service name: "<< service.serviceName() << "\n";
    QObject::connect( mClient, SIGNAL( messageReceived(QString,QString)),
                      this, SLOT( receiveMsg( QString, QString)));

    QObject::connect( mClient, SIGNAL( disconnected()),
                      this, SLOT( clientDisconnected()));

    QObject::connect( this, SIGNAL( sendMessage(QString)),
                      mClient, SLOT(sendMsg(QString)));

    QString msg = QString("Connected to service %1").arg( service.serviceName() );
    new QListWidgetItem(msg, ui->msgs_listWidget );

    mClient->startClient(service);
  } else {
      qDebug() <<"No accepted cd \n";
  }
}

/**
 * @function disconnect
 */
void DexterityClient::disconnect() {

}

/**
 * @function showPlainMsg
 */
void DexterityClient::showPlainMsg( const QString &_msg ) {
  new QListWidgetItem( _msg, ui->msgs_listWidget );

}

/**
 * @function receiveMsg
 */
void DexterityClient::receiveMsg( const QString &_sender,
                                  const QString &_message ) {
printf("GOT A MESSAGE!!! \n");
  QString msg = QString("%1: %2").arg( _sender, _message );
  new QListWidgetItem( msg, ui->msgs_listWidget );

  std::string msg2; msg2 = _message.toStdString();
  std::cout << "Msg: "<< msg2<<std::endl;
/*
  if( msg.compare( "We are going to start\n" ) == 0 ) {
    printf("Start updates \n");
    startUpdate();
  } else if( msg.compare( " We are finishing!\n" ) == 0 ) {
    printf("Stop updates \n");
    stopUpdate();
  }
  */
}

void DexterityClient::sendMsg( const QString &_msg ) {

}

void DexterityClient::showMsg(const QString &_sender, const QString &_msg) {

}

void DexterityClient::clientDisconnected() {


}
