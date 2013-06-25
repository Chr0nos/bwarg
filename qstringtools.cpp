#include "qstringtools.h"
#include <QStringList>
#include <qmath.h>

//#include <QDebug>

QStringTools::QStringTools(QObject *parent) :
    QObject(parent)
{
}

void QStringTools::init() {
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}

QString QStringTools::randString(const QString patern,const int lenght) {
    //retourne une chaine de texte avec les caracteres aléatoires compris dans patern sur la longueur "lenght"
    QString buffer;
    const int m = patern.length();
    for (int p = 0;p < lenght;p++) {
        buffer += patern.at(qrand() % m);
    }
    return buffer;
}

QString QStringTools::scrambleString(QString input) {
    //mélange le contenu d'une chaine de texte et renvoi le resulta dans un QString
    QString buffer;
    int pos;
    while (input.length()) {
        pos = qrand() % input.length();
        buffer += input.at(pos);
        input.remove(pos,1);
    }
    return buffer;
}

QString QStringTools::shuffleWord(QString word) {
    if (word.length() < 3) return word;
    return word.left(1) + scrambleString(word.mid(1,-1)) + word.right(1);
}

QString QStringTools::shufflePhrase(QString phrase) {
    QString buffer;
    QStringList tokens = phrase.split(' ');
    for (int p = tokens.count() -1;p;p--) {
        buffer = shuffleWord(tokens.at(p)) + ' ' + buffer;
    }
    return buffer;
}

QString QStringTools::getAllAscii() {
    QString buffer;
    char c;
    for (int i = 0;i < 256;i++) {
        c = (char) i;
        buffer += c;
    }
    return buffer;
}

void QStringTools::nextChar(QChar* x, const QString* pattern) {
    //la fonction renvoi le caractere suivant dans le patern spécifié, utile pour les bruteforce... entre autre
    const int pos = pattern->indexOf(*x) +1;
    if (pos >= pattern->length()) *x = pattern->at(pattern->length() -1);
    else *x = pattern->at(pos);
}

void QStringTools::nextString(QString* input,const QString* pattern) {
    int pos = input->length();
    //si l'ancien char et le nouveau sont identiques alors on re-assigne newChar au premier char du patern fourni
    while (pos--) {
        const QChar currentChar = input->at(pos);
        QChar newChar = currentChar;
        nextChar(&newChar,pattern);
        input->replace(pos,1,newChar);
        if (currentChar != newChar) return;
        else input->replace(pos,1,pattern->at(0));
    }
    input->append(pattern->at(0));
}

bool QStringTools::matchPattern(const QString &input,const QString &pattern) {
    //renvoi true si l'input ne contiens QUE des char dans le pattern fournis sinon false
    int p = input.length();
    while (p--) {
        if (!pattern.contains(input.at(p))) return false;
    }
    return true;
}

#include <QDebug>
QString QStringTools::getStringAt(const qint64 pos,const QString &pattern) {
    //cette fonction permet de recuperer la 'pos' iteration via le pattern fournis, par exemple la premiere iteration sera pattern.at(0)
    //l'iteration pattern.lenght() +1 sera deux fois pattern.at(0) , +2 sera pattern.at(0) + pattern.at(1) etc...
    QString result;
    const int m = pattern.length();
    if (!m);
    else if (!pos);
    else {
        //len doit contenir la longueur du QString à venir
        const int len = qCeil(pos / m) +1;
        qDebug() << "Asked Pos: " << pos;
        qDebug() << "Pattern lenght: " << pattern.length();
        qDebug() << "lenght: " << len;
        for (int pos = len;pos;pos--) {
            //cette ligne decone; il faut que je trouve comment definir la position du caractere actuel
            int currentCharPos = qCeil(pos / len) +1;
            qDebug() << "currentCharPos: " << currentCharPos;
            result.append(pattern.at(currentCharPos));
        }
        qDebug() << result;
    }
    return result;
}
quint64 QStringTools::getStringCurrentPos(const QString &input,const QString &pattern) {
    quint64 result = 0;
    if (!matchPattern(input,pattern));
    else {
        const int m = input.length();
        for (int pos = 0;pos < m;pos++) {
            result += pattern.indexOf(input.at(pos),0) * (pos +1);
        }
    }
    return result;
}

QString QStringTools::removeDoublesChar(const QString &input) {
    //cette fonction supprime tous les doubles d'une chaine de texte, ca irais plus vite avec une regrex mais je sais pas faire.
    QString buffer;
    int p = input.length();
    while (p--) {
        if (!buffer.contains(input.at(p))) buffer.insert(0,input.at(p));
    }
    return buffer;
}

quint64 QStringTools::getPasswordPossibility(const QString &pattern,const int lenght) {
    return qPow(pattern.length(),lenght);
}

QString QStringTools::insert(const QString &input,const QString &add,const int evry) {
    QString buffer;
    const int m = input.length();
    int x = -1;
    for (int i = 0;i < m;i++) {
        x++;
        if (x == evry) {
            buffer += add;
            x = 0;
        }
        buffer += input.at(i);
    }
    return buffer;
}
QString QStringTools::strstr(const QChar x,const int lenght) {
    QString buffer;
    while (buffer.length() < lenght) buffer += x;
    return buffer;
}

int QStringTools::boolToInt(const bool input) {
    if (input) return 1;
    return 0;
}

bool QStringTools::toBool(const QString &input) {
    if (input.toInt()) return true;
    return false;
}
