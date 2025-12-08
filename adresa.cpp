#include "../include/adresa.hpp"

Adresa::Adresa(const std::string& str, const std::string& ors, 
               const std::string& cp, int nrAp)
    : strada(str), oras(ors), codPostal(cp), numarApartament(nrAp) {
    curatareDate();
}

void Adresa::curatareDate() {
    if (numarApartament < 0) numarApartament = 0;
}

std::string Adresa::adresaCompleta() const {
    return strada + " Nr:" + std::to_string(numarApartament) + 
           ", " + oras + " " + codPostal;
}

std::ostream& operator<<(std::ostream& os, const Adresa& adresa) {
    os << "Adresa: " << adresa.adresaCompleta();
    return os;
}