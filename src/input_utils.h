#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <iostream>
#include <string>
#include <limits>

class InputUtils {
public:
    static int getInt(const std::string& prompt, int min = 0, int max = 150);
    static double getDouble(const std::string& prompt, double min = 0.0, double max = 4.0);
    static std::string getString(const std::string& prompt);
    static void clearInputBuffer();
};

#endif