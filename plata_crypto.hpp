#ifndef PLATA_CRYPTO_HPP
#define PLATA_CRYPTO_HPP

#include "ierarhie.hpp"
#include <string>

class PlataCrypto : public Plata {
private:
    std::string walletAddress;
    std::string cryptoType;
    double exchangeRate;
    
public:
    PlataCrypto(const std::string& id, double s, 
                const std::string& wallet, const std::string& crypto, double rate);
    
    bool proceseazaPlata() const override;
    double calculeazaComision() const override;
    double calculeazaSumaInCrypto() const;
    std::unique_ptr<Plata> clone() const override;
    std::string getDetalii() const override;
    
    std::string genereazaQRCode() const;
};

#endif