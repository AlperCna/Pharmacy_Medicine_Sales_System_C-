#include "customer.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "admin.hpp"

float totalMedicinePrice = 0.0;
const char *MEDICINE_FILE = "medicine_db.txt";

void buyMedicine(int medicineID, int quantity) {
    for (int i = 0; i < numMedicines; i++) {
        if (Medicines[i].medicineID == medicineID) {
            if (Medicines[i].stockAmount >= quantity) {
                double totalPrice = Medicines[i].price * quantity;
                pharmacyBalance.updateBalance(totalPrice);

         // Update balance in the file
             updateBalanceInFile(pharmacyBalance.currentBalance);
                
                std::cout << "Purchased " << quantity << " units of " << Medicines[i].medicineName
                          << ". Total Price: " << totalPrice << "\n";
                totalMedicinePrice = totalPrice + totalMedicinePrice;
                Medicines[i].stockAmount -= quantity;

                // Update stock amount in the file
                updateStockInFile(medicineID, Medicines[i].stockAmount);

                std::string answer;
                std::cout << "Do you want to buy another medicine? (Yes/No): ";
                std::cin >> answer;
                if (answer == "Yes" || answer == "yes") {
                    std::cout << "Enter the ID of the medicine you want to buy: ";
                    std::cin >> medicineID;
                    std::cout << "How many units do you want to buy? ";
                    std::cin >> quantity;
                    buyMedicine(medicineID, quantity);
                } else if (answer == "No" || answer == "no") {
                    std::cout << "Total price of medicines purchased previously: " << totalMedicinePrice << "\n";
                    std::cout << "Exiting the program...\n";
                    return;
                } else {
                    std::cout << "You made an invalid choice. Program is terminating...\n";
                    return;
                }
                return;
            } else {
                std::cout << "There is not enough stock of " << Medicines[i].medicineName << " medicine.\n";
                return;
            }
        }
    }
    std::cout << "Medicine with ID " << medicineID << " was not found.\n";
}

void updateStockInFile(int medicineID, int newStockAmount) {
    std::ifstream file("medicine_db.txt");
    std::ofstream tempFile("temp_data.txt");

    if (!file || !tempFile) {
       
        return;
    }

    Medicine tempMedicine;

    int categoryInt;
    while (file >> tempMedicine.medicineID >> tempMedicine.medicineName >> tempMedicine.manufacturer
                >> tempMedicine.price >> tempMedicine.stockAmount >> tempMedicine.expirationDate
                >> categoryInt) {

        // casting 
        tempMedicine.category = static_cast<MedicineCategories>(categoryInt);

        if (tempMedicine.medicineID == medicineID) {
            // Uptade Stock Amount
            tempMedicine.stockAmount = newStockAmount;
        }

        // Other file operations
        tempFile << tempMedicine.medicineID << " "
                 << tempMedicine.medicineName << " "
                 << tempMedicine.manufacturer << " "
                 << tempMedicine.price << " "
                 << tempMedicine.stockAmount << " "
                 << tempMedicine.expirationDate << " "
                 << static_cast<int>(tempMedicine.category) << "\n";
    }

    // Closing files and changing name of the files

    file.close();
    tempFile.close();

    // Changing name of the files
    if (remove("medicine_db.txt") != 0) {
        // Exception Control
      
        return;
    }
    if (rename("temp_data.txt", "medicine_db.txt") != 0) {
        // Exception Control
        
    }
}
