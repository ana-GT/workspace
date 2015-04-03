#include "benchmark_server.h"
#include "ui_benchmark_server.h"

benchmark_server::benchmark_server(QWidget *parent) :
    QMainWindow(parent),
    mLocalAdapter(0),
    mServer(0),
    ui(new Ui::benchmark_server)
{
    ui->setupUi(this);

    QList<QBluetoothHostInfo> adapters;
    adapters = QBluetoothLocalDevice::allDevices();
    mLocalAdapter = new QBluetoothLocalDevice( adapters.at(0).address() );
    mLocalAdapter->setHostMode( QBluetoothLocalDevice::HostDiscoverable);

    // Create server
    mServer = new server_unit(this);
    //this->connect( mServer, SIGNAL(clientConnected(QString)),
    //               this, SLOT( onClientConnected(QString)) );
    // Start server
    mServer->start(mLocalAdapter->address() );

}

benchmark_server::~benchmark_server()
{
    delete ui;
}
