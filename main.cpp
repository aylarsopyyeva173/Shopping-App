#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>

class Client {
private:
    std::string nume;
    std::string prenume;
    std::string adresa;
    std::string telefon;
    std::string email;

public:
    Client(const std::string& nume, const std::string& prenume, const std::string& adresa,
             const std::string& telefon, const std::string& email)
        : nume(nume), prenume(prenume), adresa(adresa), telefon(telefon), email(email) {}

    std::string getNume() const { return nume; }
    std::string getPrenume() const { return prenume; }
    std::string getAdresa() const { return adresa; }
    std::string getTelefon() const { return telefon; }
    std::string getEmail() const { return email; }

    void afiseazaInformatii() const {
        std::cout << "\n=== INFORMATII CLIENT ===\n";
        std::cout << "Nume Prenume: " << nume << " " << prenume << std::endl;
        std::cout << "Telefon: " << telefon << std::endl;
        std::cout << "E-mail: " << email << std::endl;
        std::cout << "Adresa: " << adresa << std::endl;
    }
};

class Produs {
private:
    int id;
    std::string nume;
    double pret;
    int stoc;
    std::string categorie;

public:
    Produs(int id, const std::string& nume, double pret, int stoc, const std::string& categorie)
        : id(id), nume(nume), pret(pret), stoc(stoc), categorie(categorie) {}

    int getId() const { return id; }
    std::string getNume() const { return nume; }
    double getPret() const { return pret; }
    int getStoc() const { return stoc; }
    std::string getCategorie() const { return categorie; }

    void setPret(double pretNou) { pret = pretNou; }
    void setStoc(int stocNou) { stoc = stocNou; }

    void scadeStoc(int cantitate) {
        stoc -= cantitate;
        if (stoc < 0) stoc = 0;
    }

    void afiseaza() const {
        std::cout << std::setw(3) << id << " | "
                  << std::setw(20) << std::left << nume << " | "
                  << std::setw(8) << std::right << std::fixed << std::setprecision(2) << pret << " RON | "
                  << std::setw(4) << stoc << " | "
                  << std::setw(15) << std::left << categorie << std::endl;
    }
};

class ItemCos {
private:
    Produs produs;
    int cantitate;

public:
    ItemCos(const Produs& produs, int cantitate) : produs(produs), cantitate(cantitate) {}

    Produs getProdus() const { return produs; }
    int getCantitate() const { return cantitate; }
    double getPretTotal() const { return produs.getPret() * cantitate; }

    void afiseaza() const {
        std::cout << "• " << produs.getNume() << " x " << cantitate << " = "
                  << std::fixed << std::setprecision(2) << getPretTotal() << " RON\n";
    }
};

class CosCumparaturi {
private:
    std::vector<ItemCos> iteme;
    Client client;

public:
    CosCumparaturi(const Client& client) : client(client) {}

    void adaugaProdus(const Produs& produs, int cantitate) {
        if (produs.getStoc() < cantitate) {
            std::cout << "❌ Stoc insuficient! Disponibil: " << produs.getStoc() << std::endl;
            return;
        }

        // Verifică dacă produsul există deja în coș
        for (auto& item : iteme) {
            if (item.getProdus().getId() == produs.getId()) {
                std::cout << " Acest produs este deja in cos! Cantitatea este actualizata.\n";
                return;
            }
        }

        iteme.push_back(ItemCos(produs, cantitate));
        std::cout << "✅ " << cantitate << " bucati " << produs.getNume() << " au fost adaugate in cos.\n";
    }

    void afiseazaCos() const {
        if (iteme.empty()) {
            std::cout << "🛒 Cosul dvs. este gol.\n";
            return;
        }

        double total = 0.0;
        std::cout << "\n=== COSUL DVS. ===\n";
        for (const auto& item : iteme) {
            item.afiseaza();
            total += item.getPretTotal();
        }
        std::cout << "────────────────────────────\n";
        std::cout << "Total: " << std::fixed << std::setprecision(2) << total << " RON\n";
    }

    double getTotal() const {
        double total = 0.0;
        for (const auto& item : iteme) {
            total += item.getPretTotal();
        }
        return total;
    }

    void golesteCos() {
        iteme.clear();
        std::cout << "  Cosul a fost golit.\n";
    }

    bool esteGol() const {
        return iteme.empty();
    }

    const std::vector<ItemCos>& getIteme() const {
        return iteme;
    }

    Client getClient() const {
        return client;
    }
};

class ManagerProduse {
private:
    std::vector<Produs> produse;

public:
    ManagerProduse() {
        incarcaProduseExemplu();
    }

    void incarcaProduseExemplu() {
        produse.push_back(Produs(1, "Laptop Gaming", 8999.99, 10, "Electronice"));
        produse.push_back(Produs(2, "Mouse Wireless", 199.50, 25, "Accesorii"));
        produse.push_back(Produs(3, "Tastatura Mecanica", 450.00, 15, "Accesorii"));
        produse.push_back(Produs(4, "Monitor 24 inch", 1999.99, 8, "Electronice"));
        produse.push_back(Produs(5, "Căști Bluetooth", 299.99, 20, "Audio"));
        produse.push_back(Produs(6, "Tableta", 2499.99, 12, "Electronice"));
        produse.push_back(Produs(7, "Powerbank", 399.50, 30, "Accesorii"));
    }

    void afiseazaToateProdusele() {
        if (produse.empty()) {
            std::cout << "Inca nu exista produse in sistem.\n";
            return;
        }

        std::cout << "\n=== TOATE PRODUSELE ===\n";
        std::cout << "ID | Nume Produs           | Pret     | Stoc | Categorie" << std::endl;
        std::cout << "-------------------------------------------------------" << std::endl;

        for (const auto& produs : produse) {
            produs.afiseaza();
        }
    }

    void adaugaProdus() {
        int id, stoc;
        double pret;
        std::string nume, categorie;

        std::cout << "ID Produs: ";
        std::cin >> id;

        for (const auto& produs : produse) {
            if (produs.getId() == id) {
                std::cout << " Eroare: Acest ID exista deja!\n";
                return;
            }
        }

        std::cin.ignore();
        std::cout << "Nume Produs: ";
        std::getline(std::cin, nume);

        std::cout << "Pret: ";
        std::cin >> pret;

        std::cout << "Stoc: ";
        std::cin >> stoc;

        std::cin.ignore();
        std::cout << "Categorie: ";
        std::getline(std::cin, categorie);

        produse.push_back(Produs(id, nume, pret, stoc, categorie));
        std::cout << "Produs adaugat cu succes!\n";
    }

    void actualizeazaStoc() {
        int id, cantitate;
        std::cout << "ID Produs: ";
        std::cin >> id;

        std::cout << "Modificare stoc (+ sau -): ";
        std::cin >> cantitate;

        for (auto& produs : produse) {
            if (produs.getId() == id) {
                int stocNou = produs.getStoc() + cantitate;
                if (stocNou < 0) {
                    std::cout << "Eroare: Stocul nu poate fi negativ!\n";
                    return;
                }
                produs.setStoc(stocNou);
                std::cout << " Stoc actualizat. Stoc nou: " << stocNou << std::endl;
                return;
            }
        }

        std::cout << " Produsul nu a fost gasit.\n";
    }

    void stergeProdus() {
        int id;
        std::cout << "ID-ul produsului de sters: ";
        std::cin >> id;

        for (auto it = produse.begin(); it != produse.end(); ++it) {
            if (it->getId() == id) {
                std::cout << " Produs șters: " << it->getNume() << std::endl;
                produse.erase(it);
                return;
            }
        }

        std::cout << "❌ Produsul nu a fost gasit.\n";
    }

    void afiseazaProdusePentruClient() {
        std::cout << "\n  PRODUSE DISPONIBILE\n";
        std::cout << "ID | Nume Produs           | Pret     | Stoc | Categorie" << std::endl;
        std::cout << "-------------------------------------------------------" << std::endl;

        bool produseDisponibile = false;
        for (const auto& produs : produse) {
            if (produs.getStoc() > 0) {
                produs.afiseaza();
                produseDisponibile = true;
            }
        }

        if (!produseDisponibile) {
            std::cout << "  Momentan nu exista produse disponibile.\n";
        }
    }

    Produs* gasesteProdus(int id) {
        for (auto& produs : produse) {
            if (produs.getId() == id) {
                return &produs;
            }
        }
        return nullptr;
    }

    Client citesteDateClient() {
        std::string nume, prenume, adresa, telefon, email;

        std::cin.ignore();
        std::cout << "\n=== DATE CLIENT ===\n";
        std::cout << "Nume: ";
        std::getline(std::cin, nume);

        std::cout << "Prenume: ";
        std::getline(std::cin, prenume);

        std::cout << "Telefon: ";
        std::getline(std::cin, telefon);

        std::cout << "E-mail: ";
        std::getline(std::cin, email);

        std::cout << "Adresa: ";
        std::getline(std::cin, adresa);

        return Client(nume, prenume, adresa, telefon, email);
    }

    void proceseazaComanda(CosCumparaturi& cos) {
        if (cos.esteGol()) {
            std::cout << " Cosul dvs. este gol!\n";
            return;
        }

        std::cout << "\n REZUMAT COMANDA\n";
        cos.afiseazaCos();
        cos.getClient().afiseazaInformatii();

        std::cout << "\nConfirmati comanda? (d/n): ";
        char confirmare;
        std::cin >> confirmare;

        if (confirmare == 'd' || confirmare == 'D') {
            // Actualizează stocurile
            for (const auto& item : cos.getIteme()) {
                Produs* produs = gasesteProdus(item.getProdus().getId());
                if (produs) {
                    produs->scadeStoc(item.getCantitate());
                }
            }

            // Salvează comanda în fișier
            salveazaComandaInFisier(cos);

            std::cout << "\n Comanda dvs. a fost plasata cu succes! Va multumim.\n";
            std::cout << " Comanda dvs. va fi procesata în cel mai scurt timp.\n";
            cos.golesteCos();
        } else {
            std::cout << " Comanda a fost anulata.\n";
        }
    }

    void salveazaComandaInFisier(const CosCumparaturi& cos) {
        std::ofstream fisier("comenzi.txt", std::ios::app);
        if (fisier.is_open()) {
            time_t acum = time(0);
            char* dataOra = ctime(&acum);

            fisier << "\n=== COMANDA NOUĂ ===\n";
            fisier << "Data comenzii: " << dataOra;
            fisier << "Client: " << cos.getClient().getNume() << " " << cos.getClient().getPrenume() << std::endl;
            fisier << "Telefon: " << cos.getClient().getTelefon() << std::endl;
            fisier << "E-mail: " << cos.getClient().getEmail() << std::endl;
            fisier << "Adresa: " << cos.getClient().getAdresa() << std::endl;
            fisier << "Produse:\n";

            for (const auto& item : cos.getIteme()) {
                fisier << "- " << item.getProdus().getNume() << " x " << item.getCantitate()
                     << " = " << std::fixed << std::setprecision(2) << item.getPretTotal() << " RON\n";
            }

            fisier << "Total de plată: " << std::fixed << std::setprecision(2) << cos.getTotal() << " RON\n";
            fisier << "================================\n";
            fisier.close();

            std::cout << " Detaliile comenzii au fost salvate în 'comenzi.txt'.\n";
        }
    }
};

class Aplicatie {
private:
    ManagerProduse manager;
    CosCumparaturi* cosCurent;

public:
    Aplicatie() : cosCurent(nullptr) {}

    ~Aplicatie() {
        if (cosCurent != nullptr) {
            delete cosCurent;
        }
    }

    void afiseazaMeniuVanzator() {
        std::cout << "\n=== PANEL VANZATOR ===\n";
        std::cout << "1. Afișeaza toate produsele\n";
        std::cout << "2. Adauga produs nou\n";
        std::cout << "3. Actualizeaza stoc\n";
        std::cout << "4. Sterge produs\n";
        std::cout << "5. Mergi la panel client\n";
        std::cout << "0. Iesire\n";
        std::cout << "Alegeti optiunea: ";
    }

    void afiseazaMeniuClient() {
        std::cout << "\n=== PANEL CLIENT ===\n";
        std::cout << "1. Listeaza produse\n";
        std::cout << "2. Adauga in cos\n";
        std::cout << "3. Afișeaza cos\n";
        std::cout << "4. Finalizeaza comanda\n";
        std::cout << "5. Goleste cos\n";
        std::cout << "6. Mergi la panel vanzator\n";
        std::cout << "0. Iesire\n";
        std::cout << "Alegeti optiunea: ";
    }

    void ruleazaPanelVanzator() {
        int optiune;
        do {
            afiseazaMeniuVanzator();
            std::cin >> optiune;

            switch (optiune) {
                case 1:
                    manager.afiseazaToateProdusele();
                    break;
                case 2:
                    manager.adaugaProdus();
                    break;
                case 3:
                    manager.actualizeazaStoc();
                    break;
                case 4:
                    manager.stergeProdus();
                    break;
                case 5:
                    return;
                case 0:
                    std::cout << "Aplicația se închide...\n";
                    exit(0);
                default:
                    std::cout << " Opțiune invalida!\n";
            }
        } while (true);
    }

    void ruleazaPanelClient() {
        // Autentificare client
        if (cosCurent == nullptr) {
            std::cout << "\n Introduceti datele dvs.:\n";
            Client client = manager.citesteDateClient();
            cosCurent = new CosCumparaturi(client);
        }

        int optiune;
        do {
            afiseazaMeniuClient();
            std::cin >> optiune;

            switch (optiune) {
                case 1:
                    manager.afiseazaProdusePentruClient();
                    break;
                case 2:
                    {
                        int idProdus, cantitate;
                        std::cout << "ID Produs: ";
                        std::cin >> idProdus;
                        std::cout << "Cantitate: ";
                        std::cin >> cantitate;

                        Produs* produs = manager.gasesteProdus(idProdus);
                        if (produs) {
                            cosCurent->adaugaProdus(*produs, cantitate);
                        } else {
                            std::cout << "Produsul nu a fost găsit!\n";
                        }
                    }
                    break;
                case 3:
                    cosCurent->afiseazaCos();
                    break;
                case 4:
                    manager.proceseazaComanda(*cosCurent);
                    break;
                case 5:
                    cosCurent->golesteCos();
                    break;
                case 6:
                    return;
                case 0:
                    std::cout << "Aplicatia se inchide...\n";
                    exit(0);
                default:
                    std::cout << " Optiune invalida!\n";
            }
        } while (true);
    }

    void ruleaza() {
        int optiunePrincipala;

        std::cout << " BINE ATI VENIT IN SISTEMUL DE MANAGEMENT\n";

        do {
            std::cout << "\n=== MENIU PRINCIPAL ===\n";
            std::cout << "1. Panel Vanzator\n";
            std::cout << "2. Panel Client\n";
            std::cout << "0. Iesire\n";
            std::cout << "Alegeti opiunea: ";
            std::cin >> optiunePrincipala;

            switch (optiunePrincipala) {
                case 1:
                    ruleazaPanelVanzator();
                    break;
                case 2:
                    ruleazaPanelClient();
                    break;
                case 0:
                    std::cout << " La revedere!\n";
                    break;
                default:
                    std::cout << " Optiune invalida!\n";
            }
        } while (optiunePrincipala != 0);
    }
};

int main() {
    Aplicatie app;
    app.ruleaza();
    return 0;
}
