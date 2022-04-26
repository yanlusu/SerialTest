﻿#ifndef DEVICETAB_H
#define DEVICETAB_H

#include <QWidget>
#include <QBluetoothHostInfo>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QSerialPortInfo>
#include <QSerialPort>

#include "mysettings.h"
#include "connection.h"

namespace Ui
{
class DeviceTab;
}

class DeviceTab : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceTab(QWidget *parent = nullptr);
    ~DeviceTab();

    void initSettings();
    void setConnection(Connection* conn);
public slots:
    void refreshTargetList();
    void saveDevicesPreference(const QString &deviceName);
    void getAvailableTypes(bool useFirstValid = false);
private:
    Ui::DeviceTab *ui;

    MySettings* settings;
    Connection* m_connection = nullptr;

    QBluetoothDeviceDiscoveryAgent *BTClient_discoveryAgent = nullptr;

    void loadDevicesPreference(const QString &id);

    void initUI();
#ifdef Q_OS_ANDROID
    void getBondedTarget(bool isBLE);
#endif
    void setBTClientDiscoveryAgent(QBluetoothAddress adapterAddress = QBluetoothAddress());
signals:
    void updateStatusBar();
    void connTypeChanged(Connection::Type type);
private slots:
    void on_SP_advancedBox_clicked(bool checked);
    void on_openButton_clicked();
    void on_closeButton_clicked();
    void onTargetListCellClicked(int row, int column);

    void BTdiscoverFinished();
    void BTdeviceDiscovered(const QBluetoothDeviceInfo &device);
    void on_typeBox_currentIndexChanged(int index);
    void on_refreshButton_clicked();
    void on_BTClient_adapterBox_activated(int index);
    void on_BTServer_serviceNameEdit_editingFinished();
    void on_BTServer_adapterBox_activated(int index);
};

#endif // DEVICETAB_H
