//
// Created by Xtreme Pc on 3/28/2024.
//
#include "Contact.h"

Contact::~Contact(){
    std::cout << "Contactul a fost sters cu succes!\n";
}

Contact::Contact() : nume("contact"), prenume("anonim"), numar_telefon("fara numar") {}
Contact::Contact(std::string nume, std::string prenume, std::string numar_telefon) : nume(std::move(nume)), prenume(std::move(prenume)), numar_telefon(std::move(numar_telefon)) {}
Contact::Contact(const Contact& other): nume(other.nume), prenume(other.prenume), numar_telefon(other.numar_telefon) {
    std::cout<<"Contactul s-a copiat cu succes!\n";
}



Contact& Contact::operator=(const Contact& other) {
    if (this != &other) {
        nume = other.nume;
        prenume = other.prenume;
        numar_telefon = other.numar_telefon;
    }
    return *this;
}


void Contact::afisare_contact() const {
    std::cout << nume << ' ' << prenume << ' ' << numar_telefon << '\n';
}


std::ostream& operator<<(std::ostream& out, const Contact& contact) {
    out << contact.nume << ' ' << contact.prenume << ' ' << contact.numar_telefon;
    return out;
}


std::istream& operator>>(std::istream& in, Contact& contact) {
    std::cout << "Nume: ";
    in >> contact.nume;
    std::cout << "Prenume: ";
    in >> contact.prenume;
    std::cout << "Numar de telefon: ";
    in >> contact.numar_telefon;
    return in;
}

[[nodiscard]] const std::string& Contact::get_nume() const {
    return nume;
}

[[nodiscard]] const std::string& Contact::get_prenume() const {
    return prenume;
}

[[nodiscard]] const std::string& Contact::get_numar_telefon() const {
    return numar_telefon;
}



bool validare_numar(const Contact& contact) {
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

bool Contact::operator>(const Contact& other) const {
    if (!(this->nume == other.nume))
        return this->nume > other.nume;

    return this->prenume > other.prenume;
}