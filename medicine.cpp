#include "medicine.hpp"
#include <memory>

std::istream& operator>>(std::istream& in, MedicineCategories& category) {
    int categoryInt;
    in >> categoryInt;
    category = static_cast<MedicineCategories>(categoryInt);
    return in;
}

#define MAX_MEDICINES 100
Medicine Medicines[MAX_MEDICINES];
int numMedicines = 0;


// Function to add medicine
int addMedicine(const Medicine& medicine) {
    if (numMedicines < MAX_MEDICINES) {
        Medicines[numMedicines] = medicine;
        numMedicines++;
        return 1;  // Successful
    } else {
        return 0;  // Unsuccessful, array full
    }
}

// Function to write medicines to file
int writeMedicinesToFile(const Medicine& medicine) {
    std::ofstream file(MEDICINE_FILE, std::ios::app);
    if (file.is_open()) {
        file << medicine.medicineID << " " << medicine.medicineName << " " << medicine.manufacturer
             << " " << medicine.price << " " << medicine.stockAmount << " " << medicine.expirationDate
             << " " << static_cast<int>(medicine.category) << "\n";
        return 1;
    } else {
        return 0;  // File opening failed
    }
}

void readMedicinesFromFile() {
    std::ifstream file(MEDICINE_FILE);
    if (file.is_open()) {
        Medicine tempMedicine;
        int tempCategory;
        while (file >> tempMedicine.medicineID >> tempMedicine.medicineName >> tempMedicine.manufacturer
                   >> tempMedicine.price >> tempMedicine.stockAmount >> tempMedicine.expirationDate
                   >> tempCategory) {
            tempMedicine.category = static_cast<MedicineCategories>(tempCategory);
            Medicines[numMedicines] = tempMedicine;
            numMedicines++;
            if (numMedicines >= MAX_MEDICINES) {
                break;
            }
        }
        file.close();
    }
}


// Function to create a new medicine
Medicine* createNewMedicine(int medicineID, const std::string& medicineName, const std::string& manufacturer, double price, int stockAmount, const std::string& expirationDate, MedicineCategories category) {
    std::unique_ptr<Medicine> newMedicine = std::make_unique<Medicine>();

    if (newMedicine != nullptr) {
        newMedicine->medicineID = medicineID;
        newMedicine->medicineName = medicineName;
        newMedicine->manufacturer = manufacturer;
        newMedicine->price = price;
        newMedicine->stockAmount = stockAmount;
        newMedicine->expirationDate = expirationDate;
        newMedicine->category = category;

        if (addMedicine(*newMedicine) && writeMedicinesToFile(*newMedicine)) {
            return newMedicine.release();
        } else {
            return nullptr;
        }
    }

    return nullptr;
}

// Function to display medicine information
void showMedicine(const Medicine& medicine) {
    std::cout << "Medicine ID: " << medicine.medicineID << "\n";
    std::cout << "Name: " << medicine.medicineName << "\n";
    std::cout << "Manufacturer: " << medicine.manufacturer << "\n";
    std::cout << "Price: " << medicine.price << "\n";
    std::cout << "Stock Quantity: " << medicine.stockAmount << "\n";
    std::cout << "Expiration Date: " << medicine.expirationDate << "\n";
    std::cout << "Category: " << static_cast<int>(medicine.category) << "\n";
}

// Function to list all medicines
void listMedicines() {
    std::cout << "=== Medicine List ===\n";
    for (int i = 0; i < numMedicines; i++) {
        showMedicine(Medicines[i]);
        std::cout << "\n";
    }
}

Medicine* findMedicine(int medicineID) {
    for (int i = 0; i < numMedicines; i++) {
        if (Medicines[i].medicineID == medicineID) {
            return &Medicines[i];
        }
    }
    return nullptr;  // Medicine not found
}

// Function to delete medicine by ID
int deleteMedicine(int medicineID) {
    std::ifstream file(MEDICINE_FILE);
    if (!file.is_open()) {
        perror("Error opening file");
        return 0;
    }

    std::ofstream tempFile("temp.txt");
    if (!tempFile.is_open()) {
        perror("Error creating temporary file");
        file.close();
        return 0;
    }

    int found = 0;
    for (int i = 0; i < numMedicines; i++) {
        if (Medicines[i].medicineID == medicineID) {
            found = 1;
            continue;
        }
        tempFile << Medicines[i].medicineID << " " << Medicines[i].medicineName << " " << Medicines[i].manufacturer
                 << " " << Medicines[i].price << " " << Medicines[i].stockAmount << " " << Medicines[i].expirationDate
                 << " " << static_cast<int>(Medicines[i].category) << "\n";
    }

    file.close();
    tempFile.close();

    remove(MEDICINE_FILE);
    rename("temp.txt", MEDICINE_FILE);

    if (found) {
        numMedicines--;
    }

    return found;
}

// Function to update medicine information
int updateMedicine(int medicineID, int newStockAmount, double newPrice) {
    std::ofstream tempFile("temp.txt");
    std::ifstream file(MEDICINE_FILE);

    if (file.is_open() && tempFile.is_open()) {
        Medicine tempMedicine;
        while (file >> tempMedicine.medicineID >> tempMedicine.medicineName >> tempMedicine.manufacturer
                   >> tempMedicine.price >> tempMedicine.stockAmount >> tempMedicine.expirationDate
                   >> tempMedicine.category) {
            if (tempMedicine.medicineID == medicineID) {
                tempMedicine.stockAmount = newStockAmount;
                tempMedicine.price = newPrice;
            }
            tempFile << tempMedicine.medicineID << " " << tempMedicine.medicineName << " " << tempMedicine.manufacturer
                     << " " << tempMedicine.price << " " << tempMedicine.stockAmount << " " << tempMedicine.expirationDate
                     << " " << static_cast<int>(tempMedicine.category) << "\n";
        }
        file.close();
        tempFile.close();

        remove(MEDICINE_FILE);
        rename("temp.txt", MEDICINE_FILE);
        return 1;  // Successful
    } else {
        std::cout << "Dosya açma hatası.\n";
        return 0;  // File opening failed
    }
}