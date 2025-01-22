#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "admin.hpp"

#define MAX_CUSTOMERS 100
const char *CUSTOMER_FILE = "customer.txt";
PharmacyBalance pharmacyBalance(10000.0);
std::vector<Customers> customers;




int readBalanceFromFile() {
    std::ifstream file("balance.txt");
    if (file.is_open()) {
        if (file >> pharmacyBalance.currentBalance) {
            file.close();
            return 1;  // Successful
        }
        file.close();
    }
    return 0;  // File reading failed
}

int updateBalanceInFile(double amount) {
    // Write the new amount directly to the file
    std::ofstream file("balance.txt");
    if (file.is_open()) {
        file << amount << "\n";
        file.close();
        return 1;  // Successful
    } else {
        return 0;  // File opening failed
    }
}

int addCustomer(const Customers &customer) {
    if (customers.size() < MAX_CUSTOMERS) {
        customers.push_back(customer);
        return 1;  // Successful
    } else {
        return 0;  //Cannot added, array is full
    }
}

int writeCustomerToFile(const Customers &customer) {
    std::ofstream file(CUSTOMER_FILE, std::ios::app);
    if (file.is_open()) {
        file << customer.customerID << " " << customer.name << " " << customer.address << " " << customer.contactInfo << "\n";
        file.close();
        return 1;  // Succesful
    } else {
        return 0;  // File opening failed
    }
}

void readCustomersFromFile() {
    std::ifstream file(CUSTOMER_FILE);
    if (file.is_open()) {
        while (customers.size() < MAX_CUSTOMERS) {
            Customers tempCustomer;
            if (file >> tempCustomer.customerID >> tempCustomer.name >> tempCustomer.address >> tempCustomer.contactInfo) {
                customers.push_back(tempCustomer);
            } else {
                break; // End of the file
            }
        }
        file.close();
    }
}




Customers* createCustomer(int customerID, const char *name, const char *address, const char *contactInfo) {
    Customers newCustomer;
    newCustomer.customerID = customerID;
    strncpy(newCustomer.name, name, sizeof(newCustomer.name));
    strncpy(newCustomer.address, address, sizeof(newCustomer.address));
    strncpy(newCustomer.contactInfo, contactInfo, sizeof(newCustomer.contactInfo));

    if (addCustomer(newCustomer) && writeCustomerToFile(newCustomer)) {
        return &customers.back();
    } else {
        return nullptr;
    }
}

void showCustomer(const Customers &customer) {
    std::cout << "Customer ID: " << customer.customerID << "\n";
    std::cout << "Name: " << customer.name << "\n";
    std::cout << "Address: " << customer.address << "\n";
    std::cout << "Contact Info: " << customer.contactInfo << "\n";
}

void listAllCustomers() {
    std::cout << "=== Customer List ===\n";
    for (const auto &customer : customers) {
        showCustomer(customer);
        std::cout << "\n";
    }
}

Customers* findCustomerByID(int customerID) {
    for (auto &customer : customers) {
        if (customer.customerID == customerID) {
            return &customer;
        }
    }
    return nullptr;  // Customer cannot find
}