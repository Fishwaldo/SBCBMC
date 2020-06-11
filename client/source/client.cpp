#include "client.hpp"

SBCBMCClient::SBCBMCClient(QObject *parent) :
    QObject(parent)
{
     this->engine = new QQmlApplicationEngine("qrc:///qml/main.qml");
}

SBCBMCClient::~SBCBMCClient() 
{

}

#if 0
    QRemoteObjectNode node(QUrl("tcp://127.0.0.1:1999"));

    QObject::connect(&node, &QRemoteObjectNode::remoteObjectAdded,
                     [](const QRemoteObjectSourceLocation& info){
        qDebug() << "New source added : " << info;
    });

    qDebug() << "Waiting for registry ";
    node.waitForRegistry(10000);

    qDebug() << "Already here sources : " << node.registry()->sourceLocations();

    QTimer timer;
    timer.start(5000);

    QObject::connect(&timer, &QTimer::timeout,
                     [&](){
        qDebug() << "New sources list : " << node.registry()->sourceLocations();
    });

    QRemoteObjectDynamicReplica *plugin = node.acquireDynamic("plugins/thermal/thermal_zone1/x86_pkg_temp");
    QRemoteObjectDynamicReplica *plugin2 = node.acquireDynamic("plugins/thermal/thermal_zone0/x86_pkg_temp");

#endif