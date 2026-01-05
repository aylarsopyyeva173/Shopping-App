#include "ierarhie.hpp"
#include <iostream>
#include <algorithm>

int Plata::numarTotalPlati = 0;

Plata::Plata(const std::string& id, double s, const std::string& m)
    : idPlata(id), suma(s), metoda(m) {
    numarTotalPlati++;
}

std::string Plata::getDetalii() const {
    return "Plata ID: " + idPlata + ", Suma: $" + 
           std::to_string(suma) + ", Metoda: " + metoda;
}

void Plata::afiseazaDetalii() const {
    std::cout << getDetalii() << std::endl;
}

int Plata::getNumarTotalPlati() {
    return numarTotalPlati;
}

// PlataCard
PlataCard::PlataCard(const std::string& id, double s, 
                     const std::string& nrCard, const std::string& dataExp)
    : Plata(id, s, "Card"), numarCard(nrCard), dataExpirare(dataExp) {}

bool PlataCard::proceseazaPlata() const {
    return numarCard.length() >= 16 && suma > 0;
}

double PlataCard::calculeazaComision() const {
    return suma * 0.02;
}

std::unique_ptr<Plata> PlataCard::clone() const {
    return std::make_unique<PlataCard>(*this);
}

std::string PlataCard::getDetalii() const {
    return Plata::getDetalii() + ", Card: ****" + 
           numarCard.substr(numarCard.length() - 4);
}

// PlataTransfer
PlataTransfer::PlataTransfer(const std::string& id, double s, 
                             const std::string& iban, const std::string& banca)
    : Plata(id, s, "Transfer"), iban(iban), banca(banca) {}

bool PlataTransfer::proceseazaPlata() const {
    return iban.length() >= 10 && suma > 0;
}

double PlataTransfer::calculeazaComision() const {
    return std::max(5.0, suma * 0.005);
}

std::unique_ptr<Plata> PlataTransfer::clone() const {
    return std::make_unique<PlataTransfer>(*this);
}

std::string PlataTransfer::getDetalii() const {
    return Plata::getDetalii() + ", Banca: " + banca + 
           ", IBAN: " + iban.substr(0, 4) + "****";
}

// PlataCash
PlataCash::PlataCash(const std::string& id, double s, const std::string& locatie)
    : Plata(id, s, "Cash"), locatieIncasare(locatie) {}

bool PlataCash::proceseazaPlata() const {
    return !locatieIncasare.empty() && suma > 0;
}

double PlataCash::calculeazaComision() const {
    return 0;
}

std::unique_ptr<Plata> PlataCash::clone() const {
    return std::make_unique<PlataCash>(*this);
}

std::string PlataCash::getDetalii() const {
    return Plata::getDetalii() + ", Locatie: " + locatieIncasare;

}
