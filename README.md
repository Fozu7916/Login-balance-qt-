# BalanceManager — Система управления балансом на Qt

![Qt](https://img.shields.io/badge/Qt-6.x-green)
![C++](https://img.shields.io/badge/C%2B%2B-17-blue)

## Описание

BalanceManager — это простое, но функциональное приложение для управления балансом пользователя с поддержкой MySQL. Приложение позволяет:
- Регистрировать и авторизовывать пользователей
- Просматривать и изменять баланс (пополнение/снятие)
- Просматривать историю операций
- Безопасно хранить пароли (хеширование)
- Использовать современный интерфейс на Qt

## Скриншот
![Скриншот](https://github.com/user-attachments/assets/28d701ca-10d9-46d8-8ca9-0dcb9091a0d7)

## Как собрать

1. Установите Qt 6.x, CMake и MySQL
2. Клонируйте репозиторий:
   ```bash
   git clone https://github.com/yourname/BalanceManager.git
   cd BalanceManager
   ```
3. Убедитесь, что в вашей системе установлен драйвер Qt для MySQL (QMYSQL)
4. Соберите проект:
   ```bash
   mkdir build
   cd build
   cmake .. -G "Ninja Multi-Config" -DCMAKE_BUILD_TYPE=Release
   cmake --build . --config Release
   ```
5. Запустите `BalanceManager.exe`

## Зависимости
- [Qt 6.x](https://www.qt.io/download)
- [MySQL](https://www.mysql.com/)
- [QSQLDriver](https://github.com/thecodemonkey86/qt_mysql_driver)

## Структура проекта
```
BalanceManager/
├── src/
│   ├── model/         # Users, DataBase
│   ├── view/          # MainWindow, RegistrWindow, MoneyWindow, ErrorWindow
│   ├── controller/    # AuthController
│   └── hashutils.h    # Хеширование паролей
├── tests/             # Unit-тесты (Qt Test)
├── CMakeLists.txt
├── README.md
└── ...
```

## Тестирование

Тесты находятся в папке `tests/` и написаны с использованием Qt Test.

### Как запустить тесты

1. Соберите проект с помощью CMake, как указано выше.
2. В папке `build/tests/` (или аналогичной для вашей сборки) будут созданы исполняемые файлы тестов:
   - `test_auth_controller.exe`
3. Запустите тестовый исполняемый файл вручную или с помощью скрипта:
   ```bash
   ./test_auth_controller.exe
   ```
   или на Linux/Mac:
   ```bash
   ./test_auth_controller
   ```

## Лицензия

Этот проект распространяется под лицензией MIT. См. файл [LICENSE](LICENSE) для подробностей.
