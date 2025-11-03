#include "database.h"
#include "input_utils.h"
#include <iostream>
#include <fstream>

void StudentDatabase::addStudent(const Student& student) {
    students.push_back(student);
}

void StudentDatabase::addStudentInteractive() {
    Student student;
    
    std::cout << "\n--- Добавление студента ---\n";
    student.name = InputUtils::getString("Введите имя студента: ");
    student.age = InputUtils::getInt("Введите возраст студента: ", 16, 100);
    student.major = InputUtils::getString("Введите специальность студента: ");
    student.gpa = InputUtils::getDouble("Введите средний балл студента: ", 0.0, 4.0);

    students.push_back(student);
    std::cout << "Студент '" << student.name << "' добавлен в базу данных.\n";
}

void StudentDatabase::displayAll() const {
    if (students.empty()) {
        std::cout << "База данных пуста.\n";
        return;
    }

    std::cout << "\n--- Список студентов ---\n";
    for (size_t i = 0; i < students.size(); ++i) {
        std::cout << "Студент #" << i + 1 << ":\n";
        std::cout << "  Имя: " << students[i].name << "\n";
        std::cout << "  Возраст: " << students[i].age << "\n";
        std::cout << "  Специальность: " << students[i].major << "\n";
        std::cout << "  Средний балл: " << students[i].gpa << "\n\n";
    }
}

void StudentDatabase::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла '" << filename << "' для записи!\n";
        return;
    }

    for (const auto& student : students) {
        file << student.name << "\n"
             << student.age << "\n"
             << student.major << "\n"
             << student.gpa << "\n";
    }

    std::cout << "Данные успешно сохранены в файл '" << filename << "'\n";
}

bool StudentDatabase::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла '" << filename << "' для чтения!\n";
        return false;
    }

    students.clear();
    Student student;
    std::string line;
    
    while (std::getline(file, student.name) &&
           std::getline(file, line)) {
        
        try {
            student.age = std::stoi(line);
        } catch (const std::exception& e) {
            std::cout << "Ошибка чтения возраста из файла.\n";
            continue;
        }
        
        if (!std::getline(file, student.major) ||
            !std::getline(file, line)) {
            break;
        }
        
        try {
            student.gpa = std::stod(line);
        } catch (const std::exception& e) {
            std::cout << "Ошибка чтения GPA из файла.\n";
            continue;
        }
        
        students.push_back(student);
    }

    std::cout << "Загружено " << students.size() << " студентов из файла '" << filename << "'\n";
    return true;
}

bool StudentDatabase::contains(const Student& student) const {
    for (const auto& s : students) {
        if (s.name == student.name && 
            s.age == student.age && 
            s.major == student.major && 
            s.gpa == student.gpa) {
            return true;
        }
    }
    return false;
}