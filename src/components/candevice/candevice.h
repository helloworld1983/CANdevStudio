#ifndef __CANDEVICE_H
#define __CANDEVICE_H

#include <QScopedPointer>
#include <QtCore/QObject>
#include <QtSerialBus/QCanBusDevice>
#include <QtSerialBus/QCanBusFrame>

class CanDevicePrivate;
struct CanFactoryInterface;

class CanDevice : public QObject {
    Q_OBJECT
    Q_DECLARE_PRIVATE(CanDevice)

public:
    CanDevice(CanFactoryInterface& factory);
    ~CanDevice();
    bool init(const QString& backend, const QString& iface);
    bool start();

Q_SIGNALS:
    void frameReceived(const QCanBusFrame& frame);
    void frameSent(bool status, const QCanBusFrame& frame, const QVariant& context);

public Q_SLOTS:
    void sendFrame(const QCanBusFrame& frame, const QVariant& context);

private Q_SLOTS:
    void errorOccurred(int error);
    void framesWritten(qint64 framesCnt);
    void framesReceived();

private:
    QScopedPointer<CanDevicePrivate> d_ptr;
    CanFactoryInterface& mFactory;
};

#endif /* !__CANDEVICE_H */
