#include "pluginbase.h"

PluginBase::PluginBase(QObject *parent) :
    QObject(parent)
{

}
PluginBase::~PluginBase() 
{

}

void PluginBase::startTimer() 
{
    connect(&this->m_updateTimer, &QTimer::timeout, this, &PluginBase::update);
    this->m_updateTimer.setInterval(1000);
    this->m_updateTimer.start();
}