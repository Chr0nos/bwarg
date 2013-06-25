#ifndef JOBLIST_H
#define JOBLIST_H

#include <QDialog>
#include <QTableWidgetItem>
#include <QMap>
#include <QString>
#include "mainwindow.h"

namespace Ui {
class JobList;
}

class JobList : public QDialog
{
    Q_OBJECT
    
public:
    explicit JobList(QWidget *parent, QList<MainWindow::jobListBase> &jobList);
    ~JobList();
    void refreshJobList();
    
private slots:
    void on_tableWidget_itemChanged(QTableWidgetItem *item);
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

private:
    Ui::JobList *ui;
    QList<MainWindow::jobListBase>* jobList;
    bool moveJob(const int pos, const int newPos);
};

#endif // JOBLIST_H
