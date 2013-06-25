#ifndef QSTRINGTOOLS_H
#define QSTRINGTOOLS_H

#define PATTERN_NUMERIC "0123456789"
#define PATTERN_HEXADECIMAL "0123456789abcdef"
#define PATTERN_ALPHA_LOWER "abcdefghijklmnopqrstuvwxyz"
#define PATTERN_ALPHA_UPPER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define PATTERN_ALPHA "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define PATTERN_ALPHA_NUMERIC_LOWER "0123456789abcdefghijklmnopqrstuvwxyz"
#define PATTERN_ALPHA_NUMERIC "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define PATTERN_PASSWORD "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz!\"#$%&'()*+,-./0123456789:;<=>?@{|} "
#define PATTERN_PRINTABLE "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz!\"#$%&'()*+,-./0123456789:;<=>?@{|}~¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ "

#include <QObject>
#include <QString>
#include <QTime>


class QStringTools : public QObject
{
    Q_OBJECT
public:
    explicit QStringTools(QObject *parent = 0);
    static void init();
    static QString randString(const QString patern,const int lenght);
    static QString scrambleString(QString input);
    static QString shuffleWord(QString word);
    static QString shufflePhrase(QString phrase);
    static QString getAllAscii();
    static void nextChar(QChar* x, const QString *pattern);
    static void nextString(QString *input, const QString *pattern);
    static QString getStringAt(const qint64 pos, const QString &pattern);
    static quint64 getStringCurrentPos(const QString &input,const QString &pattern);
    static bool matchPattern(const QString &input, const QString &pattern);
    static QString removeDoublesChar(const QString &input);
    static quint64 getPasswordPossibility(const QString &pattern, const int lenght);
    static QString insert(const QString &input, const QString &add, const int evry = 1);
    static QString strstr(const QChar x,const int lenght);
    static int boolToInt(const bool input);
    static bool toBool(const QString &input);

signals:

public slots:
    
};

#endif // QSTRINGTOOLS_H
