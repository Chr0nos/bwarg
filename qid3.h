#ifndef QID3_H
#define QID3_H

#include <QObject>
#include <QString>
#include <QFile>

struct QId3TagId3v1 {
    QString title;
    QString artist;
    QString album;
    int year;
    QString comment;
    QString genre;
    bool isEmpty;
};
struct QId3TagId3v2 {
    QString title;
    QString genre;
    QString track;
    QString album;
    QString artist;
    QString lenght;
    int year;
    int bitrate;
    QString comment;
    bool isEmpty;
};

class QId3 : public QObject
{
    Q_OBJECT
private:
    bool loadId3v1Tags();
    bool loadId3v2Tags();
    bool bhasId3v1;
    bool bhasId3v2;
    QFile* file;
    QId3TagId3v1 tagId3v1;
    QId3TagId3v2 tagId3v2;

public:
    explicit QId3(QString filePath, QObject *parent = 0);
    QString getGenreString(const int genreInt);
    QId3TagId3v1 getId3v1Tags();
    QId3TagId3v2 getId3v2Tags();
    bool hasId3v1();

signals:
    
public slots:
    
};

#endif // QID3_H
