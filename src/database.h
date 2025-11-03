#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include "student.h"

class StudentDatabase {
private:
    std::vector<Student> students;
    
public:
    void addStudent(const Student& student);
    void addStudentInteractive();
    void displayAll() const;
    void saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
    
    bool isEmpty() const { return students.empty(); }
    size_t getCount() const { return students.size(); }
    const Student& getStudent(size_t index) const { return students[index]; }
    void clear() { students.clear(); }
    bool contains(const Student& student) const;
};

#endif