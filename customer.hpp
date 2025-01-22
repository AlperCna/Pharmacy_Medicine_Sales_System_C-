#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "medicine.hpp"

extern Medicine Medicines[];
extern int numMedicines;

void buyMedicine(int medicineID, int quantity);
void updateStockInFile(int medicineID, int newStockAmount);

#endif /* CUSTOMER_H */