#ifndef MEDICINE_H
#define MEDICINE_H

#include <iostream>
#include <fstream>
#include <string>

enum MedicineCategories {
    PAINKILLER,
    ANTIBIOTIC,
    COUGH_SYRUP,
 
   
};

extern const char *MEDICINE_FILE;
extern int numMedicines;

class Medicine {
public:
    int medicineID;
    std::string medicineName;
    std::string manufacturer;
    double price;
    int stockAmount;
    std::string expirationDate;
    MedicineCategories category;

  

    // Operator overloading and Friend Function
    friend std::istream& operator>>(std::istream& in, MedicineCategories& category);
};

int addMedicine(const Medicine& medicine);
int writeMedicinesToFile(const Medicine& medicine);
void readMedicinesFromFile();
Medicine* createNewMedicine(int medicineID, const std::string& medicineName, const std::string& manufacturer, double price, int stockAmount, const std::string& expirationDate, MedicineCategories category);
void showMedicine(const Medicine &medicine);
void listMedicines();
Medicine* findMedicine(int medicineID);
int deleteMedicine(int medicineID);
int updateMedicine(int medicineID, int newStockAmount, double newPrice);

#endif // MEDICINE_H
