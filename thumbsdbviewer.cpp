#include "thumbsdbviewer.h"
#include "ui_thumbsdbviewer.h"
#include "qiconizer.h"
#include <QList>
#include <QImage>
#include <QIcon>
#include <QFile>
#include <QIODevice>
#include <QFileDialog>

ThumbsDbViewer::ThumbsDbViewer(const QString &ThumbsdbPath,QWidget *parent = 0) :
    QDialog(parent),
    ui(new Ui::ThumbsDbViewer)
{
    ui->setupUi(this);
    dbPath = ThumbsdbPath;
    refreshIcons();
}

ThumbsDbViewer::~ThumbsDbViewer()
{
    delete ui;
}

void ThumbsDbViewer::refreshIcons() {
    ui->pushButton_2->setEnabled(false);

    QList<QImage> imageList = QIconizer::getAllIconFromThumbsDb(dbPath);
    QList<QIcon> iconList = QIconizer::toIconList(&imageList);
    ui->listWidget->clear();
    int i = 0;
    foreach (QIcon icon,iconList) {
        if (!icon.isNull()) {
            ui->listWidget->addItem(QString().number(i));
            ui->listWidget->item(i)->setIcon(icon);
            i++;
        }
    }
}

void ThumbsDbViewer::on_pushButton_clicked()
{
    refreshIcons();
}

void ThumbsDbViewer::on_pushButton_2_clicked()
{
    if (ui->listWidget->selectedItems().isEmpty()) return;
    QString filePath = QFileDialog::getSaveFileName(this,tr("Selectionez le fichier de destination"),QString(),"*.jpg");
    if (filePath.isEmpty()) return;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) return;
    QImage image = ui->listWidget->selectedItems().last()->icon().pixmap(QSize(200,200)).toImage();
    image.save(filePath);
}

void ThumbsDbViewer::on_listWidget_clicked()
{
    ui->pushButton_2->setEnabled(true);
}
