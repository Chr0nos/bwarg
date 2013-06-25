#ifndef QCRC32_H
#define QCRC32_H

#include <QObject>
#include <QString>
#include <QByteArray>

class QCrc32 : public QObject
{
    Q_OBJECT
public:
    explicit QCrc32(QObject *parent = 0);
    static quint32 crc32_tab[];
    static quint32 getCrc32(const char *data, size_t size);
    static quint32 getCrc32(const QByteArray &data);
    static QString getCrc32Hex(const QByteArray &data);
    static QString getCrc32Hex(const QString &data);

signals:
    
public slots:
    
};

#endif // QCRC32_H
