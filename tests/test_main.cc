#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>
#include <cstdio>
#include "../src/database.h"
#include "../src/input_utils.h"

// Вспомогательная функция для тестирования ввода
class TestInputHelper {
public:
    TestInputHelper(const std::string& input) {
        old_cin = std::cin.rdbuf();
        test_input.str(input);
        std::cin.rdbuf(test_input.rdbuf());
    }
    
    ~TestInputHelper() {
        std::cin.rdbuf(old_cin);
    }

private:
    std::streambuf* old_cin;
    std::stringstream test_input;
};

void printTestHeader(const std::string& testName) {
    std::cout << "🧪 " << testName << "\n";
}

void printTestStep(const std::string& step) {
    std::cout << "   ↳ " << step << "\n";
}

void testAddStudent() {
    printTestHeader("Тест 1: Добавление студента");
    
    StudentDatabase db;
    Student student{"Иван Иванов", 20, "Информатика", 3.8};
    
    printTestStep("Создана пустая база данных");
    assert(db.isEmpty());
    printTestStep("База пуста - ✓");
    
    printTestStep("Добавляем студента: " + student.name);
    db.addStudent(student);
    
    assert(db.getCount() == 1);
    printTestStep("Количество студентов: 1 - ✓");
    
    assert(db.contains(student));
    printTestStep("Студент найден в базе - ✓");
    
    const Student& retrieved = db.getStudent(0);
    assert(retrieved.name == "Иван Иванов");
    assert(retrieved.age == 20);
    assert(retrieved.major == "Информатика");
    assert(retrieved.gpa == 3.8);
    printTestStep("Данные студента корректны - ✓");
    
    std::cout << "   ✅ Успешно\n\n";
}

void testMultipleStudents() {
    printTestHeader("Тест 2: Добавление нескольких студентов");
    
    StudentDatabase db;
    
    Student s1{"Анна Петрова", 19, "Математика", 3.9};
    Student s2{"Петр Сидоров", 21, "Физика", 3.5};
    Student s3{"Мария Козлова", 20, "Химия", 4.0};
    
    printTestStep("Добавляем первого студента: " + s1.name);
    db.addStudent(s1);
    
    printTestStep("Добавляем второго студента: " + s2.name);
    db.addStudent(s2);
    
    printTestStep("Добавляем третьего студента: " + s3.name);
    db.addStudent(s3);
    
    assert(db.getCount() == 3);
    printTestStep("Общее количество студентов: 3 - ✓");
    
    assert(db.contains(s1));
    printTestStep("Первый студент найден - ✓");
    
    assert(db.contains(s2));
    printTestStep("Второй студент найден - ✓");
    
    assert(db.contains(s3));
    printTestStep("Третий студент найден - ✓");
    
    std::cout << "   ✅ Успешно\n\n";
}

void testSaveAndLoad() {
    printTestHeader("Тест 3: Сохранение и загрузка из файла");
    
    StudentDatabase db1;
    
    Student s1{"Тест Студент", 22, "Тестология", 3.7};
    Student s2{"Другой Студент", 23, "Другая Наука", 3.2};
    
    printTestStep("Создаем первую базу с 2 студентами");
    db1.addStudent(s1);
    db1.addStudent(s2);
    
    const std::string filename = "test_db.txt";
    printTestStep("Сохраняем базу в файл: " + filename);
    db1.saveToFile(filename);
    
    printTestStep("Создаем вторую пустую базу");
    StudentDatabase db2;
    assert(db2.isEmpty());
    
    printTestStep("Загружаем данные из файла во вторую базу");
    bool loaded = db2.loadFromFile(filename);
    
    assert(loaded);
    printTestStep("Файл загружен успешно - ✓");
    
    assert(db2.getCount() == 2);
    printTestStep("Загружено 2 студента - ✓");
    
    assert(db2.contains(s1));
    printTestStep("Первый студент загружен корректно - ✓");
    
    assert(db2.contains(s2));
    printTestStep("Второй студент загружен корректно - ✓");
    
    printTestStep("Удаляем тестовый файл");
    std::remove(filename.c_str());
    
    std::cout << "   ✅ Успешно\n\n";
}

void testEmptyDatabase() {
    printTestHeader("Тест 4: Работа с пустой базой");
    
    StudentDatabase db;
    
    assert(db.isEmpty());
    printTestStep("Новая база пуста - ✓");
    
    assert(db.getCount() == 0);
    printTestStep("Количество студентов: 0 - ✓");
    
    const std::string filename = "empty_test.txt";
    printTestStep("Сохраняем пустую базу в файл: " + filename);
    db.saveToFile(filename);
    
    printTestStep("Проверяем что файл создан");
    std::ifstream file(filename);
    assert(file.good());
    file.close();
    printTestStep("Файл создан успешно - ✓");
    
    printTestStep("Удаляем тестовый файл");
    std::remove(filename.c_str());
    
    std::cout << "   ✅ Успешно\n\n";
}

void testFileErrorHandling() {
    printTestHeader("Тест 5: Обработка ошибок файловых операций");
    
    StudentDatabase db;
    
    const std::string badFilename = "nonexistent_file_12345.txt";
    printTestStep("Пытаемся загрузить несуществующий файл: " + badFilename);
    bool loaded = db.loadFromFile(badFilename);
    
    assert(!loaded);
    printTestStep("Загрузка правильно завершилась ошибкой - ✓");
    
    assert(db.isEmpty());
    printTestStep("База осталась пустой после ошибки - ✓");
    
    std::cout << "   ✅ Успешно\n\n";
}

void testInputUtils() {
    printTestHeader("Тест 6: Тестирование утилит ввода");
    
    // Тест 1: getInt с обработкой ошибок
    {
        // Сохраняем оригинальные буферы
        std::streambuf* orig_cin = std::cin.rdbuf();
        std::streambuf* orig_cout = std::cout.rdbuf();
        
        // Создаем тестовые потоки
        std::stringstream test_input;
        std::stringstream test_output;
        
        // Настраиваем тестовый ввод
        test_input.str("invalid\n150\n-5\n30\n");
        std::cin.rdbuf(test_input.rdbuf());
        std::cout.rdbuf(test_output.rdbuf());
        
        // Вызываем тестируемую функцию
        int result = InputUtils::getInt("Введите число: ", 0, 100);
        
        // Проверяем результат
        assert(result == 30);
        
        // Восстанавливаем буферы
        std::cin.rdbuf(orig_cin);
        std::cout.rdbuf(orig_cout);
        
        printTestStep("getInt корректно обрабатывает ошибки ввода - ✓");
    }
    
    // Тест 2: getDouble с обработкой ошибок
    {
        std::streambuf* orig_cin = std::cin.rdbuf();
        std::streambuf* orig_cout = std::cout.rdbuf();
        
        std::stringstream test_input;
        std::stringstream test_output;
        
        test_input.str("abc\n5.0\n-1.0\n3.2\n");
        std::cin.rdbuf(test_input.rdbuf());
        std::cout.rdbuf(test_output.rdbuf());
        
        double result = InputUtils::getDouble("Введите GPA: ", 0.0, 4.0);
        
        assert(result == 3.2);
        
        std::cin.rdbuf(orig_cin);
        std::cout.rdbuf(orig_cout);
        
        printTestStep("getDouble корректно обрабатывает ошибки ввода - ✓");
    }
    
    // Тест 3: getString
    {
        std::streambuf* orig_cin = std::cin.rdbuf();
        std::streambuf* orig_cout = std::cout.rdbuf();
        
        std::stringstream test_input;
        std::stringstream test_output;
        
        test_input.str("Test String\n");
        std::cin.rdbuf(test_input.rdbuf());
        std::cout.rdbuf(test_output.rdbuf());
        
        std::string result = InputUtils::getString("Введите текст: ");
        
        assert(result == "Test String");
        
        std::cin.rdbuf(orig_cin);
        std::cout.rdbuf(orig_cout);
        
        printTestStep("getString корректно работает - ✓");
    }
    
    // Тест 4: clearInputBuffer - просто проверяем что не падает
    {
        // Временно подавляем вывод
        std::streambuf* orig_cout = std::cout.rdbuf();
        std::stringstream null_stream;
        std::cout.rdbuf(null_stream.rdbuf());
        
        InputUtils::clearInputBuffer();
        
        std::cout.rdbuf(orig_cout);
        printTestStep("clearInputBuffer выполняется без ошибок - ✓");
    }
    
    std::cout << "   ✅ Успешно\n\n";
}

void testStudentComparison() {
    printTestHeader("Тест 7: Сравнение студентов");
    
    Student s1{"Иван Иванов", 20, "Информатика", 3.8};
    Student s2{"Иван Иванов", 20, "Информатика", 3.8};
    Student s3{"Петр Петров", 21, "Математика", 3.9};
    
    assert(s1 == s2);
    printTestStep("Одинаковые студенты равны - ✓");
    
    assert(!(s1 == s3));
    printTestStep("Разные студенты не равны - ✓");
    
    std::cout << "   ✅ Успешно\n\n";
}

void runAllTests() {
    std::cout << "🎯 === Запуск тестовой системы ===\n\n";
    
    testAddStudent();
    testMultipleStudents();
    testSaveAndLoad();
    testEmptyDatabase();
    testFileErrorHandling();
    testInputUtils();
    testStudentComparison();
    
    std::cout << "🎉 === Все тесты пройдены успешно! ===\n";
    std::cout << "📊 Итог: 7 тестов, 0 failures\n";
}

int main() {
    runAllTests();
    return 0;
}