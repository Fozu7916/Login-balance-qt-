#ifndef HASHUTILS_H
#define HASHUTILS_H

#include <QString>
#include <QCryptographicHash>

class HashUtils {
public:
    static QString hashPassword(const QString& password) {
        QByteArray data = password.toUtf8();
        QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Sha256);
        return hash.toHex();
    }
};

#endif // HASHUTILS_H 