/***************************************************************************************************
 * Copyright 2023-2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of xTools project.
 *
 * xTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include "xToolsCommunicationToolUi.h"
#include <QLoggingCategory>

namespace Ui {
class SAKSocketServerToolUi;
}

class xToolsSocketServerTool;
class xToolsSocketServerToolUi : public xToolsCommunicationToolUi
{
    Q_OBJECT
public:
    explicit xToolsSocketServerToolUi(QWidget *parent = nullptr);
    ~xToolsSocketServerToolUi();
    virtual void onIsWorkingChanged(bool isWorking) final;
    virtual void onBaseToolUiInitialized(xToolsBaseTool *tool, const QString &settingsGroup) final;

private:
    xToolsSocketServerTool *mTool{nullptr};
    const QLoggingCategory mLoggingCategory{"sak.socketservertoolui"};

private:
    Ui::SAKSocketServerToolUi *ui{nullptr};

    void onComboBoxServerIpActived();
    void onSpinBoxServerPortValueChanged(int value);
    void onComboBoxClientsIndexChanged();
    void onComboBoxMessageTypeIndexChanged();
    void onCheckBoxSpecifyIpAndPortClicked();
};