#ifndef THERMAL_H
#define THERMAL_H

#include <QDir>

#include "pluginbase.h"
#include "rep_thermal_source.h"

class Thermal_Properties : public Thermal_PropertiesSimpleSource {
    Q_OBJECT
    public:
        Thermal_Properties(QString name, QObject *parent = nullptr);
        ~Thermal_Properties();
        Q_PROPERTY(QDir directory READ getDirectory WRITE setDirectory);

        QDir getDirectory() { return this->m_directory; }
        void processPacket(QVariant);
    public Q_SLOTS:
        void setDirectory(QDir directory);
    private:
        QDir m_directory;
};


class Thermal : public PluginBase {
    Q_OBJECT
    public:
        Thermal(QObject *parent = nullptr);
        ~Thermal();
        bool initilize() override;
        void update() override;
    public Q_SLOTS:
        void printUpdate(QVariant);
        bool registerSource(QRemoteObjectHostBase *host) override;
    private:
        QHash<QString, Thermal_Properties*> m_properties;
};

#endif