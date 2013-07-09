#include "helpui.h"
#include "ui_helpui.h"
#include <QMap>
#include <QTableWidgetItem>

HelpUi::HelpUi(QLineEdit *edit,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpUi)
{
    ui->setupUi(this);
    this->edit = edit;

    QMap<QString,QString> map;
    map["%p"] = "The current dir name";
    map["%x"] = "Sub regex value (by defaut the episode number)";
    map["%i"] = "Incremental count (general)";
    map["%n"] = "Incremental count (by type)";
    map["%d"] = "file Date";
    map["%h"] = "file creation hour";
    map["%F"] = "file name (original)";
    map["%f"] = "file name in lower chars";
    map["%e"] = "file extenssion (ex: jpg)";
    map["%r"] = "random value";
    map["%album"] = "song album name";
    map["%artist"] = "song artist name";
    map["%co"] = "song comment";
    map["%genre"] = "song genre";
    map["%b"] = "song bitrate";
    map["%track"] = "song track number";
    map["%model"] = "image device model used for capture";


    map["%crc"] = "File crc32 (on data)";


    foreach (QString key,map.keys()) {
        QTableWidgetItem *trigger = new QTableWidgetItem;
        QTableWidgetItem *usage = new QTableWidgetItem;

        trigger->setText(key);
        trigger->setToolTip(map[key]);
        usage->setText(map[key]);

        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0,0,trigger);
        ui->tableWidget->setItem(0,1,usage);
    }
}

HelpUi::~HelpUi()
{
    delete ui;
}

void HelpUi::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    if (edit->text().isEmpty()) edit->setText(index.data().toString());
    else edit->setText(edit->text() + " " + index.data().toString());
}
