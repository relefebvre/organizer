/********************************************************************************
** Form generated from reading UI file 'orgview.ui'
**
** Created: Sat Jan 18 11:41:47 2014
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
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrgView
{
public:
    QAction *actionAuteurs;
    QWidget *centralwidget;
    QWidget *widget;
    QTabWidget *recherche;
    QWidget *doublons;
    QPushButton *search_double;
    QTreeView *treeView;
    QProgressBar *progressBarDouble;
    QPushButton *deleteFile;
    QWidget *tab;
    QPushButton *search_empty;
    QTextBrowser *view_empty;
    QTextBrowser *textBrowser;
    QPushButton *start_stop;
    QTreeView *vue;
    QLabel *label;
    QLabel *status;
    QLabel *status_error;
    QMenuBar *menubar;
    QMenu *menuA_propos;

    void setupUi(QMainWindow *OrgView)
    {
        if (OrgView->objectName().isEmpty())
            OrgView->setObjectName(QString::fromUtf8("OrgView"));
        OrgView->resize(1000, 759);
        OrgView->setMinimumSize(QSize(1000, 759));
        OrgView->setMaximumSize(QSize(1000, 1000));
        actionAuteurs = new QAction(OrgView);
        actionAuteurs->setObjectName(QString::fromUtf8("actionAuteurs"));
        centralwidget = new QWidget(OrgView);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setEnabled(true);
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(-1, -1, 1001, 731));
        recherche = new QTabWidget(widget);
        recherche->setObjectName(QString::fromUtf8("recherche"));
        recherche->setGeometry(QRect(290, 70, 691, 341));
        recherche->setMinimumSize(QSize(0, 0));
        doublons = new QWidget();
        doublons->setObjectName(QString::fromUtf8("doublons"));
        doublons->setFocusPolicy(Qt::TabFocus);
        search_double = new QPushButton(doublons);
        search_double->setObjectName(QString::fromUtf8("search_double"));
        search_double->setEnabled(true);
        search_double->setGeometry(QRect(10, 10, 111, 51));
        treeView = new QTreeView(doublons);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(10, 70, 671, 231));
        treeView->setSelectionMode(QAbstractItemView::MultiSelection);
        treeView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        treeView->setAutoExpandDelay(-1);
        treeView->setAnimated(false);
        treeView->setAllColumnsShowFocus(false);
        treeView->header()->setStretchLastSection(true);
        progressBarDouble = new QProgressBar(doublons);
        progressBarDouble->setObjectName(QString::fromUtf8("progressBarDouble"));
        progressBarDouble->setGeometry(QRect(140, 20, 431, 23));
        progressBarDouble->setValue(0);
        deleteFile = new QPushButton(doublons);
        deleteFile->setObjectName(QString::fromUtf8("deleteFile"));
        deleteFile->setGeometry(QRect(580, 10, 97, 51));
        recherche->addTab(doublons, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        search_empty = new QPushButton(tab);
        search_empty->setObjectName(QString::fromUtf8("search_empty"));
        search_empty->setEnabled(true);
        search_empty->setGeometry(QRect(10, 10, 111, 51));
        view_empty = new QTextBrowser(tab);
        view_empty->setObjectName(QString::fromUtf8("view_empty"));
        view_empty->setGeometry(QRect(10, 70, 671, 231));
        recherche->addTab(tab, QString());
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
        vue->setUniformRowHeights(false);
        vue->setAnimated(true);
        vue->header()->setCascadingSectionResizes(false);
        vue->header()->setStretchLastSection(false);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 20, 831, 21));
        status = new QLabel(widget);
        status->setObjectName(QString::fromUtf8("status"));
        status->setGeometry(QRect(0, 560, 1001, 21));
        status_error = new QLabel(widget);
        status_error->setObjectName(QString::fromUtf8("status_error"));
        status_error->setGeometry(QRect(0, 600, 1001, 21));
        OrgView->setCentralWidget(centralwidget);
        menubar = new QMenuBar(OrgView);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 29));
        menuA_propos = new QMenu(menubar);
        menuA_propos->setObjectName(QString::fromUtf8("menuA_propos"));
        OrgView->setMenuBar(menubar);

        menubar->addAction(menuA_propos->menuAction());
        menuA_propos->addAction(actionAuteurs);

        retranslateUi(OrgView);

        recherche->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(OrgView);
    } // setupUi

    void retranslateUi(QMainWindow *OrgView)
    {
        OrgView->setWindowTitle(QApplication::translate("OrgView", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionAuteurs->setText(QApplication::translate("OrgView", "Auteurs", 0, QApplication::UnicodeUTF8));
        search_double->setText(QApplication::translate("OrgView", "Chercher", 0, QApplication::UnicodeUTF8));
        deleteFile->setText(QApplication::translate("OrgView", "Supprimer", 0, QApplication::UnicodeUTF8));
        recherche->setTabText(recherche->indexOf(doublons), QApplication::translate("OrgView", "Doublons", 0, QApplication::UnicodeUTF8));
        search_empty->setText(QApplication::translate("OrgView", "Search", 0, QApplication::UnicodeUTF8));
        recherche->setTabText(recherche->indexOf(tab), QApplication::translate("OrgView", "Dossiers vides", 0, QApplication::UnicodeUTF8));
        start_stop->setText(QApplication::translate("OrgView", "Scanner", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("OrgView", "TextLabel", 0, QApplication::UnicodeUTF8));
        status->setText(QString());
        status_error->setText(QString());
        menuA_propos->setTitle(QApplication::translate("OrgView", "A propos", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OrgView: public Ui_OrgView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORGVIEW_H
