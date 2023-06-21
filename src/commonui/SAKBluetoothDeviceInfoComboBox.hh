﻿/******************************************************************************
 * Copyright 2023 Qsaker(wuuhaii@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 *****************************************************************************/
#ifndef SAKBLUETOOTHDEVICEINFOCOMBOBOX_HH
#define SAKBLUETOOTHDEVICEINFOCOMBOBOX_HH

#include "SAKComboBox.hh"
#include "SAKBleScanner.hh"

class SAKBluetoothDeviceInfoComboBox : public SAKComboBox
{
public:
    SAKBluetoothDeviceInfoComboBox(QWidget *parent = Q_NULLPTR);
    ~SAKBluetoothDeviceInfoComboBox();
    void startDiscover();
    void stopDiscover();
    bool isActive();
    void setTimeoutInterval(int interval);
    void setNameFiltter(const QString &filtter);

private:
    SAKBleScanner *mScanner;
};

#endif // SAKBLUETOOTHDEVICEINFOCOMBOBOX_HH