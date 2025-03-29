#include <QTest>
#include <QSignalSpy>
#include "../src/controller/authcontroller.h"
#include "../src/view/errorwindow.h"

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
};

void TestAuthController::initTestCase()
{
    // Подготовка тестовой базы данных
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(":memory:");
    QVERIFY(m_db.open());

    // Создание таблицы
    QSqlQuery query;
    query.exec("CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT UNIQUE, password TEXT, balance INTEGER DEFAULT 0)");

    m_controller = new AuthController();
}

void TestAuthController::testRegistration()
{
    QSignalSpy errorSpy(m_controller, &AuthController::error);
    
    // Тест успешной регистрации
    m_controller->registerUser("testuser", "testpass");
    QSqlQuery query;
    query.exec("SELECT * FROM users WHERE name = 'testuser'");
    QVERIFY(query.next());
    
    // Тест дублирования пользователя
    m_controller->registerUser("testuser", "testpass");
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
    
    // Тест пополнения баланса
    m_controller->updateBalance(100, false);
    QSqlQuery query;
    query.exec("SELECT balance FROM users WHERE name = 'testuser'");
    query.next();
    QCOMPARE(query.value(0).toInt(), 100);
    
    // Тест снятия средств
    m_controller->updateBalance(50, true);
    query.exec("SELECT balance FROM users WHERE name = 'testuser'");
    query.next();
    QCOMPARE(query.value(0).toInt(), 50);
    
    // Тест снятия больше баланса
    m_controller->updateBalance(100, true);
    QCOMPARE(errorSpy.count(), 1);
}

void TestAuthController::cleanupTestCase()
{
    delete m_controller;
    m_db.close();
}

QTEST_MAIN(TestAuthController)
#include "test_auth_controller.moc" 