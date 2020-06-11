#include <QDebug>
#include <QMetaObject>
#include <QMetaMethod>
#include <QDir>

#include "thermal.h"


Thermal::Thermal(QObject *parent) :
    PluginBase(parent)
{

}
Thermal::~Thermal() 
{

}

bool Thermal::initilize() 
{
    QDir sysclass("/sys/class/thermal/");
    QStringList thermals = sysclass.entryList(QStringList() << "thermal_zone*", QDir::Dirs);
    foreach(QString directory, thermals) {
        /* Get the name for this Thermal class */
        QFile thermal("/sys/class/thermal/"+directory+"/type");
        if (!thermal.exists())
        {
            qWarning() << "Thermal Type Entry does not Exist for " << directory;
            continue;
        }
        if (!thermal.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qWarning() << "Can Not Open Thermal Type Entry for " << directory;
            continue;
        }
        QString name = thermal.readLine();
        Thermal_Properties *tp = new Thermal_Properties(directory+"/"+name.simplified(), this);
        tp->setDirectory(QDir("/sys/class/thermal/"+directory));
        this->m_properties.insert(directory+"/"+name.simplified(), tp);
        connect(tp, &Thermal_Properties::tempChanged, this, &Thermal::printUpdate);
    }
    this->startTimer();
    return true;
}

void Thermal::update() 
{
    foreach(Thermal_Properties *tp, this->m_properties) {
        QFile temp(tp->getDirectory().absoluteFilePath("temp"));

        if (!temp.exists()) {
            qWarning() << "Temp Entry for " << tp->name() << " doesn't exist";
            continue;
        }
        if (!temp.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qWarning() << "Can't Open Temp File for " << tp->name();
            continue;
        }
        QString value = temp.readLine().simplified();
        tp->processPacket(value);
    }
}

void Thermal::printUpdate(QVariant data) {
    QObject *sender = QObject::sender();
    int signalindex = QObject::senderSignalIndex();
    const QMetaObject *mo = sender->metaObject();
    qInfo() << "Changed Single: " << sender->objectName() <<  QString::fromLatin1(mo->method(signalindex).methodSignature()) << data.toString();
}

bool Thermal::registerSource(QRemoteObjectHostBase *host) {
    bool ret = false;
    foreach(Thermal_Properties *tp, this->m_properties) {
        ret |= host->enableRemoting(tp, "plugins/thermal/"+tp->name().toString());
    }
    return ret;
}



Thermal_Properties::Thermal_Properties(QString name, QObject *parent) :
    Thermal_PropertiesSimpleSource(parent)
{
    this->setObjectName(name);
    this->setName(name);
    qDebug() << "New Thermal Property Found: " << name;
}
Thermal_Properties::~Thermal_Properties() 
{

}
void Thermal_Properties::setDirectory(QDir directory) 
{
    this->m_directory = directory;
}

void Thermal_Properties::processPacket(QVariant data) 
{
    this->setTemp(data.toInt() * 0.001);
}
