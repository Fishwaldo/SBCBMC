#ifndef DCDC_USB_200_H
#define DCDC_USB_200_H

#include <usb.h>
#include <QVariant>

#include "pluginbase.h"
#include "rep_dcdc_usb_200_source.h"

class DCDCUSB200_Properties : public DCDCUSB200_PropertiesSimpleSource {
    Q_OBJECT
    public:
        DCDCUSB200_Properties(QObject *parent = nullptr);
        ~DCDCUSB200_Properties();
        bool parsePacket(quint8 *data, int size);
};


class DCDCUSB200 : public PluginBase {
    Q_OBJECT
    public:
        DCDCUSB200(QObject *parent = nullptr);
        ~DCDCUSB200();
        bool initilize() override;
        void update() override;
    public Q_SLOTS:
        void printUpdate(QVariant);
    public Q_SLOTS:
        bool registerSource(QRemoteObjectHostBase *host);

    private:
        struct usb_dev_handle *m_usb_handle;
        DCDCUSB200_Properties m_properties;
};

#endif