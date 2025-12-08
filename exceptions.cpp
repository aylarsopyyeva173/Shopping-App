#include "../include/exceptions.hpp"

EroareMagazin::EroareMagazin(const std::string& msg) : mesaj(msg) {}

const char* EroareMagazin::what() const noexcept {
    return mesaj.c_str();
}

EroareProdus::EroareProdus(const std::string& msg) 
    : EroareMagazin("[Eroare Produs] " + msg) {}

EroareStoc::EroareStoc(const std::string& produs, int cantitate)
    : EroareProdus("Stoc insuficient pentru '" + produs + 
                  "'. Cerut: " + std::to_string(cantitate)) {}

EroareClient::EroareClient(const std::string& msg)
    : EroareMagazin("[Eroare Client] " + msg) {}

EroarePlata::EroarePlata(const std::string& msg)
    : EroareMagazin("[Eroare Plata] " + msg) {}