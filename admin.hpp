#ifndef ADMIN_HPP
#define ADMIN_HPP

#include <vector>
#include <iostream>
#include <fstream>

struct PharmacyBalance {
    double currentBalance;

    PharmacyBalance(double initialBalance = 0.0)
        : currentBalance(initialBalance) {}

    void updateBalance(double amount) {
        currentBalance += amount;
    }
};

extern PharmacyBalance pharmacyBalance;

struct Customers {
    int customerID;
    char name[50];
    char address[100];
    char contactInfo[50];
};

extern std::vector<Customers> customers;

int addCustomer(const Customers &customer);
int writeCustomerToFile(const Customers &customer);
void readCustomersFromFile();
Customers* createCustomer(int customerID, const char *name, const char *address, const char *contactInfo);
void showCustomer(const Customers &customer);
void listAllCustomers();
Customers* findCustomerByID(int customerID);
int readBalanceFromFile();
int updateBalanceInFile(double balance);

#endif // ADMIN_HPP
