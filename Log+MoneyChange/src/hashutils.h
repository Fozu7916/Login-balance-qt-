#ifndef HASHUTILS_H
#define HASHUTILS_H

#include <QString>
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QDebug>

class HashUtils {
public:
    static QString hashPassword(const QString& password) {
        
        QByteArray salt;
        salt.resize(16);
        for(int i = 0; i < 16; ++i) {
            salt[i] = QRandomGenerator::global()->generate() % 256;
        }

        QByteArray data;
        data.append(salt);
        data.append(password.toUtf8());

        QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Sha256);
        return salt.toHex() + ":" + hash.toHex();
    }


    static bool verifyPassword(const QString& password, const QString& hashedPassword) {
        QStringList parts = hashedPassword.split(":");
        if (parts.size() != 2) {
            qWarning() << "Неверный формат хеша пароля";
            return false;
        }

        QByteArray salt = QByteArray::fromHex(parts[0].toUtf8());
        QByteArray storedHash = QByteArray::fromHex(parts[1].toUtf8());


        QByteArray data;
        data.append(salt);
        data.append(password.toUtf8());

        QByteArray computedHash = QCryptographicHash::hash(data, QCryptographicHash::Sha256);
        return computedHash == storedHash;
    }

private:
    HashUtils() = delete;
    ~HashUtils() = delete;
};

#endif // HASHUTILS_H 