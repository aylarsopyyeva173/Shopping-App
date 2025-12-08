#include "../include/comanda.hpp"
#include "../include/exceptions.hpp"
#include <iostream>
#include <ctime>
#include <utility>

int Comanda::numarComenzi = 0;

Comanda::Comanda(const Client& c, const std::string& s)
    : client(c), status(s) {
    generareIdComanda();
    numarComenzi++;
}

Comanda::Comanda(const Comanda& other)
    : idComanda(other.idComanda),
      status(other.status),
      client(other.client),
      produse(other.produse),
      cantitati(other.cantitati) {
    if (other.plata) {
        plata = other.plata->clone();
    }
}

Comanda& Comanda::operator=(Comanda other) {
    swap(*this, other);
    return *this;
}

void swap(Comanda& first, Comanda& second) {
    using std::swap;
    swap(first.idComanda, second.idComanda);
    swap(first.status, second.status);
    swap(first.client, second.client);
    swap(first.produse, second.produse);
    swap(first.cantitati, second.cantitati);
    swap(first.plata, second.plata);
}

void Comanda::generareIdComanda() {
    idComanda = "CMD" + std::to_string(time(nullptr) % 10000 + numarComenzi);
}

double Comanda::calculTotal() const {
    double total = 0;
    for (size_t i = 0; i < produse.size(); i++) {
        total += produse[i].getPret() * cantitati[i];
    }
    return total;
}

bool Comanda::adaugaProdus(const Produs& p, int cant) {
    if (cant <= 0) {
        throw EroareProdus("Cantitate invalida: " + std::to_string(cant));
    }
    if (!p.inStoc(cant)) {
        throw EroareStoc(p.getNume(), cant);
    }
    
    produse.push_back(p);
    cantitati.push_back(cant);
    return true;
}

void Comanda::setPlata(std::unique_ptr<Plata> p) {
    plata = std::move(p);
}

void Comanda::proceseazaPlata() const {
    if (!plata) {
        throw EroarePlata("Nu exista plata setata pentru comanda");
    }
    
    std::cout << "Procesare plata...\n";
    plata->afiseazaDetalii();
    
    if (plata->proceseazaPlata()) {
        std::cout << "Comision: $" << plata->calculeazaComision() << std::endl;
        std::cout << "Plata efectuata cu succes!\n";
    } else {
        throw EroarePlata("Plata nu a putut fi procesata");
    }
}

void Comanda::afisareRezumat() const {
    std::cout << "\n=== REZUMAT COMANDA ===\n"
              << "ID: " << idComanda << "\n"
              << "Client: " << client.getNume() << "\n"
              << "Status: " << status << "\n"
              << "Total: $" << calculTotal() << "\n"
              << "Produse:\n";
    
    for (size_t i = 0; i < produse.size(); i++) {
        std::cout << "  - " << produse[i].getNume() 
                  << " (" << produse[i].getMarime() << ") "
                  << "x" << cantitati[i] 
                  << " - $" << (produse[i].getPret() * cantitati[i]) << "\n";
    }
    std::cout << "=======================\n";
}

void Comanda::finalizeazaComanda() {
    if (produse.empty()) {
        throw EroareMagazin("Comanda nu contine produse");
    }
    
    if (!plata) {
        throw EroarePlata("Metoda de plata nu a fost selectata");
    }
    
    try {
        proceseazaPlata();
        status = "Finalizata";
        std::cout << "Comanda finalizata cu succes!\n";
    } catch (const EroarePlata& e) {
        status = "Plata esuata";
        throw;
    }
}

int Comanda::getNumarComenzi() {
    return numarComenzi;
}