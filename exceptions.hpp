#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

class EroareMagazin : public std::exception {
protected:
    std::string mesaj;
    
public:
    EroareMagazin(const std::string& msg);
    virtual const char* what() const noexcept override;
    virtual ~EroareMagazin() = default;
};

class EroareProdus : public EroareMagazin {
public:
    EroareProdus(const std::string& msg);
};

class EroareStoc : public EroareProdus {
public:
    EroareStoc(const std::string& produs, int cantitate);
};

class EroareClient : public EroareMagazin {
public:
    EroareClient(const std::string& msg);
};

class EroarePlata : public EroareMagazin {
public:
    EroarePlata(const std::string& msg);
};

#endif