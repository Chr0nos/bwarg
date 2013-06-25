#ifndef THUMBSDBVIEWER_H
#define THUMBSDBVIEWER_H

#include <QDialog>
#include <QString>

namespace Ui {
class ThumbsDbViewer;
}

class ThumbsDbViewer : public QDialog
{
    Q_OBJECT
    
public:
    explicit ThumbsDbViewer(const QString &ThumbsdbPath, QWidget *parent);
    ~ThumbsDbViewer();
    void refreshIcons();

    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_clicked();

private:
    Ui::ThumbsDbViewer *ui;
    QString dbPath;
};

#endif // THUMBSDBVIEWER_H
