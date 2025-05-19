#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include "Section.h"

static inline std::string trim(const std::string &s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    return (start == std::string::npos) ? std::string() : s.substr(start, end - start + 1);
}

bool conflict(const Section &a, const Section &b) {
    if (a.professor.ci == b.professor.ci) return true;
    return a.students.interseccion(b.students).cardinal() > 0;
}

void assignDay(std::vector<Section> &sections, int strategy) {
    int n = sections.size();
    std::vector<int> order(n);
    if (strategy == 1) {
        std::iota(order.begin(), order.end(), 0);
    } else if (strategy == 2) {
        for (int i = 0; i < n; ++i) order[i] = n - 1 - i;
    } else {
        std::vector<bool> used(n);
        for (int k = 0; k < n; ++k) {
            int best = -1, bestConf = -1;
            for (int i = 0; i < n; ++i) if (!used[i]) {
                int cnt = 0;
                for (int j = 0; j < n; ++j)
                    if (used[j] && conflict(sections[i], sections[j])) cnt++;
                if (cnt > bestConf) {
                    bestConf = cnt;
                    best = i;
                }
            }
            used[best] = true;
            order[k] = best;
        }
    }

    for (auto &sec : sections) sec.initSchedule();

    for (int idx : order) {
        Section &sec = sections[idx];
        int maxTwo = std::count(sec.blocks.begin(), sec.blocks.end(), 2);
        int twoCount = 0, totalH = 0;
        std::vector<bool> usedSlots(11, false);
        // mark forbidden
        for (auto &other : sections) {
            if (&other == &sec) continue;
            if (conflict(sec, other)) {
                for (auto &b : other.schedule) {
                    if (b.start_hour > 0) {
                        int start = b.start_hour - 7;
                        int len = b.end_hour() - b.start_hour;
                        for (int s = start; s < start + len; ++s)
                            if (s >= 0 && s < 11) usedSlots[s] = true;
                    }
                }
            }
        }
        // assign
        for (size_t i = 0; i < sec.blocks.size(); ++i) {
            int dur = sec.blocks[i];
            if (dur == 2 && twoCount >= maxTwo) continue;
            for (int s = 0; s + dur <= 11; ++s) {
                if (totalH + dur > 4) break;
                bool ok = true;
                for (int k = 0; k < dur; ++k)
                    if (usedSlots[s + k]) { ok = false; break; }
                if (!ok) continue;
                // assign block
                sec.schedule[i].start_hour = s + 7;
                for (int k = 0; k < dur; ++k) usedSlots[s + k] = true;
                if (dur == 2) twoCount++;
                totalH += dur;
                break;
            }
        }
    }
}

int main() {
    std::cout << "Ingrese nombre de archivo de secciones (o 'salir'): " << std::flush;
    std::string infileName;
    if (!std::getline(std::cin, infileName) || infileName == "salir") return 0;
    if (infileName.find('.') == std::string::npos) infileName += ".txt";

    std::ifstream infile(infileName);
    if (!infile) {
        std::cerr << "No se pudo abrir '" << infileName << "'\n";
        return 1;
    }

    std::vector<Section> sections;
    std::string line;
    while (std::getline(infile, line)) {
        line = trim(line);
        if (line.rfind("Seccion:", 0) != 0) continue;
        std::string name = trim(line.substr(8));
        // metadata
        std::getline(infile, line); // Facultad
        std::getline(infile, line); // Escuela
        std::getline(infile, line); // Catedra
        std::getline(infile, line); // Profesor
        auto ciPos = line.find("ci:");
        std::string profName = line.substr(9, ciPos - 10);
        long profCi = std::stol(trim(line.substr(ciPos + 3)));

        // Bloques
        std::getline(infile, line);
        auto colon = line.find(':');
        std::istringstream cnt(line.substr(colon+1));
        int blkCount; cnt >> blkCount;
        std::getline(infile, line);
        std::istringstream blks(line.substr(line.find(':')+1));
        std::vector<int> blocks(blkCount);
        for (int i = 0; i < blkCount; ++i) blks >> blocks[i];

        Section sec(name, blocks);
        sec.setProfessor(trim(profName), profCi);

        // Estudiantes
        std::getline(infile, line); // Estudiantes:
        while (std::getline(infile, line) && !line.empty() && line.rfind("Seccion:",0)!=0) {
            auto pos = line.find("ci:");
            if (pos == std::string::npos) continue;
            long sci = std::stol(trim(line.substr(pos+3)));
            sec.addStudent(sci);
        }
        sections.push_back(sec);
        if (line.rfind("Seccion:",0)==0)
            infile.seekg(-static_cast<int>(line.size()), std::ios::cur);
    }

    std::cout << "Seleccione estrategia (1=original,2=inverso,3=conflicto): " << std::flush;
    int opt; std::cin >> opt; std::cin.ignore();
    assignDay(sections, opt);

    std::cout << "Nombre de archivo de salida (sin extensión): " << std::flush;
    std::string outfile; std::getline(std::cin, outfile);
    if (outfile.find('.') == std::string::npos) outfile += ".txt";
    std::ofstream out(outfile);

    out << "Asignacion horaria de este dia" << '\n';
    out << "---------------------------" << '\n';
    for (auto &s : sections) {
        out << "Seccion: " << s.name << '\n';
        out << "Profesor: " << s.professor.name << " (ci=" << s.professor.ci << ")" << '\n';
        out << "Horario:" << '\n';
        for (auto &b : s.schedule) {
            if (b.start_hour > 0)
                out << "  " << std::setw(2) << b.start_hour << ":00 - "
                    << std::setw(2) << b.end_hour() << ":00" << '\n';
        }
        out << "Estudiantes (ci): ";
        for (auto id : s.students.obtenerVector()) out << id << ' ';
        out << '\n' << "---------------------------" << '\n';
    }

    std::cout << "Mostrar en pantalla? (s/n): " << std::flush;
    char show; std::cin >> show;
    if (show=='s'||show=='S') {
        std::cout << "\n--- Resumen en pantalla ---\n";
        for (auto &s: sections) {
            std::cout << s.name << " [Prof=" << s.professor.name << "] ";
            for (auto &b: s.schedule) if(b.start_hour>0)
                std::cout << "("<<b.start_hour<<"-"<<b.end_hour()<<")";
            std::cout<<'\n';
        }
    }
    return 0;
}