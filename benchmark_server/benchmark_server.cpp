#include "benchmark_server.h"
#include "ui_benchmark_server.h"

/**
 * @brief Constructor
 * @param parent
 */
benchmark_server::benchmark_server(QWidget *parent) :
    QMainWindow(parent),
    mLocalAdapter(0),
    mServer(0),
    ui(new Ui::benchmark_server)
{
    ui->setupUi(this);

    // Start and stop buttons
    QObject::connect( ui->start_pushButton, SIGNAL(clicked()),
                      this, SLOT(sendStartMsg()) );
    QObject::connect( ui->stop_pushButton, SIGNAL(clicked()),
                      this, SLOT(sendStopMsg()) );

    // Get local adapter
    QList<QBluetoothHostInfo> adapters;
    adapters = QBluetoothLocalDevice::allDevices();
    mLocalAdapter = new QBluetoothLocalDevice( adapters.at(0).address() );
    mLocalAdapter->setHostMode( QBluetoothLocalDevice::HostDiscoverable);

    // Create server
    mServer = new server_unit(this);

    this->connect( mServer, SIGNAL(clientConnected(QString)),
                   this, SLOT( clientConnected(QString)) );
    this->connect( mServer, SIGNAL(messageReceived(QString, QString)),
                   this, SLOT(showMessage(QString, QString)));
    this->connect( this, SIGNAL(sendMessage(QString)),
                   mServer, SLOT(sendMessage(QString)) );
    // Start server
    mServer->startServer(mLocalAdapter->address() );

    // Get local device name
    mLocalName = QBluetoothLocalDevice().name();

}

benchmark_server::~benchmark_server()
{
    delete ui;
}

/**
 * @brief benchmark_server::clientConnected
 * @param _name
 */
void benchmark_server::clientConnected( const QString &_name ) {

    QString msg =QString( "A connection with %1 is ON").arg(_name);

    ui->msgs_label->setText( msg );
}

/**
 * @function showMessage
 */
void benchmark_server::showMessage( const QString &_sender, const QString &_message )  {
    QString msg = QString("Msg from %1 : %2").arg( _sender, _message );
    ui->msgs_label->setText( msg );
}

/**
 * @brief benchmark_server::sendStartMsg
 */
void benchmark_server::sendStartMsg() {
   ui->msgs_label->setText("Sending message start \n");
   emit sendMessage( "Start" );
}

/**
 * @brief benchmark_server::sendStopMsg
 */
void benchmark_server::sendStopMsg() {
    ui->msgs_label->setText("Sending message stop \n");
    emit sendMessage( "Stop" );

}
