#include "daemon.h"
#include "dcdc-usb-200.h"
#include "thermal.h"

sbc_agent::sbc_agent(QObject *parent) :
    QObject(parent)
{
    this->m_roregistryhost = new QRemoteObjectRegistryHost(QUrl("tcp://0.0.0.0:1999"), this);
    this->m_rohost = new QRemoteObjectHost(QUrl("tcp://0.0.0.0:1998"), QUrl("tcp://127.0.0.1:1999"), QRemoteObjectHostBase::BuiltInSchemasOnly, this);



    DCDCUSB200 *dcdcusb200 = new DCDCUSB200(this);
    if (dcdcusb200->initilize()) {
        this->m_Plugins.insert("DCDCUSB200", dcdcusb200);
        dcdcusb200->registerSource(this->m_rohost);
    }
    Thermal *thermal = new Thermal(this);
    if (thermal->initilize()) {
        this->m_Plugins.insert("Thermal", thermal);
        thermal->registerSource(this->m_rohost);
    }
}

sbc_agent::~sbc_agent() 
{

}