// Conjunto.h (de Lab3)
#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <vector>
#include <algorithm>

// Plantilla de conjunto simple
template<typename T>
class Conjunto {
private:
    std::vector<T> elems;
public:
    void insertar(const T &e) {
        if (!pertenece(e)) elems.push_back(e);
    }
    bool pertenece(const T &e) const {
        return std::find(elems.begin(), elems.end(), e) != elems.end();
    }
    void eliminar(const T &e) {
        elems.erase(std::remove(elems.begin(), elems.end(), e), elems.end());
    }
};

#endif // CONJUNTO_H


// Section.h
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


// Section.cpp
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


// main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include "Section.h"

// Función para recortar espacios al inicio y fin
static inline std::string trim(const std::string &s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    return (start == std::string::npos) ? std::string() : s.substr(start, end - start + 1);
}

int main() {
    std::ifstream infile("datos.txt");
    if (!infile) {
        std::cerr << "Error al abrir datos.txt\n";
        return 1;
    }

    std::vector<Section> sections;
    std::string line;
    while (std::getline(infile, line)) {
        line = trim(line);
        if (line.empty()) continue;
        std::istringstream ss(line);
        std::string secName, blocksPart, profPart, studentsPart;

        std::getline(ss, secName, ';');
        std::getline(ss, blocksPart, ';');
        std::getline(ss, profPart, ';');
        std::getline(ss, studentsPart);

        secName = trim(secName);
        blocksPart = trim(blocksPart);
        profPart = trim(profPart);
        studentsPart = trim(studentsPart);

        // Parse blocks
        std::vector<int> blocks;
        std::istringstream bs(blocksPart);
        std::string tok;
        while (std::getline(bs, tok, ',')) {
            tok = trim(tok);
            if (!tok.empty()) blocks.push_back(std::stoi(tok));
        }

        Section sec(secName, blocks);

        // Parse profesor: "Nombre,CI"
        {
            std::istringstream ps(profPart);
            std::string name, ciStr;
            std::getline(ps, name, ',');
            std::getline(ps, ciStr, ',');
            name = trim(name);
            ciStr = trim(ciStr);
            long ci = 0;
            if (!ciStr.empty()) {
                try { ci = std::stol(ciStr); }
                catch (...) { ci = 0; }
            }
            sec.setProfessor(name, ci);
        }

        // Parse students
        {
            std::istringstream es(studentsPart);
            while (std::getline(es, tok, ',')) {
                tok = trim(tok);
                if (!tok.empty()) {
                    try { sec.addStudent(std::stol(tok)); }
                    catch (...) { /* omitir */ }
                }
            }
        }

        sections.push_back(sec);
    }

    // Input de horarios
    for (auto &sec : sections) {
        std::cout << "Sección " << sec.name << " (Prof. "
                  << sec.professor.name << "):\n";
        for (size_t i = 0; i < sec.blocks.size(); ++i) {
            int h;
            do {
                std::cout << "  Bloque " << (i+1)
                          << " (" << sec.blocks[i] << "h) iniciar a las (0-23): ";
                std::cin >> h;
            } while (h < 0 || h > 23);
            sec.schedule[i].start_hour = h;
        }
        std::cout << "\n";
    }

    // Mostrar tabla
    std::cout << std::left << std::setw(12) << "Sección"
              << std::setw(15) << "Profesor";
    for (size_t i = 0; i < 3; ++i)
        std::cout << std::setw(15) << (std::string("Bloque") + std::to_string(i+1));
    std::cout << "\n";

    for (const auto &sec : sections) {
        std::cout << std::setw(12) << sec.name
                  << std::setw(15) << sec.professor.name;
        for (size_t i = 0; i < sec.schedule.size(); ++i) {
            int start = sec.schedule[i].start_hour;
            int end = sec.schedule[i].end_hour();
            std::ostringstream os;
            os << start << ":00-" << end << ":00";
            std::cout << std::setw(15) << os.str();
        }
        std::cout << "\n";
    }

    return 0;
}