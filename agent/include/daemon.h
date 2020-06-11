#ifndef DAEMON_H
#define DAEMON_H

#include <QObject>
#include <QString>
#include <QHash>

#include "pluginbase.h"

class sbc_agent : public QObject 
{
    Q_OBJECT
    public:
        sbc_agent(QObject *parent = nullptr);
        ~sbc_agent();
    private:
        QHash<QString, PluginBase *> m_Plugins;
        QRemoteObjectHost *m_rohost;
        QRemoteObjectRegistryHost * m_roregistryhost;
};

#endif