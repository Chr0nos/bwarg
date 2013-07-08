#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QMap>
#include <QIcon>
#include <QFile>
#include "qexifimageheader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void refreshNewFileList();
    void jobAdd(const QString &replace, const QString &by, const bool regex = true, const bool after = false);
    static int askInt(const int currentValue);
    static QString askString(QString text, QString value);
    void resetNewNames();
    struct jobListBase {
        QString replace;
        QString by;
        bool regex;
    };

private slots:
    void on_browse_clicked();
    void on_pushButton_clicked();
    void on_lineEdit_textChanged();
    void on_lineEdit_2_textChanged();
    void on_dirPath_textChanged();
    void on_checkBox_stateChanged();
    void on_actionQuitter_triggered();
    void on_actionCRC32_triggered();
    void on_actionCrochets_triggered();
    void on_actionDouble_majuscules_triggered();
    void on_actionCompter_triggered();
    void on_actionDecaper_triggered();
    void on_actionTout_triggered();
    void on_numLen_valueChanged();
    void on_actionExtenssion_en_minuscules_triggered();
    void on_pushButton_2_clicked();
    void on_lineEdit_2_returnPressed();
    void renameFiles();
    void on_actionToujours_au_dessus_triggered();
    void on_actionTrier_triggered();
    void refreshFileList();
    void on_fileList_doubleClicked(const QModelIndex &index);
    void refreshFilesIcons();
    void on_actionPas_du_compteur_triggered();
    void on_actionDebut_du_compteur_triggered();
    void on_actionEspaces_en_debut_de_titre_triggered();
    void on_actionActiver_ID3_changed();
    void on_actionType_triggered();
    void on_actionDefault_triggered();
    void on_actionPreferences_triggered();
    void on_actionActiver_miniatures_triggered();
    void on_action_piste_artiste_titre_triggered();
    void on_actionMode_icones_changed();
    void refreshFileIcon(const int i);
    void on_actionReLister_triggered();
    void on_actionLongueur_triggered();
    void on_actionModele_triggered();
    void on_actionDefinir_triggered();
    void on_actionJobList_triggered();
    void on_pushButton_3_clicked();
    void on_actionIgnorer_Extenssions_changed();
    void on_actionNombres_triggered();
    void on_actionRecompter_triggered();
    void on_actionVersion_triggered();
    void on_actionEn_fin_de_nom_triggered();
    void on_actionThumb_db_viewer_triggered();

    void on_actionActiver_Exif_triggered();

    void on_actionAide_triggered();

private:
    Ui::MainWindow *ui;
    int counterPas;
    int counterBase;
    bool ignoreExt;
    bool enableId3;
    bool enableIcons;
    bool autoRefresh;
    bool enableExif;
    QString putZero(const int &value);
    QString randomPattern;
    int randomLenght;
    QMap<int,QIcon> thumbs;
    QMap<int,QString> crc32List;
    QMap<int,QExifImageHeader*> exif;
    QRegExp regexForX;
    jobListBase job;
    QList<jobListBase> jobList;
    QList<jobListBase> afterJobList;
    void setDefaultJobList();
    void initConfig();
    bool loadIconFromThumbnailCache(QString filePath, const int i);
    void clearExif();
};

#endif // MAINWINDOW_H
