#ifndef SECTION_H
#define SECTION_H

#include <string>
#include <vector>
#include "Conjunto.h"

struct Professor {
    std::string name;
    long ci;
};

struct BlockSchedule {
    int start_hour;
    int duration;
    int end_hour() const { return start_hour + duration; }
};

class Section {
public:
    std::string name;
    std::vector<int> blocks;
    Professor professor;
    Conjunto<long> students;
    std::vector<BlockSchedule> schedule;

    Section(const std::string &name_, const std::vector<int> &blocks_);
    void addStudent(long ci);
    void setProfessor(const std::string &name, long ci);
    void initSchedule();
};

#endif // SECTION_H
