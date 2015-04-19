/**
 * @file test1_server.cpp
 */

#include "test1_server.h"
#include "ui_test1_server.h"
#include <QListWidget>
#include <QListWidgetItem>

/**
 * @brief Constructor
 * @param parent
 */
Test1_Server::Test1_Server(QWidget *parent) :
    QMainWindow(parent),
    mLocalAdapter(0),
    mServer(0),
    ui(new Ui::Test1_Server)
{
    ui->setupUi(this);

    // Button messages
    QObject::connect( ui->maydayTest_pushButton, SIGNAL(clicked()),
                      this, SLOT(sendMsg_slot()) );
    QObject::connect( ui->stopComm_pushButton, SIGNAL(clicked()),
                      this, SLOT(stopComm_slot()) );

    // Get local adapter
    QList<QBluetoothHostInfo> adapters;
    adapters = QBluetoothLocalDevice::allDevices();
    mLocalAdapter = new QBluetoothLocalDevice( adapters.at(0).address() );
    mLocalAdapter->setHostMode( QBluetoothLocalDevice::HostDiscoverable);

    // Create server
    mServer = new server_unit(this);

    this->connect( mServer, SIGNAL(clientConnected_signal(QString)),
                   this, SLOT( clientConnected_slot(QString)) );
    this->connect( mServer, SIGNAL(clientDisconnected_signal(QString)),
                   this, SLOT( clientDisconnected_slot(QString)) );
    this->connect( mServer, SIGNAL(rcvMsg_signal(QString, QString)),
                   this, SLOT( showMsg_slot(QString, QString)));
    this->connect( this, SIGNAL(sendMsg_signal(QString)),
                   mServer, SLOT(sendMsg_slot(QString)) );

    this->connect( mServer, SIGNAL(dbgMsg_signal(QString)),
                   this, SLOT(dbgMsg_slot(QString)) );


    // Start server
    mServer->startServer(mLocalAdapter->address() );

    // Get local device name
    mLocalName = QBluetoothLocalDevice().name();

}

void Test1_Server::stopComm_slot() {
    // Stop server
    mServer->stopServer();
}

/**
 * @function dbgMsg_slot
 */
void Test1_Server::dbgMsg_slot( const QString &_msg ) {

    new QListWidgetItem( _msg, ui->msgs_listWidget );
}


Test1_Server::~Test1_Server()
{
    delete ui;
}

/**
 * @function showMessage_slot
 */
void Test1_Server::showMsg_slot( const QString &_sender, const QString &_message )  {
    QString msg = QString("%1 : %2").arg( _sender, _message );
    new QListWidgetItem( msg, ui->msgs_listWidget );
}

/**
 * @brief clientConnected_slot
 */
void Test1_Server::clientConnected_slot( const QString &_name ) {

    QString msg =QString( "%1: Connected to this server").arg(_name);
    new QListWidgetItem( msg, ui->msgs_listWidget );
}

/**
 * @brief clientDisconnected_slot
 */
void Test1_Server::clientDisconnected_slot( const QString &_name ) {

    QString msg =QString( "%1: Disconnected to this server").arg(_name);
    new QListWidgetItem( msg, ui->msgs_listWidget );
}

/**
 * @brief sendMsg_slot
 */
void Test1_Server::sendMsg_slot() {

   QObject* obj = sender();

   if( obj == ui->maydayTest_pushButton ) {
     new QListWidgetItem( tr("Sent: Mayday test"), ui->msgs_listWidget );
     emit sendMsg_signal( "Mayday test" );
   }

}
