#include <QtSql>
#include "orgview.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QApplication app(argc, argv);
    OrgView org;
    org.show();
    return app.exec();
}

