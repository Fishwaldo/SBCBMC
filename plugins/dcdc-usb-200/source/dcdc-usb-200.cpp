#include <QDebug>
#include <QMetaObject>
#include <QMetaMethod>

#include "dcdc-usb-200.h"

extern "C" { 

    #include "dcdc-usb.h"

}

DCDCUSB200::DCDCUSB200(QObject *parent) :
    PluginBase(parent)
{

}
DCDCUSB200::~DCDCUSB200() 
{

}

bool DCDCUSB200::initilize() 
{
    m_usb_handle = dcdc_connect();
    if (m_usb_handle == NULL) {
        qWarning() << "DCDCUSB200 - Can't Open USB Handle";
        return false;
    }
    if (dcdc_setup(m_usb_handle) < 0) {
        qWarning() << "DCDCUSB200 - Can't Setup Device";
        return false;
    }
    connect(&this->m_properties, &DCDCUSB200_Properties::modeChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::timeConfigChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::voltageConfigChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::stateChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::vInChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::vIgnitionChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::vOutChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::powerSwitchChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::outputEnableChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::auxVInEnableChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::statusFlags1Changed, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::statusFlags2Changed, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::voltageFlagsChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::timerFlagsChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::flashPointerChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::timerWaitChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::timerVOutChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::timerVAuxChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::timerPwSwitchChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::timerOffDelayChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::timerHardOffDelayChanged, this, &DCDCUSB200::printUpdate);
    connect(&this->m_properties, &DCDCUSB200_Properties::firmwareVersionChanged, this, &DCDCUSB200::printUpdate);

    this->startTimer();
    return true;
}

void DCDCUSB200::update() 
{
    unsigned char data[MAX_TRANSFER_SIZE];
    int ret = dcdc_get_status(m_usb_handle, data, MAX_TRANSFER_SIZE);
    if (ret <= 0) {
        qWarning() << "DCDCUSB200 - Failed To Get Status from Device";
        return;
    }
    this->m_properties.parsePacket(data, ret);
    //dcdc_parse_data(data, ret);
    qDebug() << "";
}


void DCDCUSB200::printUpdate(QVariant data) {
    QObject *sender = QObject::sender();
    int signalindex = QObject::senderSignalIndex();
    const QMetaObject *mo = sender->metaObject();
    qInfo() << "Changed Single: " << QString::fromLatin1(mo->method(signalindex).methodSignature()) << data;
}

bool DCDCUSB200::registerSource(QRemoteObjectHostBase *host) {
    return host->enableRemoting(&this->m_properties, "plugins/DCDCUSB200");
}



DCDCUSB200_Properties::DCDCUSB200_Properties(QObject *parent) :
    DCDCUSB200_PropertiesSimpleSource(parent)
{

}
DCDCUSB200_Properties::~DCDCUSB200_Properties() 
{

}

bool DCDCUSB200_Properties::parsePacket(quint8 *data, int size) {
    double value;
    
    this->setMode((data[1] & 0x03));
    this->setState(data[2]);
    this->setVIn((double) data[3] * 0.1558f);
    this->setVIgnition((double) data[4] * 0.1558f);
    this->setVOut((float) data[5] * 0.1170f);
    this->setStatusFlags1(data[6]);
    this->setTimeConfig((data[1] >> 5) & 0x07);
    this->setVoltageConfig((data[1] >> 2) & 0x07);
    this->setPowerSwitch((data[6] & 0x04) ? true : false);
    this->setOutputEnable((data[6] & 0x08) ? true : false);
    this->setAuxVInEnable((data[6] & 0x10) ? true : false);
    this->setStatusFlags2(data[7]);
    this->setVoltageFlags(data[8]);
    this->setTimerFlags(data[9]);
    this->setFlashPointer(data[10]);
    this->setTimerWait((data[11] << 8) | data[12]);
    this->setTimerVOut((data[13] << 8) | data[14]);
    this->setTimerVAux((data[15] << 8) | data[16]);
    this->setTimerPwSwitch((data[17] << 8) | data[18]);
    this->setTimerOffDelay((data[19] << 8) | data[20]);
    this->setTimerHardOffDelay((data[21] << 8) | data[22]);
    QString version("%1.%2");
    this->setFirmwareVersion(version.arg(((data[23] >> 5) & 0x07)).arg((data[23] & 0x1F)));
    return true;
}
