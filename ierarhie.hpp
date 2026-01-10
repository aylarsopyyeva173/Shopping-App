#ifndef IERARHIE_HPP
#define IERARHIE_HPP

#include <string>
#include <memory>

class Plata {
protected:
    std::string idPlata;
    double suma;
    std::string metoda;
    
public:
    Plata(const std::string& id, double s, const std::string& m);
    virtual ~Plata() = default;
    
    virtual bool proceseazaPlata() const = 0;
    virtual double calculeazaComision() const = 0;
    virtual std::unique_ptr<Plata> clone() const = 0;
    virtual std::string getDetalii() const;
    
    void afiseazaDetalii() const;
    
    static int numarTotalPlati;
    static int getNumarTotalPlati();
};

class PlataCard : public Plata {
private:
    std::string numarCard;
    std::string dataExpirare;
    
public:
    PlataCard(const std::string& id, double s, 
              const std::string& nrCard, const std::string& dataExp);
    
    bool proceseazaPlata() const override;
    double calculeazaComision() const override;
    std::unique_ptr<Plata> clone() const override;
    std::string getDetalii() const override;
};

class PlataTransfer : public Plata {
private:
    std::string iban;
    std::string banca;
    
public:
    PlataTransfer(const std::string& id, double s, 
                  const std::string& iban, const std::string& banca);
    
    bool proceseazaPlata() const override;
    double calculeazaComision() const override;
    std::unique_ptr<Plata> clone() const override;
    std::string getDetalii() const override;
};

class PlataCash : public Plata {
private:
    std::string locatieIncasare;
    
public:
    PlataCash(const std::string& id, double s, const std::string& locatie);
    
    bool proceseazaPlata() const override;
    double calculeazaComision() const override;
    std::unique_ptr<Plata> clone() const override;
    std::string getDetalii() const override;
};


#endif
