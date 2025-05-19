#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <vector>
#include <algorithm>

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
    Conjunto<T> interseccion(const Conjunto<T> &other) const {
        Conjunto<T> res;
        for (const auto &e : elems) if (other.pertenece(e)) res.insertar(e);
        return res;
    }
    int cardinal() const { return elems.size(); }
    std::vector<T> obtenerVector() const { return elems; }
};

#endif // CONJUNTO_H
