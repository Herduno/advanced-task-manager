/********************************************************************************
** Form generated from reading UI file 'advancedsystemmonitor.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADVANCEDSYSTEMMONITOR_H
#define UI_ADVANCEDSYSTEMMONITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdvancedSystemMonitorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AdvancedSystemMonitorClass)
    {
        if (AdvancedSystemMonitorClass->objectName().isEmpty())
            AdvancedSystemMonitorClass->setObjectName(QStringLiteral("AdvancedSystemMonitorClass"));
        AdvancedSystemMonitorClass->resize(600, 400);
        menuBar = new QMenuBar(AdvancedSystemMonitorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        AdvancedSystemMonitorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AdvancedSystemMonitorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        AdvancedSystemMonitorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(AdvancedSystemMonitorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        AdvancedSystemMonitorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(AdvancedSystemMonitorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        AdvancedSystemMonitorClass->setStatusBar(statusBar);

        retranslateUi(AdvancedSystemMonitorClass);

        QMetaObject::connectSlotsByName(AdvancedSystemMonitorClass);
    } // setupUi

    void retranslateUi(QMainWindow *AdvancedSystemMonitorClass)
    {
        AdvancedSystemMonitorClass->setWindowTitle(QApplication::translate("AdvancedSystemMonitorClass", "AdvancedSystemMonitor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdvancedSystemMonitorClass: public Ui_AdvancedSystemMonitorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADVANCEDSYSTEMMONITOR_H
