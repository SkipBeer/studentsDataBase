#include "menu.h"
#include "input_utils.h"

int main() {
    InputUtils::clearInputBuffer();
    Menu menu;
    menu.run();
    return 0;
}