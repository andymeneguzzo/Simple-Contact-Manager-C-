#include <iostream>
#include <vector>
#include <string>

class Contact {
public:
    Contact(const std::string& name, const std::string& phone, const std::string& email)
        : name(name), phone(phone), email(email) {}

    void display() const {
        std::cout << "Name: " << name << "\nPhone: " << phone << "\nEmail: " << email << std::endl;
    }

private:
    std::string name;
    std::string phone;
    std::string email;
};

class ContactManager {
public:
    void addContact(const std::string& name, const std::string& phone, const std::string& email) {
        contacts.emplace_back(name, phone, email);
    }

    void displayContacts() const {
        for (const auto& contact : contacts) {
            contact.display();
            std::cout << "-------------------" << std::endl;
        }
    }

private:
    std::vector<Contact> contacts;
};

int main() {
    ContactManager manager;

    std::cout << "Contact List:" << std::endl;
    manager.displayContacts();

    return 0;
}