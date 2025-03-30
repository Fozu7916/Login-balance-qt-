#include <QTest>
#include <QSignalSpy>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "../src/controller/authcontroller.h"
#include "../src/model/database.h"


class TestAuthController : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testRegistration();
    void testLogin();
    void testUpdateBalance();
    void cleanupTestCase();

private:
    AuthController* m_controller;
    QSqlDatabase m_db;
    DataBase* m_database;
};

void TestAuthController::initTestCase()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(":memory:");
    QVERIFY(m_db.open());

    QSqlQuery query;
    QVERIFY(query.exec("CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "Name TEXT UNIQUE, Hash_Password TEXT, Money INTEGER DEFAULT 0)"));

    m_database = new DataBase(m_db);
    m_controller = new AuthController(*m_database);
}

void TestAuthController::testRegistration()
{
    QSignalSpy errorSpy(m_controller, &AuthController::error);
    
    // Тест успешной регистрации
    m_controller->reg("testuser", "testpass", "testpass");
    QSqlQuery query;
    QVERIFY(query.exec("SELECT * FROM users WHERE Name = 'testuser'"));
    QVERIFY(query.next());
    
    // Тест дублирования пользователя
    m_controller->reg("testuser", "testpass", "testpass");
    QCOMPARE(errorSpy.count(), 1);
}

void TestAuthController::testLogin()
{
    QSignalSpy errorSpy(m_controller, &AuthController::error);
    QSignalSpy successSpy(m_controller, &AuthController::moneyWindowRequested);
    
    // Тест успешного входа
    m_controller->login("testuser", "testpass");
    QCOMPARE(successSpy.count(), 1);
    
    // Тест неверного пароля
    m_controller->login("testuser", "wrongpass");
    QCOMPARE(errorSpy.count(), 1);
}

void TestAuthController::testUpdateBalance()
{
    QSignalSpy errorSpy(m_controller, &AuthController::error);
    QSignalSpy moneyChangedSpy(m_controller, &AuthController::moneyChanged);
    
    // Тест пополнения баланса
    m_controller->updateBalance(false, 100);
    QSqlQuery query;
    QVERIFY(query.exec("SELECT Money FROM users WHERE Name = 'testuser'"));
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 100);
    QCOMPARE(moneyChangedSpy.count(), 1);
    
    // Тест снятия средств
    m_controller->updateBalance(true, 50);
    QVERIFY(query.exec("SELECT Money FROM users WHERE Name = 'testuser'"));
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toInt(), 50);
    QCOMPARE(moneyChangedSpy.count(), 2);
    
    // Тест снятия больше баланса
    m_controller->updateBalance(true, 100);
    QCOMPARE(errorSpy.count(), 1);
}

void TestAuthController::cleanupTestCase()
{
    delete m_controller;
    delete m_database;
    m_db.close();
}

QTEST_MAIN(TestAuthController)
#include "test_auth_controller.moc"
