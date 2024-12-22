#include "ContactManager.h"
#include "Database.h"
#include <iostream>
#include <algorithm>
#include <fstream>

ContactManager::ContactManager() {}

ContactManager::~ContactManager() {}

void ContactManager::addContact(const std::string& name, const std::string& phone, const std::string& email) {
    contacts.emplace_back(name, phone, email);
    saveContacts(dataFile);
    Database db("contacts.db");
    db.connect();
    db.addContact(name, phone, email);
    db.disconnect();
}

void ContactManager::displayContacts() const {
    if (contacts.empty()) {
        std::cout << "No contacts to display." << std::endl;
        return;
    }

    for (const auto& contact : contacts) {
        contact.to_string();
        std::cout << "-------------------" << std::endl;
    }
}

bool ContactManager::editContact(const std::string& oldName, const std::string& newName, const std::string& newPhone, const std::string& newEmail) {
    auto it = std::find_if(contacts.begin(), contacts.end(), [&oldName](const Contact& contact) {
        return contact.getName() == oldName;
    });

    if (it != contacts.end()) {
        it->setName(newName);
        it->setPhone(newPhone);
        it->setEmail(newEmail);
        saveContacts(dataFile);
        Database db("contacts.db");
        db.connect();
        db.updateContact(oldName, newName, newPhone, newEmail);
        db.disconnect();
        return true;
    }
    return false;
}

bool ContactManager::removeContact(const std::string& name) {
    auto it = std::remove_if(contacts.begin(), contacts.end(), [&name](const Contact& contact) {
        return contact.getName() == name;
    });

    if (it != contacts.end()) {
        contacts.erase(it, contacts.end());
        saveContacts(dataFile);
        Database db("contacts.db");
        db.connect();
        db.removeContact(name);
        db.disconnect();
        return true;
    }
    return false;
}

void ContactManager::loadContacts(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    std::string name, phone, email;
    while (file >> name >> phone >> email) {
        contacts.emplace_back(name, phone, email);
    }

    file.close();
}

void ContactManager::saveContacts(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    for (const auto& contact : contacts) {
        file << contact.getName() << " " << contact.getPhone() << " " << contact.getEmail() << std::endl;
    }

    file.close();
}