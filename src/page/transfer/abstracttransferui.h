/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of xTools project.
 *
 * xTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <QHeaderView>

#include "page/common/abstractmodelui.h"

class AbstractTransferUi : public AbstractModelUi
{
    Q_OBJECT
public:
    explicit AbstractTransferUi(QWidget *parent = nullptr);
    ~AbstractTransferUi() override;
};
