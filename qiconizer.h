#ifndef QICONIZER_H
#define QICONIZER_H

#include <QObject>
#include <QIcon>
#include <QString>
#include <QSize>
#include <QList>
#include <QImage>

class QIconizer : public QObject
{
    Q_OBJECT
public:
    explicit QIconizer(const QString &file, QObject *parent = 0);
    QIcon loadIconFromThumbnailCache();
    QIcon loadIconFromExif();
    QIcon loadIconFromFile();
    QIcon loadIconFromProvider();
    QIcon icon();
    bool isImage();
    static QList<QImage> getAllIconFromThumbsDb(const QString &dbPath);
    static QList<QIcon> toIconList(const QList<QImage>* imageList);
    
signals:
    
public slots:
    
private:
    QString filePath;
};

#endif // QICONIZER_H
