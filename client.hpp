#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include "adresa.hpp"

class Client {
private:
    std::string idClient, nume, email, telefon;
    Adresa adresaLivrare;
    void verificareEmail();
    
public:
    Client(const std::string& id = "", 
           const std::string& n = "", 
           const std::string& e = "", 
           const std::string& t = "", 
           const Adresa& a = Adresa());
    
    std::string getNume() const;
    std::string getIdClient() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Client& c);
};

#endif