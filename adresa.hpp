#ifndef ADRESA_HPP
#define ADRESA_HPP

#include <string>
#include <iostream>

class Adresa {
private:
    std::string strada, oras, codPostal;
    int numarApartament;
    void curatareDate();
    
public:
    Adresa(const std::string& str = "", 
           const std::string& ors = "", 
           const std::string& cp = "", 
           int nrAp = 0);
    
    std::string adresaCompleta() const;
    friend std::ostream& operator<<(std::ostream& os, const Adresa& adresa);
};

#endif