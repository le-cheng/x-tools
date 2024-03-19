/***************************************************************************************************
 * Copyright 2023-2024 Qsaker(qsaker@foxmail.com). All rights reserved.
 *
 * The file is encoded in "utf8 with bom", it is a part of QtSwissArmyKnife project.
 *
 * xTools is licensed according to the terms in the file LICENCE in the root of the source code
 * directory.
 **************************************************************************************************/
#ifndef XTOOLSMAINWINDOW_H
#define XTOOLSMAINWINDOW_H

#include <QActionGroup>
#include <QApplication>
#include <QLoggingCategory>
#include <QMainWindow>
#include <QMenu>
#include <QStyleFactory>

class xToolsMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    xToolsMainWindow(QWidget* parent = Q_NULLPTR);
    ~xToolsMainWindow();

protected:
    QMenu* m_fileMenu;
    QMenu* m_optionMenu;
    QMenu* m_languageMenu;
    QMenu* m_helpMenu;

private:
    QActionGroup* m_appStyleActionGroup;
    QActionGroup* m_languageActionGroup;

private:
    void init();
    void initMenu();
    void initMenuFile();
    void initMenuOption();
    void initMenuLanguage();
    void initMenuHelp();

    void initOptionMenuAppStyleMenu();
    void initOptionMenuSettingsMenu();
    void initOptionMenuHdpiPolicy();

    void onHdpiPolicyActionTriggered(int policy);
    void onGithubActionTriggered();
    void onGiteeActionTriggered();
    void onUserQqGroupTriggerd();
    void onAboutActionTriggered();

    void tryToReboot();
    void createQtConf();
    QString getQtConfFileName();
};

#endif // XTOOLSMAINWINDOW_H