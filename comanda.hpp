#ifndef COMANDA_HPP
#define COMANDA_HPP

#include <string>
#include <vector>
#include <memory>
#include "produs.hpp"
#include "client.hpp"
#include "ierarhie.hpp"

class Comanda {
private:
    std::string idComanda;
    std::string status;
    Client client;
    std::vector<Produs> produse;
    std::vector<int> cantitati;
    std::unique_ptr<Plata> plata;
    
    void generareIdComanda();
    double calculTotal() const;
    
public:
    Comanda(const Client& c, const std::string& s = "In pregatire");
    Comanda(const Comanda& other);
    Comanda& operator=(Comanda other);
    ~Comanda() = default;
    
    bool adaugaProdus(const Produs& p, int cant);
    void setPlata(std::unique_ptr<Plata> p);
    void proceseazaPlata() const;
    void afisareRezumat() const;
    void finalizeazaComanda();
    
    static int numarComenzi;
    static int getNumarComenzi();
    
    friend void swap(Comanda& first, Comanda& second);
};

#endif