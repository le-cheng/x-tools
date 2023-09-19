﻿/******************************************************************************
 * Copyright 2018-2023 Qsaker(qsaker@foxmail.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 *****************************************************************************/
#include <QFile>
#include <QLoggingCategory>
#include <QStyleFactory>

#include "SAKApplication.h"
#include "SAKInterface.h"
#include "SAKLog.h"
#include "SAKSettings.h"

#ifdef SAK_IMPORT_MODULE_QML
#if QT_VERSION >= QT_VERSION_CHECK(6, 4, 0)
#include "SAKGuiApplication.h"
#endif
#endif

int main(int argc, char* argv[]) {
#ifndef QT_DEBUG
  qInstallMessageHandler(SAKLog::messageOutput);
#endif

  // Initialize some information about application.
  QCoreApplication::setOrganizationName(QString("Qsaker"));
  QCoreApplication::setOrganizationDomain(QString("IT"));
#ifdef SAK_RELEASE_FOR_APP_STORE
  QCoreApplication::setApplicationName(QString("QtSwissArmyKnife"));
#else
  QCoreApplication::setApplicationName(QString("QtSwissArmyKnife(Community)"));
#endif
#ifdef SAK_VERSION
  QCoreApplication::setApplicationVersion(SAK_VERSION);
#else
  QCoreApplication::setApplicationVersion("0.0.0");
#endif

  QLoggingCategory lc{"SAK.Main"};

  // Remove settings file and database
  if (SAKSettings::instance()->clearSettings()) {
    SAKSettings::instance()->setClearSettings(false);
    if (QFile::remove(SAKSettings::instance()->fileName())) {
      qCInfo(lc) << "Remove settings file successfully.";
    } else {
      qCWarning(lc) << "Remove settings file failed!";
    }
  }

  qCInfo(lc) << "Supported style:" << QStyleFactory::keys();

  // High dpi settings.
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
  int policy = SAKSettings::instance()->hdpiPolicy();
  if (SAKInterface::isQtHighDpiScalePolicy(policy)) {
    auto cookedPolicy = Qt::HighDpiScaleFactorRoundingPolicy(policy);
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(cookedPolicy);
  }
#endif

#ifdef SAK_IMPORT_MODULE_QML
  int uiType = SAKSettings::instance()->uiType();
#else
  int ui_type = SAKSettings::UiTypeWidget;
#endif

  // Startup application.
  if (ui_type == SAKSettings::UiTypeWidget) {
    QString style = SAKSettings::instance()->appStyle();
    if (!style.isEmpty() && QStyleFactory::keys().contains(style)) {
      qCInfo(lc) << "App style:" << style;
      QApplication::setStyle(QStyleFactory::create(style));
    }

    SAKApplication app(argc, argv);
    SAKLog::instance()->start();
    return app.exec();
  }

#ifdef SAK_IMPORT_MODULE_QML
#if QT_VERSION >= QT_VERSION_CHECK(6, 4, 0)
  SAKGuiApplication app(argc, argv);
  SAKLog::instance()->start();
  return app.exec();
#else
  SAKSettings::instance()->setUiType(SAKSettings::UiTypeWidget);
  qCInfo(lc) << "To using qml ui, please using qt 6.4.0 or later!";
  return 0;
#endif
#endif
  return 0;
}