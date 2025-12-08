#include "produs.hpp"
#include "client.hpp"
#include "comanda.hpp"
#include "ierarhie.hpp"
#include "plata_crypto.hpp"
#include "exceptions.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <limits>

using namespace std;

// Yardımcı fonksiyonlar
void afisareMeniu() {
    cout << "\n=== SISTEM MAGAZIN ONLINE ===\n"
         << "1. Adauga client\n"
         << "2. Afiseaza clienti\n"
         << "3. Creeaza comanda\n"
         << "4. Afiseaza comenzi\n"
         << "5. Demo polimorfism plati\n"
         << "6. Statistici\n"
         << "7. Iesire\n"
         << "Alegere: ";
}

Adresa citesteAdresa() {
    string strada, oras, codPostal;
    int numar;

    cout << "--- Introduceti adresa ---\n";
    cout << "Strada: ";
    getline(cin, strada);
    cout << "Oras: ";
    getline(cin, oras);
    cout << "Cod postal: ";
    getline(cin, codPostal);
    cout << "Numar apartament: ";
    cin >> numar;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return Adresa(strada, oras, codPostal, numar);
}

Client citesteClient() {
    string nume, email, telefon;

    cout << "--- Introduceti date client ---\n";
    cout << "Nume: ";
    getline(cin, nume);
    cout << "Email: ";
    getline(cin, email);
    cout << "Telefon: ";
    getline(cin, telefon);

    Adresa a = citesteAdresa();
    string id = "C" + to_string(time(nullptr) % 1000);

    return Client(id, nume, email, telefon, a);
}

void demoPolimorfismPlati() {
    cout << "\n=== DEMO POLIMORFISM PLATI ===\n";

    vector<unique_ptr<Plata>> plati;

    // Farklı ödeme türleri oluştur
    plati.push_back(make_unique<PlataCard>("CARD001", 150.0,
                                           "4111111111111111", "12/25"));
    plati.push_back(make_unique<PlataTransfer>("TRF001", 300.0,
                                               "RO49AAAA1B31007593840000",
                                               "BCR"));
    plati.push_back(make_unique<PlataCash>("CASH001", 50.0,
                                           "Magazin Central"));
    plati.push_back(make_unique<PlataCrypto>("CRYPTO001", 200.0,
                                            "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa",
                                            "BTC", 50000.0));

    // Polimorfik çağrılar
    for (const auto& plata : plati) {
        cout << "\n";
        plata->afiseazaDetalii();
        cout << "Comision: $" << plata->calculeazaComision() << endl;

        // Dynamic cast ile özel işlemler
        if (auto* crypto = dynamic_cast<PlataCrypto*>(plata.get())) {
            cout << "Suma in BTC: " << crypto->calculeazaSumaInCrypto() << endl;
            cout << "QR Code: " << crypto->genereazaQRCode() << endl;
        }

        // Ödeme işlemini dene
        try {
            if (plata->proceseazaPlata()) {
                cout << "Status: SUCCES\n";
            } else {
                cout << "Status: ESEC\n";
            }
        } catch (const exception& e) {
            cout << "Eroare: " << e.what() << endl;
        }
    }
}

int main() {
    vector<Client> clienti;
    vector<Produs> produse;
    vector<unique_ptr<Comanda>> comenzi;

    // Başlangıç ürünleri
    produse.push_back(Produs("P001", "Camasa clasica", "Camasi", 129.99, 10, "M"));
    produse.push_back(Produs("P002", "Blugi", "Pantaloni", 199.99, 5, "L"));
    produse.push_back(Produs("P003", "Geaca piele", "Jachete", 449.99, 3, "XL"));
    produse.push_back(Produs("P004", "Pulover tricotat", "Pulovere", 179.99, 8, "M"));

    int alegere;

    try {
        do {
            afisareMeniu();
            cin >> alegere;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (alegere) {
                case 1: { // Adauga client
                    Client c = citesteClient();
                    clienti.push_back(c);
                    cout << "\nClient adaugat cu succes!\n";
                    cout << c << endl;
                    break;
                }

                case 2: { // Afiseaza clienti
                    if (clienti.empty()) {
                        cout << "Nu exista clienti inregistrati.\n";
                    } else {
                        cout << "\n=== LISTA CLIENTI ===\n";
                        for (size_t i = 0; i < clienti.size(); i++) {
                            cout << i + 1 << ". " << clienti[i].getNume()
                                 << " [" << clienti[i].getIdClient() << "]\n";
                        }
                    }
                    break;
                }

                case 3: { // Creeaza comanda
                    if (clienti.empty()) {
                        cout << "Nu exista clienti. Adaugati mai intai un client.\n";
                        break;
                    }

                    cout << "\nSelectati clientul:\n";
                    for (size_t i = 0; i < clienti.size(); i++) {
                        cout << i + 1 << ". " << clienti[i].getNume() << "\n";
                    }

                    int selClient;
                    cout << "Alegere: ";
                    cin >> selClient;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (selClient < 1 || selClient > clienti.size()) {
                        cout << "Selectie invalida.\n";
                        break;
                    }

                    auto comanda = make_unique<Comanda>(clienti[selClient - 1]);
                    char continua = 'd';

                    while (continua == 'd' || continua == 'D') {
                        cout << "\nProduse disponibile:\n";
                        for (size_t i = 0; i < produse.size(); i++) {
                            cout << i + 1 << ". " << produse[i] << "\n";
                        }

                        int produsId, cantitate;
                        cout << "Selectati produsul (numar): ";
                        cin >> produsId;
                        cout << "Cantitate: ";
                        cin >> cantitate;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        if (produsId >= 1 && produsId <= produse.size()) {
                            try {
                                comanda->adaugaProdus(produse[produsId - 1], cantitate);
                                cout << "Produs adaugat cu succes!\n";
                            } catch (const EroareStoc& e) {
                                cout << "Eroare: " << e.what() << endl;
                            }
                        } else {
                            cout << "Produs inexistent.\n";
                        }

                        cout << "Adaugati alt produs? (d/n): ";
                        cin >> continua;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    // Selectare metoda de plata
                    cout << "\nSelectati metoda de plata:\n"
                         << "1. Card\n"
                         << "2. Transfer bancar\n"
                         << "3. Cash\n"
                         << "4. Crypto\n"
                         << "Alegere: ";

                    int metodaPlata;
                    cin >> metodaPlata;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    double total = comanda->calculTotal();

                    switch (metodaPlata) {
                        case 1: {
                            string cardNr, expDate;
                            cout << "Numar card (16 cifre): ";
                            getline(cin, cardNr);
                            cout << "Data expirare (MM/AA): ";
                            getline(cin, expDate);

                            comanda->setPlata(make_unique<PlataCard>(
                                "PLT" + to_string(time(nullptr) % 1000),
                                total, cardNr, expDate
                            ));
                            break;
                        }
                        case 2: {
                            string iban, banca;
                            cout << "IBAN: ";
                            getline(cin, iban);
                            cout << "Nume banca: ";
                            getline(cin, banca);

                            comanda->setPlata(make_unique<PlataTransfer>(
                                "PLT" + to_string(time(nullptr) % 1000),
                                total, iban, banca
                            ));
                            break;
                        }
                        case 3: {
                            string locatie;
                            cout << "Locatie incasare: ";
                            getline(cin, locatie);

                            comanda->setPlata(make_unique<PlataCash>(
                                "PLT" + to_string(time(nullptr) % 1000),
                                total, locatie
                            ));
                            break;
                        }
                        case 4: {
                            string wallet, crypto;
                            double rate;
                            cout << "Wallet address: ";
                            getline(cin, wallet);
                            cout << "Tip crypto (BTC/ETH/etc): ";
                            getline(cin, crypto);
                            cout << "Exchange rate (1 " << crypto << " = ? USD): ";
                            cin >> rate;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            comanda->setPlata(make_unique<PlataCrypto>(
                                "PLT" + to_string(time(nullptr) % 1000),
                                total, wallet, crypto, rate
                            ));
                            break;
                        }
                        default:
                            cout << "Metoda invalida. Plata setata pe cash.\n";
                            comanda->setPlata(make_unique<PlataCash>(
                                "PLT" + to_string(time(nullptr) % 1000),
                                total, "Magazin"
                            ));
                    }

                    try {
                        comanda->finalizeazaComanda();
                        comenzi.push_back(move(comanda));
                        cout << "Comanda creata cu succes!\n";
                    } catch (const exception& e) {
                        cout << "Eroare la finalizare comanda: " << e.what() << endl;
                    }

                    break;
                }

                case 4: { // Afiseaza comenzi
                    if (comenzi.empty()) {
                        cout << "Nu exista comenzi.\n";
                    } else {
                        cout << "\n=== LISTA COMENZI ===\n";
                        for (const auto& comanda : comenzi) {
                            comanda->afisareRezumat();
                        }
                    }
                    break;
                }

                case 5: { // Demo polimorfism
                    demoPolimorfismPlati();
                    break;
                }

                case 6: { // Statistici
                    cout << "\n=== STATISTICI ===\n"
                         << "Numar total plati: " << Plata::getNumarTotalPlati() << "\n"
                         << "Numar comenzi: " << Comanda::getNumarComenzi() << "\n"
                         << "Numar clienti: " << clienti.size() << "\n"
                         << "Numar produse: " << produse.size() << endl;
                    break;
                }

                case 7: { // Iesire
                    cout << "La revedere!\n";
                    break;
                }

                default:
                    cout << "Optiune invalida. Incercati din nou.\n";
            }

        } while (alegere != 7);

    } catch (const exception& e) {
        cerr << "Eroare neprevazuta: " << e.what() << endl;
        return 1;
    }

    return 0;
}
