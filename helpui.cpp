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
    ui->tableWidget->setColumnWidth(1,380);

    QMap<QString,QString> map;
    map["%p"] = tr("The current dir name");
    map["%x"] = tr("Sub regex value (by defaut the episode number)");
    map["%i"] = tr("Incremental count (general)");
    map["%n"] = tr("Incremental count (by type)");
    map["%d"] = tr("file Date");
    map["%h"] = tr("file creation hour");
    map["%F"] = tr("file name (original)");
    map["%f"] = tr("file name in lower chars");
    map["%e"] = tr("file extenssion (ex: jpg)");
    map["%r"] = tr("random value");
    map["%album"] = tr("song album name");
    map["%artist"] = tr("song artist name");
    map["%co"] = tr("song comment");
    map["%genre"] = tr("song genre");
    map["%b"] = tr("song bitrate");
    map["%track"] = tr("song track number");
    map["%model"] = tr("image device model used for capture");


    map["%crc"] = tr("File crc32 (on data)");


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
    //todo: bug fix ici: on doit dans tous les cas prendre la colone 0  et pas que la colone actuelle
    if (edit->text().isEmpty()) edit->setText(index.data().toString());
    else edit->setText(edit->text() + " " + index.data().toString());
}
