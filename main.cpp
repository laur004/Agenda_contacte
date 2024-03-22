#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
//#include <fstream>

class Contact {
private:
    std::string nume;
    std::string prenume;
    std::string numar_telefon;

public:
    ~Contact();
    Contact() : nume("contact"), prenume("anonim"), numar_telefon("fara numar") {}
    Contact(std::string nume, std::string prenume, std::string numar_telefon) : nume(std::move(nume)), prenume(std::move(prenume)), numar_telefon(std::move(numar_telefon)) {}

    Contact& operator=(const Contact& other) {
        if (this != &other) {
            nume = other.nume;
            prenume = other.prenume;
            numar_telefon = other.numar_telefon;
        }
        return *this;
    }
    void afisare_contact() const {
        std::cout << nume << ' ' << prenume << ' ' << numar_telefon << '\n';
    }

    friend std::ostream& operator<<(std::ostream& out, const Contact& contact) {
        out << contact.nume << ' ' << contact.prenume << ' ' << contact.numar_telefon;
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Contact& contact) {
        std::cout << "Nume: ";
        in >> contact.nume;
        std::cout << "Prenume: ";
        in >> contact.prenume;
        std::cout << "Numar de telefon: ";
        in >> contact.numar_telefon;
        return in;
    }

    [[nodiscard]] const std::string& get_nume() const {
        return nume;
    }

    [[nodiscard]] const std::string& get_prenume() const {
        return prenume;
    }

    [[nodiscard]] const std::string& get_numar_telefon() const {
        return numar_telefon;
    }

    friend bool NumarValid(const Contact& contact);
    friend bool operator==(const Contact& contact1, const Contact& contact2);
};

Contact::~Contact()=default;

bool NumarValid(const Contact& contact) {
    const std::string& nr_telefon = contact.numar_telefon;

    if (nr_telefon.length() != 10) {
        return false;
    }

    for (size_t i = 0; i < nr_telefon.length(); ++i) {
        if (nr_telefon[i] < '0' || nr_telefon[i] > '9') {
            return false;
        }
    }
    return true;
}


bool operator==(const Contact& contact1, const Contact& contact2) {
    return contact1.nume == contact2.nume && contact1.prenume == contact2.prenume &&
           contact1.numar_telefon == contact2.numar_telefon;
}


class Lista_Contacte {
private:
    std::vector<Contact> lista_contacte;

public:
    void afisare_lista() const {
        if (lista_contacte.empty()) {
            std::cout << "Lista de contacte este goala!\n";
            return;
        }
        std::cout << "\n\nAcestea sunt contactele dumneavoastra:\n";
        for (size_t i = 0; i < lista_contacte.size(); ++i) {
            std::cout << i + 1 << '.';
            lista_contacte[i].afisare_contact();
        }
    }

    void adaugare_contact() {
        Contact contact_nou;
        std::cin >> contact_nou;
        if(NumarValid(contact_nou))
        {bool flag=false;
            for(const auto & contact : lista_contacte)
                if (contact == contact_nou) {
                    flag = true;
                    break;
                }
            if(!flag)
            {lista_contacte.push_back(contact_nou);
                std::cout << "Contact inregistrat cu succes!\n";}
            else
                std::cout<<"Exista deja un contact identic!\n";
        }
        else{
            std::cout<<"Numarul de telefon introdus este invalid!\n";}
    }

    void eliminare_contact() {
        if (lista_contacte.empty()) {
            std::cout << "Lista de contacte este deja goala!\n";
            return;
        }

        afisare_lista();
        std::cout << "\nIntroduceti indicele contactului pe care vreti sa-l eliminati: ";
        unsigned indice;
        std::cin >> indice;

        if (indice < 1 || indice > lista_contacte.size()) {
            std::cout << "Nu exista un contact cu indicele: " << indice << '\n';
            return;
        }

        lista_contacte.erase(lista_contacte.begin() + indice - 1);
        std::cout << "Contactul a fost sters cu succes!\n";
    }

    void cautare_contact_nume() const {
        std::string sir;
        bool gasit = false;
        std::cout << "\n\nCautati contact dupa nume sau prenume: ";
        std::cin >> sir;

        for (const auto& contact : lista_contacte) {
            if (contact.get_nume().find(sir) != std::string::npos || contact.get_prenume().find(sir) != std::string::npos) {
                gasit = true;
                contact.afisare_contact();
            }
        }

        if (!gasit) {
            std::cout << "Nu s-a gasit un contact.\n";
        }
    }

    void cautare_numar_de_telefon() const {
        std::string sir;
        bool gasit = false;
        std::cout << "\n\nCautati contact dupa numar de telefon: ";
        std::cin >> sir;

        for (const auto& contact : lista_contacte) {
            if (contact.get_numar_telefon().find(sir) != std::string::npos) {
                gasit = true;
                contact.afisare_contact();
            }
        }

        if (!gasit) {
            std::cout << "Nu s-a gasit un contact.\n";
        }
    }

    void sorteaza_crescator_contacte() {
        std::sort(lista_contacte.begin(), lista_contacte.end(), [](const Contact& a, const Contact& b) {
            return a.get_nume() < b.get_nume();
        });

        afisare_lista();
    }

    void sorteaza_descrescator_contacte() {
        std::sort(lista_contacte.begin(), lista_contacte.end(), [](const Contact& a, const Contact& b) {
            return a.get_nume() > b.get_nume();
        });

        afisare_lista();
    }

    void citeste_si_afiseaza_n_contacte();
};

void meniu() {
    std::cout << "\n\nMeniu\n";
    std::cout << "1. Afiseaza contacte\n";
    std::cout << "2. Cauta contact dupa nume/prenume\n";
    std::cout << "3. Cauta contact dupa numar de telefon\n";
    std::cout << "4. Adauga contact\n";
    std::cout << "5. Sterge contact\n";
    std::cout << "6. Sorteaza crescator dupa nume\n";
    std::cout << "7. Sorteaza descrescator dupa nume\n";
    std::cout << "8. Adauga n contacte\n";
    std::cout << "9. Iesire\n";
    std::cout << "Alegeti optiunea: ";
}


void Lista_Contacte::citeste_si_afiseaza_n_contacte() {
    std::vector<Contact> contacte;
    unsigned int n,nr_contacte;
    std::cout<<"Numar contacte de adaugat sa adaugat: ";
    std::cin>>n;
    for (unsigned int i = 0; i < n; ++i) {
        nr_contacte=lista_contacte.size();
        Contact contact;
        std::cout << "Introduceti datele pentru contactul " << i + 1 << ":\n";
        adaugare_contact();
        if(lista_contacte.size()-1==nr_contacte)
            contacte.push_back(lista_contacte.back());
        else i--;
    }


    std::cout << "Contactele introduse sunt:\n";
    for (const auto& contact : contacte) {
        std::cout << contact << "\n";
    }
}


/*int citire_din_fisier() {
    std::string i;
    std::ifstream infile("date.txt"); // Input file stream

    if (!infile.is_open()) { // Check for opening error
        std::cout << "Could not open file date.txt.\n";
        return 1; // 1 signifies an error.
    }
std::cout<<"S-a deschis.";
    while (infile >> i) { // Read with a loop.
        std::cout << i << "\n";
    }

    infile.close(); // Done with the file, close it.
    return 0;
}*/


int main() {
    //if (citire_din_fisier()) {
    int optiune;
    Lista_Contacte lista_contacte;


    while (true) {
        meniu();
        std::cin >> optiune;
        switch (optiune) {
            case 1:
                lista_contacte.afisare_lista();
                break;
            case 2:
                lista_contacte.cautare_contact_nume();
                break;
            case 3:
                lista_contacte.cautare_numar_de_telefon();
                break;
            case 4:
                lista_contacte.adaugare_contact();
                break;
            case 5:
                lista_contacte.eliminare_contact();
                break;
            case 6:
                lista_contacte.sorteaza_crescator_contacte();
                break;
            case 7:
                lista_contacte.sorteaza_descrescator_contacte();
                break;
            case 8:
                lista_contacte.citeste_si_afiseaza_n_contacte();
                break;
            case 9:
                return 0;
            default:
                std::cout << "Nu exista optiunea!\n";
        }
    }

}
//return 0;
//}