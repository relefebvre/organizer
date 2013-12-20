#ifndef ORGVIEW_H
#define ORGVIEW_H

#include <QMainWindow>

namespace Ui {
class OrgView;
}

class OrgView : public QMainWindow
{
    Q_OBJECT

public:
    explicit OrgView(QWidget *parent = 0);
    ~OrgView();
    int main(std::string argv);
    void affiche(QString s);



private slots:
    void on_go_clicked();

private:
    Ui::OrgView *ui;
};

#endif // ORGVIEW_H
