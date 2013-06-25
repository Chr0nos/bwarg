#include "qiconizer.h"
#include "qexifimageheader.h"

#include <QIcon>
#include <QImage>
#include <QFile>
#include <QFileIconProvider>
#include <QList>
#include <QIODevice>
#include <QStringList>

#if (defined (Q_OS_LINUX))
#include <QCryptographicHash>
#include <QPixmap>
#include <QProcessEnvironment>
#include <QUrl>
#endif

#include <QDebug>

QIconizer::QIconizer(const QString &file,QObject *parent) :
    QObject(parent)
{
    if (QFile::exists(file)) filePath = file;
}
#if (defined (Q_OS_LINUX))
QIcon QIconizer::loadIconFromThumbnailCache() {
    QIcon result;
    //cette fonction charge les miniatures depuis le cache de mate
    //elle ne marche que sous linux aussi elle ne sera pas compliée sous windows
    QProcessEnvironment env(QProcessEnvironment::systemEnvironment());
    QCryptographicHash hash(QCryptographicHash::Md5);

    hash.addData("file://" + QString(QUrl(filePath).encodedPath().data()).toLocal8Bit());

    QString iconPath = env.value("HOME") +"/.cache/thumbnails/normal/" + hash.result().toHex() + ".png";

    QFile iconFile(iconPath);
    if (!iconFile.exists()) return result;
    else if (!iconFile.open(QFile::ReadOnly)) return result;
    else {
        //qDebug() << "Icon found: " << filePath;
        QImage image = QImage().fromData(iconFile.readAll());
        iconFile.close();
        if (!image.isNull()) return QIcon(QPixmap().fromImage(image));
    }
    return result;
}

#else
//pour windows et macos je renvoi une fonction creuse pour une question de compatibilitée.
QIcon MainWindow::loadIconFromThumbnailCache() {
    return QIcon();
}
#endif

QIcon QIconizer::loadIconFromExif() {
    //cette fonction charge l'icone en utilisant les données exif de l'image (ne marche que sur les images donc)
    if (!isImage()) return QIcon();
    QExifImageHeader exif(filePath);
    return QIcon(QPixmap().fromImage(exif.thumbnail()));;
}

QIcon QIconizer::loadIconFromFile() {
    QIcon icon;
    if (!isImage()) return icon;
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    icon = QIcon(QPixmap().fromImage(QImage().fromData(file.readAll()).scaledToHeight(200)));
    file.close();
    return icon;
}

QIcon QIconizer::loadIconFromProvider() {
    return QFileIconProvider().icon(QFileInfo(filePath));
}

bool QIconizer::isImage() {
    QStringList ext;
    ext << "png" << "jpg" << "bmp";
    if (!ext.contains(filePath.split('.').last().toLower())) return false;
    return true;
}

QList<QImage> QIconizer::getAllIconFromThumbsDb(const QString &dbPath) {
    //cette fonction charge les icones contenues dans un fichier Thumbs.db (créé par windows Xp/7)
    QList<QImage> imageList;
    QFile file(dbPath);
    if (!file.exists());
    else if (!file.open(QFile::ReadOnly));
    else {
        QByteArray fileContent = file.readAll();
        file.close();
        if (fileContent.mid(0,8).toHex() != "d0cf11e0a1b11ae1") qDebug() << "invalid thumbs.db file format";
        else {
            qDebug() << "file seams to be valid.";
            //ici je déclare le header classique d'un fichier jpg
            QByteArray jpgHeader = QByteArray().fromHex("ffd8");
            QByteArray jpgHeaderEnd = QByteArray().fromHex("ffd9");

            //je compte le nombre de headers trouvé dans le fichier et le stoque dans imageCount
            const int imagesCount = fileContent.count(jpgHeader);
            qDebug() << "Thumbnails found:" << imagesCount;

            //construction de l'index des debuts de fichiers jpg
            QList<int> imagesPosStart;
            int pos = 0;
            while ((pos = fileContent.indexOf(jpgHeader,pos)) != -1) imagesPosStart.append(pos++);

            for (pos = 0;pos < imagesCount;pos++) {
                int start = imagesPosStart.at(pos);

                //le end est definis sur la prochaine occurence de la fin du header jpg à partir du debut du fichier
                int end = fileContent.indexOf(jpgHeaderEnd,start) +2 - start;
                if (end > file.size()) return imageList;
                //si la fin est invalide on stop tout
                else if (end <= 0) return imageList;

                QByteArray imageData = fileContent.mid(start,end);
                qDebug() << "Current image num: " << pos;
                if ((imageData.mid(0,2) != jpgHeader) || (imageData.mid(imageData.count() -2,2) != jpgHeaderEnd)) qDebug() << "Warning: the jpg data seams to be bad !";

                QImage image = QImage().fromData(imageData);

                //si l'image est valide on l'ajoute à la liste d'images actueles (pour retour en fin de fonction)
                if (!image.isNull()) imageList.append(image);
            }

            //gestion des noms des fichier à partir d'ici.
            //ici je déclare ce qui semble être le délimitateur entre les noms de fichiers.
            QByteArray delimiterStart = QByteArray().fromHex("1b0f8203");
            QByteArray delimiterEnd = QByteArray().fromHex("002c");
            QByteArray delimiterSub = QByteArray().fromHex("c801");
            QStringList filesNames;
            pos = 0;
            while ((pos = fileContent.indexOf(delimiterStart,pos)) != -1) {
                int start = fileContent.indexOf(delimiterSub,pos) +2;
                int end = fileContent.indexOf(delimiterEnd,start) - start;
                QByteArray rawFileName = fileContent.mid(start,end);
                QString fileNameHex = rawFileName.toHex();
                fileNameHex.remove("00");
                QString fileName = QByteArray().fromHex(fileNameHex.toLocal8Bit()).data();

                qDebug() << pos << end << rawFileName.toHex() << fileNameHex << fileName;
                filesNames << fileName;
                pos++;
            }
            qDebug() << filesNames;
        }
    }
    return imageList;
}

QList<QIcon> QIconizer::toIconList(const QList<QImage>* imageList) {
    //cette fonction convertis une liste de QImage en QIcon
    QList<QIcon> result;
    const int m = imageList->count();
    for (int pos = 0;pos < m;pos++) {
        result << QIcon(QPixmap().fromImage(imageList->at(pos)));
    }
    qDebug() << "before: " << m << " after: " << result.count();
    return result;
}

QIcon QIconizer::icon() {
    //cette fonction chargera l'icone du moyen du plus rapide au plus long, dans l'ordre:
    //1: cache des miniatures de caja (*)
    //2: données exif (images)
    //3: image complete (images)
    //4: provider d'icones (*)
    QIcon icon;
    if (filePath.isNull()) return icon;
    icon = loadIconFromThumbnailCache();
    if (icon.isNull()) icon = loadIconFromExif();
    if (icon.isNull()) icon = loadIconFromFile();
    if (icon.isNull()) icon = loadIconFromProvider();
    return icon;
}
