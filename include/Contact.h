//
// Created by Xtreme Pc on 3/28/2024.
//

#ifndef OOP_CONTACT_H
#define OOP_CONTACT_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Contact {
private:
    std::string nume;
    std::string prenume;
    std::string numar_telefon;

public:
    ~Contact();
    Contact();
    Contact(std::string nume, std::string prenume, std::string numar_telefon);
    Contact(const Contact& other);
    Contact& operator=(const Contact& other);

    void afisare_contact() const;

    friend std::ostream& operator<<(std::ostream& out, const Contact& contact);

    friend std::istream& operator>>(std::istream& in, Contact& contact);

    [[nodiscard]] const std::string& get_nume() const;

    [[nodiscard]] const std::string& get_prenume() const;

    [[nodiscard]] const std::string& get_numar_telefon() const;

    friend bool validare_numar(const Contact& contact);
    friend bool operator==(const Contact& contact1, const Contact& contact2);
    bool operator>(const Contact& other) const;
};
#endif //OOP_CONTACT_H
