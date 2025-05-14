#include "Section.h"

Section::Section(const std::string &name_, const std::vector<int> &blocks_)
    : name(name_), blocks(blocks_) {
    initSchedule();
}

void Section::addStudent(long ci) {
    students.insertar(ci);
}

void Section::setProfessor(const std::string &name, long ci) {
    professor.name = name;
    professor.ci = ci;
}

void Section::initSchedule() {
    schedule.clear();
    schedule.reserve(blocks.size());
    for (int dur : blocks) {
        schedule.push_back(BlockSchedule{0, dur});
    }
}
