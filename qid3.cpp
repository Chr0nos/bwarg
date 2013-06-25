#include "qid3.h"
#include <QFile>
#include <QByteArray>
#include <QStringList>
//#include <qmath.h>

#include <taglib/fileref.h>
#include <taglib/tag.h>

QId3::QId3(QString filePath, QObject *parent) :
    QObject(parent)
{
    file = new QFile(filePath);
#if (defined (Q_OS_WIN32))
 bhasId3v1 = loadId3v1Tags()
#else
    bhasId3v2 = loadId3v2Tags();
    if (!bhasId3v2) bhasId3v1 = loadId3v1Tags();
#endif
}

bool QId3::loadId3v1Tags() {
    if (!file->open(QFile::ReadOnly)) return false;
    else if (file->size() < 128) return false;
    else if (!file->seek(file->size() - 128)) {
        file->close();
        return false;
    }
    QByteArray rawId3 = file->read(128);
    file->close();
    if (rawId3.mid(0,3).data() != QString("TAG")) {
        //qDebug() << "No Id3v1 tag present: " << rawId3.mid(0,3).data();
        tagId3v1.isEmpty = true;
        return false;
    }
    else {
        tagId3v1.isEmpty = false;
        tagId3v1.title = rawId3.mid(3,30).data();
        tagId3v1.artist = rawId3.mid(33,30).data();
        tagId3v1.album = rawId3.mid(63,33).data();
        tagId3v1.year = QString(rawId3.mid(93,4).data()).toInt();
        tagId3v1.comment = rawId3.mid(97,30).data();
        tagId3v1.genre = getGenreString(rawId3.mid(127,1).toHex().toInt(0,16));
        return true;
    }
}

bool QId3::loadId3v2Tags() {
    /*
    qDebug() << "Start: " << file->fileName();
    //cette fonction renvoi true si le fichier contiens des données Id3V2 sinon false;
    if (!file->open(QFile::ReadOnly)) return false;
    else if (!file->isReadable()) return false;
    QByteArray Id3Header = file->read(11);
    if (Id3Header.mid(0,3).data() != QString("ID3")) return false;
    */

    /*
    int pow = 0;
    unsigned int size = 0;
    qDebug() << Id3Header.mid(7,4).toHex();
    for (int pos = 11;pos > 6;pos--) size += qPow((Id3Header.mid(pos,1).toHex().toInt(0,16) * 4),pow++);
    qDebug() << size;
    */

    /*
    const int m = file->size();
    file->seek(10);
    QStringList tagList;
    tagList << "TIT2" << "TALB" << "TYER" << "PRIV" << "DTRCK";
    for (int pos = 11;pos < m;pos++) {
        QString tag = file->read(4).data();
        qDebug() << "Tag: " << tag;
        if (!tagList.contains(tag)) break;
        else {
            QString value = file->read(15).toHex();
            qDebug() << "Value: " << value;
        }
    }
    file->close();

    return true;
    */
#if (defined (Q_OS_WIN32))
    //la tag lib ne marche pas sous windows, aussi je la vire purement et simplement dans ce cas la.
    return false;
#else
    TagLib::FileRef f(file->fileName().toLocal8Bit());
    tagId3v2.isEmpty = f.tag()->isEmpty();
    tagId3v2.track = QString().number(f.tag()->track());
    tagId3v2.album = f.tag()->album().toCString(true);
    tagId3v2.title = f.tag()->title().toCString(true);
    tagId3v2.artist = f.tag()->artist().toCString(true);
    tagId3v2.year = f.tag()->year();
    tagId3v2.comment = f.tag()->comment().toCString(true);
    tagId3v2.bitrate = f.audioProperties()->bitrate();
    return true;
#endif
}

QString QId3::getGenreString(const int genreInt) {
    QList<QString> genres;
    genres << "Blues" << "Classic rock" << "Country" << "Dance" << "Disco" << "Funk" << "Grunge" << "Hip-Hop" << "Jazz";
    genres << "Metal" << "New age" << "Oldies" << "Other" << "Pop" << "R'n'B" << "Rap" << "Reggae" << "Rock" << "Techno";
    genres << "Industrial" << "Rock Alternative" << "Ska" << "Death Metal" << "Pranks" << "Ost" << "Euro-Techno" << "Ambiant";
    genres << "Trip hop" << "Vocal" << "Jazz-Funk" << "Fusion" << "Trance" << "Classic" << "Instrumental" << "Acid" << "House";
    genres << "Video-Game" << "SoundTrack" << "Gospel" << "Noise" << "Rock-Alternative" << "Bass" << "Soul" << "Punk";
    genres << "Space" << "Meditative" << "Pop Instrumental" << "Rock Instrumental" << "Etnic music" << "Gothique" << "Darkwave";
    genres << "Techno-Industrial" << "Electro" << "Pop-Folk" << "EuroDance" << "Dream" << "Southern Rock" << "Comedie" << "Cult";
    genres << "Gangsta" << "Hit-parade" << "Chistian Rap" << "Pop-Funk" << "Jungle" << "Armenian" << "Cabaret" << "New wave";
    genres << "Psychédélique" << "Rave" << "ShowTunes" << "Bande-annonce" << "Lo-fi" << "Tribal" << "Acid Punk" << "Acid Jazz";
    genres << "Polka" << "Retro" << "Théatre" << "Rock & roll" << "Hard Rock";

    //si le numero fournis est trop grand, alors on retourne une QString avec la valeur numerique du code de genre.
    if (genres.count() < genreInt) return QString().number(genreInt);
    return genres[genreInt];
}

QId3TagId3v1 QId3::getId3v1Tags() {
    return tagId3v1;
}
QId3TagId3v2 QId3::getId3v2Tags() {
    return tagId3v2;
}

bool QId3::hasId3v1() {
    //retourne true si le fichier contiens des données Id3v1
    return bhasId3v1;
}
