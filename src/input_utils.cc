#include "input_utils.h"

void InputUtils::clearInputBuffer() {
    std::cin.clear();
    if (std::cin.rdbuf()->in_avail() > 0) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int InputUtils::getInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail() || value < min || value > max) {
            std::cout << "Ошибка! Введите целое число от " << min << " до " << max << ".\n";
            clearInputBuffer();
        } else {
            clearInputBuffer();
            return value;
        }
    }
}

double InputUtils::getDouble(const std::string& prompt, double min, double max) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail() || value < min || value > max) {
            std::cout << "Ошибка! Введите число от " << min << " до " << max << ".\n";
            clearInputBuffer();
        } else {
            clearInputBuffer();
            return value;
        }
    }
}

std::string InputUtils::getString(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}