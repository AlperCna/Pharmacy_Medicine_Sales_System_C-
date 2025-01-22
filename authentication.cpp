#include <iostream>
#include <cstring>
#include "admin.hpp"
#include "medicine.hpp"
#include "customer.hpp"
#include "authentication.hpp"

User::User(const std::string& username, const std::string& password)
    : username(username), password(password) {}

User::~User() {}

Customer::Customer(const std::string& username, const std::string& password)
    : User(username, password) {}

void Customer::displayMenu() const {
    int choice, medicineID, quantity;
    do {
        std::cout << "\n--- Medicine Purchase System ---\n";
        std::cout << "1. List Medicines\n";
        std::cout << "2. Buy Medicine\n";
        std::cout << "3. Exit\n";
        std::cout << "Your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                listMedicines(); // List medicines
                break;
            case 2:
                std::cout << "Enter the ID of the medicine you want to buy: ";
                std::cin >> medicineID;
                std::cout << "How many units do you want to buy? ";
                std::cin >> quantity;
                buyMedicine(medicineID, quantity); // Purchase medicine
                break;
            case 3:
                std::cout << "Exiting the program...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

Manager::Manager(const std::string& username, const std::string& password)
    : User(username, password) {}

void Manager::displayMenu() const {
    int choice;
    do {
        std::cout << "\nSelect an operation to perform:\n";
        std::cout << "1. Add Customer\n";
        std::cout << "2. List All Customers\n";
        std::cout << "3. Find Customer by ID\n";
        std::cout << "4. Add Medicine\n";
        std::cout << "5. Delete Medicine\n";
        std::cout << "6. Update Medicine\n";
        std::cout << "7. List All Medicines\n";
        std::cout << "8. Find Medicine by ID\n";
        std::cout << "9. Show Pharmacy Balance\n";
        std::cout << "10. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int customerID;
                char name[50];
                char address[100];
                char contactInfo[50];

                std::cout << "Customer ID: ";
                std::cin >> customerID;
                std::cout << "Name: ";
                std::cin >> name;
                std::cout << "Address: ";
                std::cin >> address;
                std::cout << "Contact Information: ";
                std::cin >> contactInfo;

                Customers *newCustomer = createCustomer(customerID, name, address, contactInfo);
                if (newCustomer != nullptr) {
                    std::cout << "Customer added successfully.\n";
                    showCustomer(*newCustomer);
                } else {
                    std::cout << "Failed to add customer.\n";
                }
                break;
            }
            case 2:
                listAllCustomers();
                break;
            case 3: {
                int searchedCustomerID;
                std::cout << "Search Customer ID: ";
                std::cin >> searchedCustomerID;
                Customers *foundCustomer = findCustomerByID(searchedCustomerID);
                if (foundCustomer != nullptr) {
                    std::cout << "Customer found:\n";
                    showCustomer(*foundCustomer);
                } else {
                    std::cout << "Customer not found.\n";
                }
                break;
            }
            case 4: {
                // Add Medicine
                int medicineID, stockAmount;
                char medicineName[200], manufacturer[100], expirationDate[20];
                double price;
                MedicineCategories category;
                std::cout << "Medicine ID: ";
                std::cin >> medicineID;
                std::cout << "Medicine Name: ";
                std::cin >> medicineName;
                std::cout << "Manufacturer: ";
                std::cin >> manufacturer;
                std::cout << "Price: ";
                std::cin >> price;
                std::cout << "Stock Amount: ";
                std::cin >> stockAmount;
                std::cout << "Expiration Date: ";
                std::cin >> expirationDate;
                std::cout << "Category (0 for A, 1 for B, 2 for C): ";
                int categorySelection;
                std::cin >> categorySelection;
                category = static_cast<MedicineCategories>(categorySelection);

                Medicine *newMedicine = createNewMedicine(medicineID, medicineName, manufacturer, price, stockAmount, expirationDate, category);
                if (newMedicine != nullptr) {
                    std::cout << "Medicine creation successful.\n";
                    showMedicine(*newMedicine);
                } else {
                    std::cout << "Medicine creation failed.\n";
                }
                break;
            }
            case 5: { // Deleting Medicine
                int medicineIDToDelete;
                std::cout << "Enter Medicine ID to delete: ";
                std::cin >> medicineIDToDelete;
                int deleteResult = deleteMedicine(medicineIDToDelete);
                if (deleteResult) {
                    std::cout << "Medicine with ID " << medicineIDToDelete << " has been deleted.\n";
                } else {
                    std::cout << "Medicine with ID " << medicineIDToDelete << " was not found.\n";
                }
                break;
            }
            case 6: { // Uptade Medicine
                int medicineIDToUpdate;
                std::cout << "Enter Medicine ID to update: ";
                std::cin >> medicineIDToUpdate;

                Medicine *medicineToUpdate = findMedicine(medicineIDToUpdate);
                if (medicineToUpdate != nullptr) {
                    int stockAmount;
                    double price;
                    std::cout << "Update Stock Amount: ";
                    std::cin >> stockAmount;
                    std::cout << "Update Price: ";
                    std::cin >> price;

                    medicineToUpdate->stockAmount = stockAmount;
                    medicineToUpdate->price = price;

                    int updateResult = updateMedicine(medicineIDToUpdate, stockAmount, price);

                    if (updateResult) {
                        std::cout << "Medicine with ID " << medicineIDToUpdate << " has been updated.\n";
                    } else {
                        std::cout << "Failed to update medicine with ID " << medicineIDToUpdate << ".\n";
                    }
                } else {
                    std::cout << "Medicine with ID " << medicineIDToUpdate << " was not found.\n";
                }
                break;
            }
            case 7:
                listMedicines();
                break;
            case 8: {
                int searchedMedicineID;
                std::cout << "Search Medicine ID: ";
                std::cin >> searchedMedicineID;
                Medicine *foundMedicine = findMedicine(searchedMedicineID);
                if (foundMedicine != nullptr) {
                    std::cout << "Medicine Found:\n";
                    showMedicine(*foundMedicine);
                } else {
                    std::cout << "Medicine Not Found.\n";
                }
                break;
            }

            case 9:{


                readBalanceFromFile();
        std::cout << "Current Pharmacy Balance: $" << pharmacyBalance.currentBalance << "\n";
            }

            case 10:{
                std::cout << "Exiting Manager operations.\n";
                break;
            }
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 10);
}

int menuSelection() {
    int choice;
    char username[20];
    char password[20];
    const char manager_username[] = "admin";
    const char manager_password[] = "1234";

    std::cout << "Please make your selection:\n";
    std::cout << "1. Customer\n";
    std::cout << "2. Manager\n";
    std::cout << "Choice: ";
    std::cin >> choice;

    if (choice == 1) {
        Customer customer("customer_username", "customer_password");
        std::cout << "Logged in as a Customer.\n";
        readMedicinesFromFile(); // Read medicines from file
        customer.displayMenu();
    } else if (choice == 2) {
        std::cout << "To log in as a Manager, please enter your username and password.\n";
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        if (strcmp(username, manager_username) == 0 && strcmp(password, manager_password) == 0) {
            Manager manager("admin", "1234");
            std::cout << "Successfully logged in as Manager.\n";
            readCustomersFromFile();
            readMedicinesFromFile();
            manager.displayMenu();
        } else {
            std::cout << "Invalid username or password. Login failed.\n";
        }
    } else {
        std::cout << "Invalid choice. Exiting the program.\n";
    }

    return 0;
}
