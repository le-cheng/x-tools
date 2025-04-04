/***************************************************************************************************
 * Copyright 2022-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of xTools project.
 *
 * xTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <QMap>
#include <QWidget>

namespace Ui {
class AsciiAssistant;
}

class AsciiAssistant : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE AsciiAssistant(QWidget* parent = Q_NULLPTR);
    ~AsciiAssistant();

private:
    Ui::AsciiAssistant* ui;
    QMap<int, QString> m_descirption;

private:
    void initDescirption();
    void setupFilter(const QString& text);
};
