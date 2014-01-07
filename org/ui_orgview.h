/********************************************************************************
** Form generated from reading UI file 'orgview.ui'
**
** Created: Tue Dec 31 12:24:38 2013
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
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrgView
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QTabWidget *tabWidget;
    QWidget *doublons;
    QTextBrowser *view_double;
    QPushButton *search_double;
    QWidget *tab;
    QPushButton *search_empty;
    QTextBrowser *view_empty;
    QTextBrowser *textBrowser;
    QPushButton *start_stop;
    QTreeView *vue;
    QLabel *label;
    QMenuBar *menubar;

    void setupUi(QMainWindow *OrgView)
    {
        if (OrgView->objectName().isEmpty())
            OrgView->setObjectName(QString::fromUtf8("OrgView"));
        OrgView->resize(1000, 759);
        OrgView->setMinimumSize(QSize(1000, 759));
        OrgView->setMaximumSize(QSize(1000, 1000));
        centralwidget = new QWidget(OrgView);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setEnabled(true);
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(-1, -1, 1001, 731));
        tabWidget = new QTabWidget(widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(290, 70, 691, 341));
        tabWidget->setMinimumSize(QSize(0, 0));
        doublons = new QWidget();
        doublons->setObjectName(QString::fromUtf8("doublons"));
        view_double = new QTextBrowser(doublons);
        view_double->setObjectName(QString::fromUtf8("view_double"));
        view_double->setGeometry(QRect(10, 70, 671, 231));
        search_double = new QPushButton(doublons);
        search_double->setObjectName(QString::fromUtf8("search_double"));
        search_double->setEnabled(true);
        search_double->setGeometry(QRect(10, 10, 111, 51));
        tabWidget->addTab(doublons, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        search_empty = new QPushButton(tab);
        search_empty->setObjectName(QString::fromUtf8("search_empty"));
        search_empty->setEnabled(true);
        search_empty->setGeometry(QRect(10, 10, 111, 51));
        view_empty = new QTextBrowser(tab);
        view_empty->setObjectName(QString::fromUtf8("view_empty"));
        view_empty->setGeometry(QRect(10, 70, 671, 231));
        tabWidget->addTab(tab, QString());
        textBrowser = new QTextBrowser(widget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 440, 971, 111));
        textBrowser->setMaximumSize(QSize(1151, 16777215));
        textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        start_stop = new QPushButton(widget);
        start_stop->setObjectName(QString::fromUtf8("start_stop"));
        start_stop->setEnabled(true);
        start_stop->setGeometry(QRect(10, 10, 111, 51));
        vue = new QTreeView(widget);
        vue->setObjectName(QString::fromUtf8("vue"));
        vue->setGeometry(QRect(10, 70, 256, 341));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 20, 831, 21));
        OrgView->setCentralWidget(centralwidget);
        menubar = new QMenuBar(OrgView);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 25));
        OrgView->setMenuBar(menubar);

        retranslateUi(OrgView);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(OrgView);
    } // setupUi

    void retranslateUi(QMainWindow *OrgView)
    {
        OrgView->setWindowTitle(QApplication::translate("OrgView", "MainWindow", 0, QApplication::UnicodeUTF8));
        search_double->setText(QApplication::translate("OrgView", "Search", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(doublons), QApplication::translate("OrgView", "Doublons", 0, QApplication::UnicodeUTF8));
        search_empty->setText(QApplication::translate("OrgView", "Search", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("OrgView", "Dossiers vides", 0, QApplication::UnicodeUTF8));
        start_stop->setText(QApplication::translate("OrgView", "Go", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("OrgView", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OrgView: public Ui_OrgView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORGVIEW_H
