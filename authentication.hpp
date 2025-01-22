#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "user.hpp"

class Customer : public User {
public:
    Customer(const std::string& username, const std::string& password);

    void displayMenu() const override;
    // Add any additional member functions specific to Customer
};

class Manager : public User {
public:
    Manager(const std::string& username, const std::string& password);

    void displayMenu() const override;
    // Add any additional member functions specific to Manager
};

// Function prototypes
int menuSelection();

#endif // AUTHENTICATION_H
