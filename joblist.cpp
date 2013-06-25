#include "joblist.h"
#include "ui_joblist.h"
#include "mainwindow.h"
#include "qstringtools.h"

#include <QFile>
#include <QFileDialog>
#include <QIODevice>

JobList::JobList(QWidget *parent,QList<MainWindow::jobListBase> &jobList) :
    QDialog(parent),
    ui(new Ui::JobList)
{
    ui->setupUi(this);
    this->jobList = &jobList;
    refreshJobList();
}

JobList::~JobList()
{
    delete ui;
}

//#include <QDebug>
void JobList::refreshJobList() {
    ui->tableWidget->reset();
    ui->tableWidget->setRowCount(0);

    int row = 0;
    const int m = jobList->count();
    if (!m) return;
    QTableWidgetItem *replace,*by;
    for (int p = 0;p < m;p++) {
        replace = new QTableWidgetItem();
        by = new QTableWidgetItem();

        replace->setText(jobList->at(p).replace);
        by->setText(jobList->at(p).by);

        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row,0,replace);
        ui->tableWidget->setItem(row,1,by);
        row++;
    }
}

void JobList::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    //je sais que le code de cette fonction est dégeulasse mais pas le choix sinon ca out of range.
    //note: ce code pue vraiment: il re-set lors de l'affichage la jobList pour y metre la meme chose qu'avant...
    //todo: remplacer cette merde par un code propre et plus utile
    const int pos = item->row();
    MainWindow::jobListBase job = jobList->at(pos);

    if (!item->column()) job.replace = ui->tableWidget->item(pos,0)->text();
    else job.by = ui->tableWidget->item(pos,1)->text();

    //qDebug() << "row: " << pos << "col: " << item->column() << "text: " << item->text();
    jobList->replace(pos,job);
}


void JobList::on_pushButton_4_clicked()
{
    this->close();
}

void JobList::on_pushButton_5_clicked()
{
    refreshJobList();
}

void JobList::on_pushButton_2_clicked()
{
    if (ui->tableWidget->selectedItems().isEmpty()) return;
    const int pos = ui->tableWidget->selectedItems().at(0)->row();
    if (moveJob(pos,pos +1)) refreshJobList();
}

void JobList::on_pushButton_3_clicked()
{
    if (ui->tableWidget->selectedItems().isEmpty()) return;
    const int pos = ui->tableWidget->selectedItems().at(0)->row();
    if (moveJob(pos,pos -1)) refreshJobList();

}

bool JobList::moveJob(const int pos,const int newPos) {
    //qDebug() << "pos: " << pos << " count: " << jobList->count();
    if (pos < 0);
    else if (newPos < 0);
    else if (newPos == pos);
    else if (newPos >= jobList->count());
    else {
        jobList->move(pos,newPos);
        ui->tableWidget->selectRow(newPos);
        return true;
    }
    return false;
}

void JobList::on_pushButton_6_clicked()
{
    if (ui->tableWidget->selectedItems().isEmpty()) return;
    int pos = ui->tableWidget->selectedItems().count();
    while (pos--) jobList->removeAt(ui->tableWidget->selectedItems().at(pos)->row());
    refreshJobList();
}



void JobList::on_pushButton_clicked()
{
    jobList->clear();
    refreshJobList();
}

void JobList::on_pushButton_7_clicked()
{
    //fonction de sauvegarde de la jobList
    QString filePath = QFileDialog::getSaveFileName(this,"Selectionez le fichier de destination",QString(),"*.job");
    if (filePath.isNull()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) return;
    QByteArray writeData;

    const int m = ui->tableWidget->rowCount();
    for (int p = 0;p < m;p++) {
        MainWindow::jobListBase job = jobList->at(p);
        writeData.append(job.replace + (char) 1 + job.by + (char) 1 + QString().number(QStringTools::boolToInt(job.regex)) + (char) 10);
    }
    file.write(writeData);
    file.flush();
    file.close();
}

void JobList::on_pushButton_8_clicked()
{
    //fonction de chargement de jobList

    //selection du fichier à charger:
    QFileDialog sel(this);
    sel.setModal(true);
    sel.setFilter("*.job");
    sel.show();
    sel.exec();
    if (sel.result() == sel.Reject) return;
    else if (!sel.selectedFiles().count()) return;

    //parsing des info
    QFile file(sel.selectedFiles().at(0));
    //qDebug() << "filePath: " << file.fileName();

    QByteArray line;
    if (!file.open(QIODevice::ReadOnly)) return;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        QStringList tokens = QString(line.data()).remove((char) 10).split((char) 1);
        //qDebug() << tokens;

        //si le nombre de tokens est invalide alors on arrete toute la procédure d'ajout.
        if (tokens.count() != 3) return;

        //sinon on créé le job en vue de l'ajouter.
        MainWindow::jobListBase job;
        job.replace = tokens.at(0);
        job.by = tokens.at(1);
        job.regex = QStringTools::toBool(tokens.at(2));

        //ajout dans la liste des jobs actuels.
        jobList->append(job);
    }
    refreshJobList();
}

void JobList::on_pushButton_9_clicked()
{
    //bouton d'ajout d'un nouveau job.
    MainWindow::jobListBase job;
    job.regex = true;
    jobList->append(job);
    refreshJobList();
}

void JobList::on_pushButton_10_clicked()
{
    if (ui->tableWidget->selectedItems().isEmpty()) return;
    const int pos = ui->tableWidget->selectedItems().at(0)->row();
    moveJob(pos,0);
    refreshJobList();
}


void JobList::on_pushButton_11_clicked()
{
    if (ui->tableWidget->selectedItems().isEmpty()) return;
    const int pos = ui->tableWidget->selectedItems().at(0)->row();
    moveJob(pos,ui->tableWidget->rowCount() -1);
    refreshJobList();
}
