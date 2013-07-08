#ifndef HELPUI_H
#define HELPUI_H

#include <QDialog>

namespace Ui {
class HelpUi;
}

class HelpUi : public QDialog
{
    Q_OBJECT
    
public:
    explicit HelpUi(QWidget *parent = 0);
    ~HelpUi();
    
private:
    Ui::HelpUi *ui;
};

#endif // HELPUI_H
