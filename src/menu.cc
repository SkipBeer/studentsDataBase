#include "menu.h"
#include "input_utils.h"
#include <iostream>

void Menu::showMenu() const {
    std::cout << "\n=== Система управления студентами ===\n";
    std::cout << "Текущее количество студентов: " << database.getCount() << "\n";
    std::cout << "1. Добавить студента\n";
    std::cout << "2. Вывести список студентов\n";
    std::cout << "3. Сохранить базу в файл\n";
    std::cout << "4. Загрузить базу из файла\n";
    std::cout << "0. Выход\n";
}

void Menu::handleChoice(int choice) {
    switch (choice) {
        case 1:
            database.addStudentInteractive();
            break;
        case 2:
            database.displayAll();
            break;
        case 3:
            getFilenameAndSave();
            break;
        case 4:
            getFilenameAndLoad();
            break;
        case 0:
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
    }
}

void Menu::getFilenameAndSave() {
    std::string filename = InputUtils::getString("Введите имя файла для сохранения: ");
    database.saveToFile(filename);
}

void Menu::getFilenameAndLoad() {
    std::string filename = InputUtils::getString("Введите имя файла для загрузки: ");
    database.loadFromFile(filename);
}

void Menu::run() {
    int choice;    
    do {
        showMenu();
        choice = InputUtils::getInt("Выберите действие: ", 0, 4);
        handleChoice(choice);
    } while (choice != 0);
}