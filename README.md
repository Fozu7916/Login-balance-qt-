# Система управления балансом

## Описание
Приложение для управления балансом пользователя с возможностью регистрации, авторизации и проведения операций с деньгами (пополнение/снятие).

## Архитектура
Проект построен на паттерне MVC (Model-View-Controller):

### Model
- База данных MySql для хранения данных пользователей
- Таблица users содержит:
  - name (varchar(255) UNIQUE)
  - password (varchar(255))
  - balance (INTEGER)

### View
- MainWindow - главное окно с формой входа
- RegistrWindow - окно регистрации
- MoneyChange - окно пополнения/снятия средств
- MoneyWindow - окно управления балансом
- ErrorWindow - окно отображения ошибок

### Controller
- AuthController - управляет авторизацией и операциями с балансом

## Функциональность
1. Регистрация пользователя
   - Проверка уникальности имени
   - Шифрование пароля
   
2. Авторизация
   - Проверка существования пользователя
   - Валидация пароля
   
3. Управление балансом
   - Пополнение счета
   - Снятие средств
   - Проверка достаточности средств

## Требования
- Qt 6.0 или выше
- C++17 или выше
- MySql

## Установка
1. Клонировать репозиторий
2. Открыть проект в Qt Creator
3. Настроить сборку
4. Запустить приложение

## Тестирование
Для запуска тестов:
1. Перейти в директорию tests
2. Выполнить `qmake`
3. Выполнить `make`
4. Запустить тесты

## Безопасность
- Пароли хранятся в зашифрованном виде
- Используются подготовленные SQL-запросы
- Проверка входных данных
- Защита от SQL-инъекций

## Лицензия
MIT License 