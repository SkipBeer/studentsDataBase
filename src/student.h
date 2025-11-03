#ifndef STUDENT_H
#define STUDENT_H

#include <string>

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
    
    bool operator==(const Student& other) const {
        return name == other.name && 
               age == other.age && 
               major == other.major && 
               gpa == other.gpa;
    }
};

#endif