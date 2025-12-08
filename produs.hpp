#ifndef PRODUS_HPP
#define PRODUS_HPP

#include <string>

class Produs {
private:
    std::string codBare, nume, categorie, marime;
    double pret;
    int stoc;
    
public:
    Produs(const std::string& cod = "", 
           const std::string& n = "", 
           const std::string& cat = "", 
           double pr = 0, 
           int s = 0, 
           const std::string& m = "");
    
    std::string getCodBare() const;
    std::string getNume() const;
    std::string getMarime() const;
    double getPret() const;
    int getStoc() const;
    bool inStoc(int cant = 1) const;
    
    friend std::ostream& operator<<(std::ostream& os, const Produs& p);
};

#endif