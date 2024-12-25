﻿/***************************************************************************************************
 * Copyright 2023-2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of xTools project.
 *
 * xTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <functional>
#include <type_traits>

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStyle>
#include <QStyleHints>

#include "./Application.h"
#include "./MainWindow.h"
#include "./Settings.h"

#ifdef X_TOOLS_ENABLE_MODULE_STYLESHEET
#include "StyleSheetManager.h"
#endif

static void xInitResources()
{
    Q_INIT_RESOURCE(xTools);
}

namespace xTools {

static void (*gOutputLog2Ui)(QtMsgType, const QMessageLogContext &, const QString &){nullptr};

void initGoogleLogging(char *argv0);
void shutdownGoogleLogging();
void qtLogToGoogleLog(QtMsgType type, const QMessageLogContext &context, const QString &msg);
void initApp(const QString &appName, bool forStore);
void installMessageHandler();
void tryToClearSettings();
void initHdpi();
void initAppStyle();
void doSomethingBeforeAppCreated(char *argv[], const QString &appName, bool forStore = false);
void doSomethingAfterAppExited();
void tryToRebootApp();

/**
 * \brief exec: Using this function to start the application with a main window, you can specified
 *  the central widget type of main window. If MainWindow is the same as CentralWidget, the
 *  main window will not be created and the instance of CentralWidget will be the main window.
 * \param argc: The number of command line arguments.
 * \param argv: The command line arguments.
 * \param appName: The name of the application.
 * \param version: The version of the application.
 * \param doSomethingBeforAppExec: The function will be called before the application exec. The
 * parameter of the function is the instance of the main window and the instance of the application.
 * \return
 */
/**
 * \brief exec: 使用此函数启动应用程序并指定主窗口的中心部件类型。如果主窗口与中心部件相同，
 * 则不会创建主窗口，而是将中心部件实例作为主窗口。
 * \param argc: 命令行参数的数量。
 * \param argv: 命令行参数数组。
 * \param appName: 应用程序的名称。
 * \param version: 应用程序的版本。
 * \param doSomethingBeforAppExec: 在应用程序执行前调用的函数。该函数的参数是主窗口实例和应用程序实例。
 * \return 返回值。
 */
template<typename CentralWidgetT, typename MainWindowT, typename ApplicationT>
int exec(int argc,
         char *argv[],
         const QString &appName,
         const QString &version = QString("0.0.0"),
         const std::function<void(void *, void *)> &doSomethingBeforAppExec = nullptr)
{
    QCoreApplication::setApplicationVersion(version);
    doSomethingBeforeAppCreated(argv, appName);

    ApplicationT app(argc, argv);
    app.setupLanguage();

    QStyleHints *styleHints = QApplication::styleHints();
    styleHints->setColorScheme(Qt::ColorScheme::Dark);

    const QString dtStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    Settings::instance()->setValue("startUpTime", dtStr);

#ifdef X_TOOLS_ENABLE_MODULE_STYLESHEET
    auto &styleSheetManager = StyleSheetManager::singleton();
    const QString styleSheet = styleSheetManager.styleSheet();
    if (!styleSheet.isEmpty() && !styleSheetManager.currentTheme().isEmpty()) {
        app.setStyleSheet(styleSheet);
    }
#endif

    initAppStyle();

    QWidget *ui;
    if (std::is_same<CentralWidgetT, MainWindowT>::value) {
        auto widget = new CentralWidgetT();
        ui = widget;
    } else {
        auto mainWindow = new MainWindowT();
        auto centralWidget = new CentralWidgetT(mainWindow);
        mainWindow->setWindowTitle(appName);
        mainWindow->setCentralWidget(centralWidget);
        ui = mainWindow;
    }

    QSplashScreen &splashScreen = app.splashScreen();
    splashScreen.finish(ui);
    ui->show();
    ui->resize(static_cast<int>(static_cast<qreal>(ui->height()) * 1.732), ui->height());
    Application::moveToScreenCenter(ui);
    qInfo() << "The size of window is" << ui->size();

    if (doSomethingBeforAppExec) {
        doSomethingBeforAppExec(ui, &app);
    }

    const int ret = app.exec();
    doSomethingAfterAppExited();
    return ret;
}

template<typename CentralWidget>
int execCentralWidget(int argc,
                      char *argv[],
                      const QString &appName,
                      const QString &version = QString("0.0.0"),
                      const std::function<void(void *, void *)> &doSomethingBeforAppExec = nullptr)
{
    xInitResources();
    return xTools::exec<CentralWidget, xTools::MainWindow, xTools::Application>(
        argc, argv, appName, version, doSomethingBeforAppExec);
}

} // namespace xTools
