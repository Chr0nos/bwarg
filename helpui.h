#ifndef HELPUI_H
#define HELPUI_H

#include <mainwindow.h>
#include <QDialog>
#include <QLineEdit>

namespace Ui {
class HelpUi;
}

class HelpUi : public QDialog
{
    Q_OBJECT
    
public:
    explicit HelpUi(QLineEdit *edit, QWidget *parent = 0);
    ~HelpUi();
    
private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::HelpUi *ui;
    QLineEdit *edit;
};

#endif // HELPUI_H
