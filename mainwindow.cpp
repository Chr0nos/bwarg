#include "qexifimageheader.h"
#include "qexifimageheader.cpp"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include "joblist.h"
#include "qid3.h"
#include "qstringtools.h"
#include "qiconizer.h"
#include "qcrc32.h"
#include "thumbsdbviewer.h"
#include "helpui.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QString>
#include <QFileDialog>
#include <QDebug>
#include <QRegExp>
#include <QInputDialog>
#include <QMessageBox>
#include <QDirModel>
#include <QSize>
#include <QIODevice>

//#include <QDebug>

#define VERSION "1.8.2"

void MainWindow::initConfig() {
    counterPas = 1;
    counterBase = 1;
    enableId3 = true;
    enableIcons = false;
    enableExif = true;
    ignoreExt = true;
    autoRefresh = true;


    randomPattern = PATTERN_ALPHA_NUMERIC;
    randomLenght = 10;

    //par default je met pour que ca match sur les épisodes des séries.
    regexForX.setPattern("[S0-9][E0-9]+");

    setDefaultJobList();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initConfig();

    ui->actionPreferences->setVisible(false); //je le cache le temp que je finise la section

    ui->actionActiver_ID3->setChecked(enableId3);
    ui->actionActiver_miniatures->setChecked(enableIcons);
    ui->actionIgnorer_Extenssions->setChecked(ignoreExt);
    ui->actionActiver_Exif->setChecked(enableExif);

    ui->statusBar->showMessage(tr("Pret."));

    //la fonction rafraichis la liste d'elle même: pas la peine de faire un refresh.
    ui->dirPath->setText(QDir::currentPath());
    ui->lineEdit->setFocus();

    //ui->statusBar->showMessage(QString().number(QStringTools::getStringCurrentPos(QString("9"),QString("0123456789"))));
}
void MainWindow::setDefaultJobList() {
    //cette fonction constuit une joblist par default
    /* Actuelemement je supprime par default:
     * - les espaces en debut de nom de fichier
     * - les espaces en fin de nom de fichier
     * Note: cette jobList ne sera évaluée qu'apres la jobList de l'utilisateur et sa frappe dans les line edit
    */
    QStringList removeList;
    removeList << "\\s+$" << "^\\s";
    foreach (QString remove,removeList) {
        jobAdd(remove,"",true,true);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
    clearExif();
}

void MainWindow::on_browse_clicked()
{
    ui->browse->setEnabled(false);
    QFileDialog sel;
    sel.setFileMode(QFileDialog::DirectoryOnly);
    sel.show();
    sel.exec();
    if (sel.result() == QFileDialog::Rejected);
    else if (!sel.selectedFiles().at(0).isNull()) {
        ui->dirPath->setText(sel.selectedFiles().at(0));
    }
    ui->browse->setEnabled(true);
}

void MainWindow::on_pushButton_clicked() {
    //bouton pour renomer les fichiers
    renameFiles();
}

void MainWindow::renameFiles() {
    QString filePath,newFilePath;
    int renamed = 0;
    const int m = ui->fileList->count();
    if (!m) ui->statusBar->showMessage(tr("Rien à renomer."),2000);
    for (int i = 0;i < m;i++) {
        filePath = ui->dirPath->text() + "/" + ui->fileList->item(i)->toolTip();
        newFilePath = ui->dirPath->text() + "/" + ui->fileList->item(i)->text();

        QFile file(filePath);
        if (filePath == newFilePath);
        else if (!file.exists()) qDebug() << "The file: " << file.fileName() << " dosent exists";
        else if (QFile::exists(newFilePath)) qDebug() << "The destination already exists.";
        else if (!file.rename(newFilePath)) qDebug() << "Renaming failure.";
        else {
            renamed++;
            refreshFileIcon(i);
        }
    }
    if (renamed) {
        //on rafraichi la liste des fichiers
        refreshFileList();
        ui->statusBar->showMessage(QString().number(renamed) + " item(s) renamed.");
    }
}

void MainWindow::refreshNewFileList() {
    if ((jobList.isEmpty()) && (ui->lineEdit->text().isEmpty())) {
            resetNewNames();
            return;
    }

    ui->pushButton_2->setEnabled(false);
    ui->statusBar->showMessage(tr("Génération des nouveaux noms de fichiers..."));
    QString fileName,newFileName,ext,rootFileName;
    QStringList tokens;
    const QString path = ui->dirPath->text().split('/').last();
    QRegExp exp(ui->lineEdit->text());
    int numeric = counterBase -1;
    if (ui->checkBox->isChecked()) exp.setPatternSyntax(QRegExp::RegExp2);
    else exp.setPatternSyntax(QRegExp::FixedString);

    QMap<QString,int> typesCounter;

    const int m = ui->fileList->count();
    ui->progressBar->setMaximum(m);
    ui->progressBar->setValue(0);
    //ici je boucle sur la liste
    for (int i = 0;i < m;i++) {
        numeric += counterPas;

        fileName = ui->fileList->item(i)->toolTip();
        QFile file(ui->dirPath->text() + "/" + fileName);
        QFileInfo info(file.fileName());

        tokens = fileName.split('.');

        if (tokens.count() < 2) ext.clear();
        else ext = tokens.last().split(' ').last().toLower();

        rootFileName.clear();
        for (int x = 0;x < tokens.count() -1;x++) rootFileName += "." + tokens.at(x);
        rootFileName = rootFileName.mid(1);


        //todo: optimiser ce petit bloc
        if (rootFileName.isNull()) rootFileName = ext;
        else if (ignoreExt) {
            if (!rootFileName.isNull()) newFileName = rootFileName;
            else newFileName = ext;
        }

        //gestion de la job liste
        const int jobs = jobList.count();
        for (int jobN = 0;jobN < jobs;jobN++) {
            QRegExp jobExp(jobList.at(jobN).replace);
            if (jobList.at(jobN).regex) jobExp.setPatternSyntax(QRegExp::RegExp2);
            else jobExp.setPatternSyntax(QRegExp::FixedString);
            newFileName.replace(jobExp,jobList.at(jobN).by);
        }

        //rempalcement selon l'interface (les lines edit)
        newFileName.replace(exp,ui->lineEdit_2->text());

        //gestion de la after joblist
        foreach (jobListBase job,afterJobList) {
            QRegExp jobExp(job.replace);
            jobExp.setPatternSyntax(QRegExp::RegExp2);
            newFileName.replace(jobExp,job.by);
        }

        //gestions des tags des mp3
        if (enableId3) {
            QStringList Id3Ext;
            Id3Ext << "mp3" << "flac" << "ogg";
            if (Id3Ext.contains(ext)) {
                //qDebug() << "file: " << file.fileName();
                QId3 tag(file.fileName());
                if (!tag.getId3v2Tags().isEmpty) {
                    newFileName.replace("%album",tag.getId3v2Tags().album);
                    newFileName.replace("%artist",tag.getId3v2Tags().artist);
                    newFileName.replace("%y",putZero(tag.getId3v2Tags().year));
                    newFileName.replace("%genre",tag.getId3v2Tags().genre);
                    newFileName.replace("%title",tag.getId3v2Tags().title);
                    newFileName.replace("%track",putZero(tag.getId3v2Tags().track.toInt()));
                    newFileName.replace("%co",tag.getId3v2Tags().comment);
                    newFileName.replace("%b",QString().number(tag.getId3v2Tags().bitrate));
                }
                else if (!tag.getId3v1Tags().isEmpty) {
                    newFileName.replace("%album",tag.getId3v1Tags().album);
                    newFileName.replace("%artist",tag.getId3v1Tags().artist);
                    newFileName.replace("%y",putZero(tag.getId3v1Tags().year));
                    newFileName.replace("%genre",tag.getId3v1Tags().genre);
                    newFileName.replace("%title",tag.getId3v1Tags().title);
                    newFileName.replace("%co",tag.getId3v1Tags().comment);
                }
            }
        }
        if (enableExif) {
            if (ext == "jpg") {
                if (!exif.contains(i)) {
                    exif[i] = new QExifImageHeader(file.fileName());
                }
                if (exif.contains(i)) {
                    newFileName.replace("%d",exif[i]->value(QExifImageHeader::DateTimeOriginal).toString().split(' ').at(0));
                    newFileName.replace("%model",exif[i]->value(QExifImageHeader::Model).toString().toLower());
                }
            }
        }

        //compteur par type
        if (typesCounter.contains(ext)) typesCounter[ext] += counterPas;
        else typesCounter[ext] = counterBase;

        if (newFileName.contains("%e")) newFileName.replace("%e",ext);
        if (newFileName.contains("%F")) newFileName.replace("%F",rootFileName);
        if (newFileName.contains("%f")) newFileName.replace("%f",rootFileName.toLower());
        if (newFileName.contains("%d")) newFileName.replace("%d",info.created().toString("MM-dd-yyyy"));
        if (newFileName.contains("%D")) newFileName.replace("%D",info.created().toString("dddd d MMMM yyyy"));
        if (newFileName.contains("%h")) newFileName.replace("%h",info.created().toString("hh"));
        if (newFileName.contains("%m")) newFileName.replace("%m",info.created().toString("mm"));
        if (newFileName.contains("%y")) newFileName.replace("%y",info.created().toString("yyyy"));
        if (newFileName.contains("%p")) newFileName.replace("%p",path);
        if (newFileName.contains("%r")) newFileName.replace("%r",QStringTools::randString(randomPattern,randomLenght));
        if (newFileName.contains("%x")) {
            //%x remplacera la valeur matché par l'expression réguliere.
            regexForX.indexIn(fileName);
            QString xValue = regexForX.capturedTexts().first();
            if (!xValue.length());
            //si X est un entier alors on rajoute des zero suivant le nombre demandé par la spinbow de l'ui
            else if (QStringTools::matchPattern(xValue,QString(PATTERN_NUMERIC))) {
                xValue = putZero(xValue.toInt());
            }
            newFileName.replace("%x",xValue);
        }
        if (newFileName.contains("%crc")) {
            //on ouvre le fichier en lecture seule
            file.open(QIODevice::ReadOnly);
            //si le crc n'est pas dans la liste des crc on l'y ajoute
            if (!crc32List.contains(i)) crc32List[i] = QCrc32::getCrc32Hex(file.readAll()).toUpper();

            //on remplace %crc par la valeur crc du fichier contenue dans la liste des crc
            newFileName.replace("%crc",crc32List[i]);
            file.close();
        }

        if (newFileName.contains("%i")) newFileName.replace("%i",putZero(numeric));
        if (newFileName.contains("%n")) newFileName.replace("%n",putZero(typesCounter[ext]));

        QStringList clean;
        clean << "%album" << "%artist" << "%genre" << "%title" << "%track" << "%co" << "%b" << "%model" << "%r";
        clean << "%p" << "%y" << "%h" << "%m" << "%D" << "%x";
        foreach (QString balise,clean) newFileName.remove(balise);

        if (!newFileName.length()) newFileName = fileName;
        else if ((ignoreExt) && (!ext.isNull())) newFileName.append("." + ext);
        //si la destination existe deja, alors n'insere pas, sinon si.
        if (!ui->fileList->findItems(newFileName,Qt::MatchFixedString).isEmpty());
        else {
            //on édite le nom de fichier actuel pour le transformer en le nouveau nom de fichier
            ui->fileList->item(i)->setText(newFileName);

            //si le nom du fichier à changé alors on le met en bleu dans la liste.
            if (fileName != newFileName) ui->fileList->item(i)->setTextColor(255);
            else ui->fileList->item(i)->setTextColor(QColor().black());
        }
        ui->progressBar->setValue(i +1);
    }
    ui->statusBar->showMessage(tr("Fini."));
    ui->pushButton_2->setEnabled(true);
}

QString MainWindow::putZero(const int &value) {
    return QString().number(value).rightJustified(ui->numLen->value(),'0');
}

void MainWindow::on_lineEdit_textChanged() {
    if (autoRefresh) refreshNewFileList();
}

void MainWindow::on_lineEdit_2_textChanged() {
    //todo : fixer le bug: si le mec tappe un char interdit au millieux de la chaine et non pas uniquement a la fin.
    if (!autoRefresh) return;
    else if (ui->lineEdit_2->text().right(1).contains(QRegExp("[\\/:*?\"<>\\|]")))
        ui->lineEdit_2->setText(ui->lineEdit_2->text().mid(0,ui->lineEdit_2->text().length() -1));
    else refreshNewFileList();
}

void MainWindow::on_dirPath_textChanged() {
    //dans le cas d'un changement de chemin: on vide le cache des miniatures
    thumbs.clear();
    crc32List.clear();
    clearExif();
    refreshFileList();
    if (!jobList.isEmpty()) refreshNewFileList();
}

void MainWindow::refreshFileList() {
    //fonction de listing des dossiers
    ui->statusBar->showMessage(tr("Listing in progress..."));
    ui->pushButton_2->setEnabled(false);
    ui->fileList->clear();
    QStringList files;
    QDir dir(ui->dirPath->text());
    if (dir.exists()) {
        dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
        files = dir.entryList();
        if (files.isEmpty()) {
            //si aucun fichier n'a été trouvé on colle quand meme la bare de progression au maxi,
            //histoire qu'elle ne patine pas dans le vide pour rien.
            ui->progressBar->setMaximum(1);
            ui->progressBar->setValue(1);
        }
        else {
            ui->progressBar->setMaximum(files.count());
            int i = 0;
            foreach (QString fileName,files) {
                //qDebug() << "Adding: " << fileName;
                ui->fileList->addItem(fileName);
                ui->fileList->item(i)->setToolTip(fileName);
                refreshFileIcon(i);
                i++;
                ui->progressBar->setValue(i);
            }
        }
    }
    else ui->progressBar->setMaximum(0);

    ui->pushButton_2->setEnabled(true);
    ui->statusBar->showMessage("Done, " + QString().number(files.count()) + " file(s) found.");

    //outil de vision des miniatures des fichier windows.
    if (files.contains("Thumbs.db")) ui->actionThumb_db_viewer->setEnabled(true);
    else ui->actionThumb_db_viewer->setEnabled(false);

    //refreshFilesIcons();
    if ((ui->lineEdit->text().length()) || (ui->lineEdit_2->text().length())) refreshNewFileList();
}

void MainWindow::on_checkBox_stateChanged()
{
    refreshNewFileList();
}

void MainWindow::on_actionQuitter_triggered()
{
    exit(0);
}

void MainWindow::on_actionCRC32_triggered() {
    ui->lineEdit->setText("([a-f0-9A-F]{8})");
    ui->lineEdit_2->clear();
    ui->checkBox->setChecked(true);
}

void MainWindow::on_actionCrochets_triggered() {
    ui->lineEdit->setText("\\[[^]]*\\]");
    ui->lineEdit_2->clear();
    ui->checkBox->setChecked(true);
}

void MainWindow::on_actionDouble_majuscules_triggered() {
    ui->lineEdit->setText("([A-Z]+){2}");
    ui->checkBox->setChecked(true);
}
//regex pour TOUS sauf nombres: ([A-z]+)|(\s)

void MainWindow::on_actionCompter_triggered()
{
    ui->lineEdit->setText("\\S.*");
    ui->lineEdit_2->setText("%i");
    ui->checkBox->setChecked(true);
}

void MainWindow::on_actionDecaper_triggered()
{
    ui->lineEdit->setText("( \\[\\S+\\])|([a-f0-9A-F]{8})|([A-Z]+){2}");
    ui->checkBox->setChecked(true);
}

void MainWindow::on_actionTout_triggered()
{
    ui->lineEdit->setText("\\S.*");
}

void MainWindow::on_numLen_valueChanged() {
    refreshNewFileList();
}

void MainWindow::on_actionExtenssion_en_minuscules_triggered()
{
    ui->lineEdit->setText("([$A-Za-z]){3}");
    ui->lineEdit_2->setText("%e");
    ui->actionIgnorer_Extenssions->setChecked(false);
    ui->checkBox->setChecked(true);
}
void MainWindow::on_pushButton_2_clicked() {
    refreshNewFileList();
}


void MainWindow::on_lineEdit_2_returnPressed() {
    refreshNewFileList();
}


void MainWindow::on_actionToujours_au_dessus_triggered() {
    Qt::WindowFlags flags = this->windowFlags();
    if (ui->actionToujours_au_dessus->isChecked()) this->setWindowFlags(flags | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
    else this->setWindowFlags(flags ^ (Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint));
    this->show();
}

void MainWindow::on_actionTrier_triggered() {
    ui->fileList->setSortingEnabled(ui->actionTrier->isChecked());
}

void MainWindow::on_fileList_doubleClicked(const QModelIndex &index) {
    QString fileName = ui->fileList->item(index.row())->text();
    QInputDialog input;
    input.setLabelText(tr("Enter the new file name."));
    input.setTextValue(fileName);
    input.show();
    input.exec();
    if (input.result() == QInputDialog::Rejected);
    else if (input.textValue().isNull());
    else if (input.textValue() == fileName);
    else if (input.textValue().contains(QRegExp("[\\/:*?\"<>\\|]"))) QMessageBox::warning(this,"Error","Illegals characters in the new file name");
    else if (!ui->fileList->findItems(input.textValue(),Qt::MatchExactly).isEmpty()) QMessageBox::warning(this,"Error","File file already exists !");
    else ui->fileList->item(index.row())->setText(input.textValue());
}

void MainWindow::refreshFilesIcons() {
    //cette fonction refraichis toute la liste de miniatures
    const int m = ui->fileList->count();
    ui->progressBar->setMaximum(m -1);
    for (int i = 0;i < m;i++) {
        refreshFileIcon(i);
        ui->progressBar->setValue(i);
    }
}

void MainWindow::refreshFileIcon(const int i) {
    //cette fonction gere le cache des miniatures et attribue la miniature à l'item "i" dans fileList

    if (enableIcons) {
        //si la miniature existe deja dans le cache on l'affiche tout simplement
        if (thumbs.contains(i)) {
            ui->fileList->item(i)->setIcon(thumbs[i]);
            return;
        }
        //sinon on utilise QIconizer qui nous fournira l'icone la plus adaptée au fichier demandé.
        QFile file(ui->dirPath->text() + "/" + ui->fileList->item(i)->text());

        thumbs[i] = QIconizer(file.fileName()).icon();
        if (thumbs[i].isNull()) thumbs.remove(i);
        else ui->fileList->item(i)->setIcon(thumbs[i]);
    }
}

int MainWindow::askInt(const int currentValue) {
    QInputDialog input;
    input.setModal(true);
    input.setLabelText(tr("Enter the numeric value"));
    input.setTextValue(QString().number(currentValue));
    input.show();
    input.exec();
    if (input.result() == input.Rejected) return currentValue;
    return input.textValue().toInt();
}

void MainWindow::on_actionPas_du_compteur_triggered()
{
    const int x = askInt(counterPas);
    if (x) {
        counterPas = x;
        refreshNewFileList();
    }
}

void MainWindow::on_actionDebut_du_compteur_triggered()
{
    counterBase = askInt(counterBase);
    refreshNewFileList();
}

void MainWindow::on_actionEspaces_en_debut_de_titre_triggered() {
    ui->checkBox->setChecked(true);
    ui->lineEdit->setText("^\\s");
    ui->lineEdit_2->clear();
}

void MainWindow::on_actionActiver_ID3_changed()
{
    enableId3 = ui->actionActiver_ID3->isChecked();
    refreshNewFileList();
}

void MainWindow::on_actionType_triggered() {
    ui->lineEdit->setText("\\S.*");
    ui->lineEdit_2->setText("%n");
    ui->checkBox->setChecked(true);
}

void MainWindow::on_actionDefault_triggered()
{
    counterBase = 0;
    counterPas = 1;
    refreshNewFileList();
}

void MainWindow::on_actionPreferences_triggered()
{
    Config config(this);
    config.show();
    config.exec();
}

void MainWindow::on_actionActiver_miniatures_triggered()
{
    enableIcons = ui->actionActiver_miniatures->isChecked();
    if (!enableIcons) {
        thumbs.clear();
        ui->actionMode_icones->setChecked(false);
        refreshFileList();
    }
    else refreshFilesIcons();
}

void MainWindow::on_action_piste_artiste_titre_triggered()
{
    ui->actionActiver_ID3->setChecked(true);
    ui->lineEdit_2->setText("%track - %artist - %title");
    ui->lineEdit->setText("\\S.*.mp3");
    ui->checkBox->setChecked(true);
}


void MainWindow::on_actionMode_icones_changed()
{
    //ici je dois vider le cache des miniatures car celles ci sont soit trop petites, soit trop grandes, économisont de la RAM.
    thumbs.clear();

    if (ui->actionMode_icones->isChecked()) {
        ui->fileList->setViewMode(QListWidget::IconMode);
        ui->fileList->setGridSize(QSize(150,140));
        ui->fileList->setIconSize(QSize(120,120));
        ui->actionActiver_miniatures->setChecked(true);
    }
    else {
        ui->fileList->setGridSize(QSize());
        ui->fileList->setIconSize(QSize(40,40));
        ui->fileList->setViewMode(QListWidget::ListMode);
    }
    on_actionActiver_miniatures_triggered();
}

void MainWindow::on_actionReLister_triggered()
{
    refreshFileList();
}

void MainWindow::on_actionLongueur_triggered()
{
    const int v = askInt(randomLenght);
    if (v) {
        randomLenght = v;
        if (randomLenght != v) refreshNewFileList();
    }
}

void MainWindow::on_actionModele_triggered()
{
    QInputDialog text;
    text.show();
    text.exec();
    if (text.result() == QInputDialog::Rejected);
    else if (!text.textValue().length());
    else {
        randomPattern = QStringTools::removeDoublesChar(text.textValue());
        refreshNewFileList();
    }
}

QString MainWindow::askString(QString text,QString value) {
    QString result;
    QInputDialog input;
    input.setLabelText(text);
    input.setTextValue(value);
    input.show();
    input.exec();
    if (input.result() == input.Rejected);
    else result =  input.textValue();
    return result;
}

void MainWindow::on_actionDefinir_triggered()
{
    QString newRegex = askString(tr("Entrez la nouvelle regex"),regexForX.pattern());
    if (!newRegex.isNull()) regexForX.setPattern(newRegex);
    refreshNewFileList();
}

void MainWindow::on_actionJobList_triggered()
{
    JobList job(this,jobList);
    job.show();
    //job.refreshJobList(&jobList);
    job.exec();
    refreshNewFileList();
}

void MainWindow::on_pushButton_3_clicked()
{
    //on empeche l'ajout de job vide.
    if ((ui->lineEdit->text().isNull()) && (ui->lineEdit_2->text().isNull())) return;
    jobListBase job;
    job.regex = ui->checkBox->isChecked();
    job.replace = ui->lineEdit->text();
    job.by = ui->lineEdit_2->text();
    jobList.append(job);
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}

void MainWindow::on_actionIgnorer_Extenssions_changed()
{
    ignoreExt = ui->actionIgnorer_Extenssions->isChecked();
    refreshNewFileList();
}

void MainWindow::on_actionNombres_triggered()
{
    regexForX.setPattern("[0-9]+");
}

void MainWindow::on_actionRecompter_triggered()
{
    ui->lineEdit->setText("\\b[0-9]+\\b");
    ui->lineEdit_2->setText("%x");
    ui->checkBox->setChecked(true);
}

void MainWindow::on_actionVersion_triggered()
{
    QMessageBox::information(this,"BwarG version","Current version: " + QString(VERSION),QMessageBox::Ok);
}

void MainWindow::on_actionEn_fin_de_nom_triggered()
{
    ui->lineEdit->setText("\\s+$");
    ui->lineEdit_2->setText("");
    ui->checkBox->setChecked(true);
}

void MainWindow::jobAdd(const QString &replace, const QString &by, const bool regex,const bool after) {
    //cette fonction ajoute le job voulu dans la liste des jobs
    jobListBase job;
    job.replace = replace;
    job.by = by;
    job.regex = regex;
    if (after) afterJobList.append(job);
    else jobList.append(job);
}

void MainWindow::on_actionThumb_db_viewer_triggered()
{
    ThumbsDbViewer gui(ui->dirPath->text() + "/Thumbs.db",this);
    gui.show();
    gui.exec();
}

void MainWindow::resetNewNames() {
    //remet les noms d'origine dans la fileList sans pour autant chercher à nouveau les fichiers sur le disque
    const int m = ui->fileList->count();
    for (int i = 0;i < m;i++) {
        ui->fileList->item(i)->setText(ui->fileList->item(i)->toolTip());
        ui->fileList->item(i)->setTextColor(QColor().black());
    }
}

void MainWindow::clearExif() {
    qDeleteAll(exif);
    exif.clear();
}

void MainWindow::on_actionActiver_Exif_triggered()
{
    enableExif = ui->actionActiver_Exif->isChecked();
    if (!enableExif) clearExif();
}

void MainWindow::on_actionAide_triggered()
{
    HelpUi help(ui->lineEdit_2);
    help.show();
    help.exec();
}
