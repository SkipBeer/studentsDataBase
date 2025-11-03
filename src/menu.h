#ifndef MENU_H
#define MENU_H

#include "database.h"

class Menu {
private:
    StudentDatabase database;
    
    void showMenu() const;
    void handleChoice(int choice);
    void getFilenameAndSave();
    void getFilenameAndLoad();
    
public:
    void run();
};

#endif