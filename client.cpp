#include "../include/client.hpp"

Client::Client(const std::string& id, const std::string& n,
               const std::string& e, const std::string& t,
               const Adresa& a)
    : idClient(id), nume(n), email(e), telefon(t), adresaLivrare(a) {
    verificareEmail();
}

void Client::verificareEmail() {
    if (email.find('@') == std::string::npos)
        email = "invalid@email.com";
}

std::string Client::getNume() const { return nume; }
std::string Client::getIdClient() const { return idClient; }

std::ostream& operator<<(std::ostream& os, const Client& c) {
    os << "Client: " << c.nume << " [" << c.idClient << "]\n"
       << "Email: " << c.email << "\n"
       << "Telefon: " << c.telefon << "\n"
       << c.adresaLivrare;
    return os;
}