#include "../include/produs.hpp"
#include <iostream>

Produs::Produs(const std::string& cod, const std::string& n,
               const std::string& cat, double pr, int s,
               const std::string& m)
    : codBare(cod), nume(n), categorie(cat), pret(pr), stoc(s), marime(m) {
    if (pret < 0) pret = 0;
}

std::string Produs::getCodBare() const { return codBare; }
std::string Produs::getNume() const { return nume; }
std::string Produs::getMarime() const { return marime; }
double Produs::getPret() const { return pret; }
int Produs::getStoc() const { return stoc; }

bool Produs::inStoc(int cant) const {
    return stoc >= cant;
}

std::ostream& operator<<(std::ostream& os, const Produs& p) {
    os << p.nume << " [" << p.codBare << "] $" << p.pret << " Stoc:" << p.stoc;
    return os;
}