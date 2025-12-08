#include "../include/plata_crypto.hpp"
#include <sstream>
#include <iomanip>

PlataCrypto::PlataCrypto(const std::string& id, double s, 
                         const std::string& wallet, 
                         const std::string& crypto, double rate)
    : Plata(id, s, "Crypto"), 
      walletAddress(wallet), 
      cryptoType(crypto), 
      exchangeRate(rate) {}

bool PlataCrypto::proceseazaPlata() const {
    return !walletAddress.empty() && exchangeRate > 0 && suma > 0;
}

double PlataCrypto::calculeazaComision() const {
    return suma * 0.01;
}

double PlataCrypto::calculeazaSumaInCrypto() const {
    return suma / exchangeRate;
}

std::unique_ptr<Plata> PlataCrypto::clone() const {
    return std::make_unique<PlataCrypto>(*this);
}

std::string PlataCrypto::getDetalii() const {
    std::ostringstream oss;
    oss << Plata::getDetalii()
        << ", Criptomoneda: " << cryptoType
        << ", Suma in " << cryptoType << ": "
        << std::fixed << std::setprecision(8) << calculeazaSumaInCrypto()
        << ", Wallet: " << walletAddress.substr(0, 8) << "...";
    return oss.str();
}

std::string PlataCrypto::genereazaQRCode() const {
    std::ostringstream oss;
    oss << "https://api.qrserver.com/v1/create-qr-code/?size=150x150&data="
        << "crypto:" << walletAddress
        << "?amount=" << std::fixed << std::setprecision(8) << calculeazaSumaInCrypto()
        << "&currency=" << cryptoType;
    return oss.str();
}