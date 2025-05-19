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
        std::vector<bool> used(n, false);
        for (int k = 0; k < n; ++k) {
            int best = -1, bestConf = -1;
            for (int i = 0; i < n; ++i) if (!used[i]) {
                int cnt = 0;
                for (int j = 0; j < n; ++j) {
                    if (used[j] && conflict(sections[i], sections[j])) cnt++;
                }
                if (cnt > bestConf) { bestConf = cnt; best = i; }
            }
            used[best] = true;
            order[k] = best;
        }
    }

    for (auto &sec : sections) sec.initSchedule();

    for (int idx : order) {
        Section &sec = sections[idx];
        std::vector<bool> bad(11, false);
        for (auto &other : sections) {
            if (&other == &sec) continue;
            if (conflict(sec, other)) {
                for (auto &b : other.schedule) {
                    if (b.start_hour > 0) {
                        int start = b.start_hour - 7;
                        int len = b.end_hour() - b.start_hour;
                        for (int s = start; s < start + len; ++s)
                            if (s >= 0 && s < 11) bad[s] = true;
                    }
                }
            }
        }
        int totalH = 0, twoCount = 0;
        int maxTwo = std::count(sec.blocks.begin(), sec.blocks.end(), 2);
        for (size_t i = 0; i < sec.blocks.size(); ++i) {
            int dur = sec.blocks[i];
            if (dur == 2 && twoCount >= maxTwo) continue;
            for (int s = 0; s + dur <= 11; ++s) {
                if (totalH + dur > 4) break;
                bool ok = true;
                for (int k = 0; k < dur; ++k) if (bad[s + k]) { ok = false; break; }
                if (!ok) continue;
                sec.schedule[i].start_hour = s + 7;
                for (int k = 0; k < dur; ++k) bad[s + k] = true;
                totalH += dur;
                if (dur == 2) twoCount++;
                break;
            }
        }
    }
}

int main() {
    std::cout << "Ingrese nombre de archivo de secciones (o 'salir'): " << std::flush;
    std::string infile;
    if (!std::getline(std::cin, infile) || infile == "salir") return 0;
    if (infile.find('.') == std::string::npos) infile += ".txt";
    std::ifstream fin(infile);
    if (!fin) { std::cerr << "Error al abrir " << infile << std::endl; return 1; }

    std::vector<Section> sections;
    std::string line;
    while (std::getline(fin, line)) {
        line = trim(line);
        if (line.rfind("Seccion:", 0) != 0) continue;
        std::string name = trim(line.substr(8));
        std::getline(fin, line); // Facultad
        std::getline(fin, line); // Escuela
        std::getline(fin, line); // Cátedra
        std::getline(fin, line); // Profesor: name, ci:###
        auto pos = line.find("ci:");
        std::string profName = trim(line.substr(9, pos - 10));
        long profCi = std::stol(trim(line.substr(pos + 3)));
        std::getline(fin, line); // Bloques: ...
        std::istringstream bs(line.substr(line.find(':')+1));
        std::vector<int> blks;
        for (int v; bs >> v; ) blks.push_back(v);
        Section sec(name, blks);
        sec.setProfessor(profName, profCi);
        std::getline(fin, line); // Estudiantes:
        while (std::getline(fin, line) && !trim(line).empty() && line.rfind("Seccion:",0)!=0) {
            auto p = line.find("ci:");
            if (p!=std::string::npos) {
                long sci = std::stol(trim(line.substr(p+3)));
                sec.addStudent(sci);
            }
        }
        sections.push_back(sec);
        if (line.rfind("Seccion:",0)==0) fin.seekg(-static_cast<int>(line.size()), std::ios::cur);
    }

    std::cout << "Seleccione estrategia (1=original,2=inverso,3=conflicto): " << std::flush;
    int opt; std::cin >> opt; std::cin.ignore();
    assignDay(sections, opt);

    std::cout << "Nombre archivo salida (sin .txt): " << std::flush;
    std::string outName; std::getline(std::cin, outName);
    if (outName.find('.')==std::string::npos) outName += ".txt";
    std::ofstream fout(outName);

    fout << "Asignacion horaria de este dia" << '\n';
    fout << "============================" << '\n';
    for (auto &s : sections) {
        fout << "Seccion: " << s.name << '\n';
        fout << "Profesor: " << s.professor.name << " (ci=" << s.professor.ci << ")" << '\n';
        fout << "Horario:" << '\n';
        for (size_t i=0;i<s.schedule.size();++i) {
            auto &b = s.schedule[i];
            int dur = s.blocks[i];
            if (b.start_hour>0) {
                int st=b.start_hour, en=st+dur;
                fout << "  " << std::setw(2)<<st<<":00 - "<<std::setw(2)<<en<<":00"<< '\n';
            }
        }
        fout << "Estudiantes (ci): ";
        for (auto id: s.students.obtenerVector()) fout<<id<<" ";
        fout << '\n'<<"----------------------------"<<'\n';
    }

    std::cout<<"Mostrar en pantalla? (s/n): "<<std::flush;
    char c; std::cin>>c;
    if (c=='s'||c=='S'){
        std::cout<<"\n--- Resumen ---\n";
        for(auto &s:sections){
            std::cout<<s.name<<" ["<<s.professor.name<<"] ";
            for(auto &b:s.schedule) if(b.start_hour>0)
                std::cout<<"("<<b.start_hour<<"-"<<b.end_hour()<<")";
            std::cout<<'\n';
        }
    }
    return 0;
}