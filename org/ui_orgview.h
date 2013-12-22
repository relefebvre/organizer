/********************************************************************************
** Form generated from reading UI file 'orgview.ui'
**
** Created: Fri Dec 20 16:58:40 2013
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORGVIEW_H
#define UI_ORGVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrgView
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *doublons;
    QTextBrowser *textBrowser;
    QPushButton *start_stop;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *OrgView)
    {
        if (OrgView->objectName().isEmpty())
            OrgView->setObjectName(QString::fromUtf8("OrgView"));
        OrgView->resize(1279, 759);
        centralwidget = new QWidget(OrgView);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 10, 1271, 691));
        doublons = new QWidget();
        doublons->setObjectName(QString::fromUtf8("doublons"));
        textBrowser = new QTextBrowser(doublons);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(0, 540, 1151, 111));
        textBrowser->setMaximumSize(QSize(1151, 16777215));
        start_stop = new QPushButton(doublons);
        start_stop->setObjectName(QString::fromUtf8("start_stop"));
        start_stop->setGeometry(QRect(10, 10, 111, 51));
        tabWidget->addTab(doublons, QString());
        OrgView->setCentralWidget(centralwidget);
        menubar = new QMenuBar(OrgView);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1279, 27));
        OrgView->setMenuBar(menubar);
        statusbar = new QStatusBar(OrgView);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        OrgView->setStatusBar(statusbar);

        retranslateUi(OrgView);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(OrgView);
    } // setupUi

    void retranslateUi(QMainWindow *OrgView)
    {
        OrgView->setWindowTitle(QApplication::translate("OrgView", "MainWindow", 0, QApplication::UnicodeUTF8));
        start_stop->setText(QApplication::translate("OrgView", "Go", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(doublons), QApplication::translate("OrgView", "Doublons", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OrgView: public Ui_OrgView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORGVIEW_H
