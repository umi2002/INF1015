/********************************************************************************
** Form generated from reading UI file 'projet.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJET_H
#define UI_PROJET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_projetClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *projetClass)
    {
        if (projetClass->objectName().isEmpty())
            projetClass->setObjectName("projetClass");
        projetClass->resize(600, 400);
        menuBar = new QMenuBar(projetClass);
        menuBar->setObjectName("menuBar");
        projetClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(projetClass);
        mainToolBar->setObjectName("mainToolBar");
        projetClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(projetClass);
        centralWidget->setObjectName("centralWidget");
        projetClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(projetClass);
        statusBar->setObjectName("statusBar");
        projetClass->setStatusBar(statusBar);

        retranslateUi(projetClass);

        QMetaObject::connectSlotsByName(projetClass);
    } // setupUi

    void retranslateUi(QMainWindow *projetClass)
    {
        projetClass->setWindowTitle(QCoreApplication::translate("projetClass", "projet", nullptr));
    } // retranslateUi

};

namespace Ui {
    class projetClass: public Ui_projetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJET_H
