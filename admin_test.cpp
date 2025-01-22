#include <iostream>
#include <cassert>
#include "admin.hpp"
#include "medicine.hpp"
#include "authentication.hpp"
#include "customer.hpp"
#include "customer.cpp"
#include "admin.cpp"
#include "authentication.cpp"
#include "medicine.hpp"
#include "medicine.cpp"
#include "user.hpp"
class TestClass {
public:
    // Test method for adding customers
    void testAddCustomer() {
        // Arrange
        Customers customer1 = {1, "John Doe", "123 Main St", "555-1234"};
        Customers customer2 = {2, "Jane Smith", "456 Oak St", "555-5678"};

        // Act
        int result1 = addCustomer(customer1);
        int result2 = addCustomer(customer2);

        // Assert
        assert(result1 == 1);  // Customer 1 added successfully
        assert(result2 == 1);  // Customer 2 added successfully
        assert(customers.size() == 2);  // Total number of customers is 2
    }

    // Test method for finding customers by ID
    void testFindCustomerByID() {
        // Arrange
        Customers customer1 = {3, "John Doe", "123 Main St", "555-1234"};
        Customers customer2 = {4, "Jane Smith", "456 Oak St", "555-5678"};
        addCustomer(customer1);
        addCustomer(customer2);

        // Act
        Customers *foundCustomer1 = findCustomerByID(3);
        Customers *foundCustomer2 = findCustomerByID(4);
        Customers *notFoundCustomer = findCustomerByID(50);

        // Assert
        assert(foundCustomer1 != nullptr);  // Customer 1 found
        assert(foundCustomer2 != nullptr);  // Customer 2 found
        assert(notFoundCustomer == nullptr);  // Customer 3 not found
    }

    // Test method for adding medicines
    void testAddMedicine() {
        // Arrange
        Medicine medicine1 = {1, "Aspirin", "ABC Pharma", 5.99, 100, "2024-01-01", PAINKILLER};
        Medicine medicine2 = {2, "Amoxicillin", "XYZ Pharma", 12.99, 50, "2024-02-01", ANTIBIOTIC};

        // Act
        int result1 = addMedicine(medicine1);
        int result2 = addMedicine(medicine2);

        // Assert
        assert(result1 == 1);  // Medicine 1 added successfully
        assert(result2 == 1);  // Medicine 2 added successfully
        assert(numMedicines == 2);  // Total number of medicines is 2
    }

    // Test method for finding medicines by ID
    void testFindMedicineByID() {
        // Arrange
        Medicine medicine1 = {3, "Aspirin", "ABC Pharma", 5.99, 100, "2024-01-01", PAINKILLER};
        Medicine medicine2 = {4, "Amoxicillin", "XYZ Pharma", 12.99, 50, "2024-02-01", ANTIBIOTIC};
        addMedicine(medicine1);
        addMedicine(medicine2);

        // Act
        Medicine *foundMedicine1 = findMedicine(3);
        Medicine *foundMedicine2 = findMedicine(4);
        Medicine *notFoundMedicine = findMedicine(105);

        // Assert
        assert(foundMedicine1 != nullptr);  // Medicine 1 found
        assert(foundMedicine2 != nullptr);  // Medicine 2 found
        assert(notFoundMedicine == nullptr);  // Medicine 3 not found
    }


    void testDeleteMedicine() {
        Medicine sampleMedicine = {5, "SampleMedicine", "Manufacturer", 10.99, 50, "2024-12-31", PAINKILLER};
        addMedicine(sampleMedicine);

      
        int testMedicineID = sampleMedicine.medicineID;

       
        int result = deleteMedicine(testMedicineID);

      
        assert(result == 1);

       
        Medicine* deletedMedicine = findMedicine(testMedicineID);
        assert(deletedMedicine == nullptr);
    }

    void testUpdateMedicine() {
        Medicine sampleMedicine = {6, "SampleMedicine", "Manufacturer", 12.99, 70, "2024-12-31", PAINKILLER};
        addMedicine(sampleMedicine);

       
        int medicineToUpdateID = sampleMedicine.medicineID;

        Medicine* medicineToUpdate = findMedicine(medicineToUpdateID);

        
        int stockAmount = 50;
        double price = 25.5;

        assert(medicineToUpdate != nullptr);

        medicineToUpdate->stockAmount = stockAmount;
        medicineToUpdate->price = price;

        int updateResult = updateMedicine(medicineToUpdateID, stockAmount, price);
        assert(updateResult == 1);

        assert(medicineToUpdate != nullptr);
        assert(medicineToUpdate->stockAmount == stockAmount);
        assert(medicineToUpdate->price == price);
    }


    // Run all tests
    void runAllTests() {
        testAddCustomer();
        testFindCustomerByID();
        testAddMedicine();
        testFindMedicineByID();
        testDeleteMedicine();
        testUpdateMedicine();
    }
};

int main() {
    TestClass testObject;
    testObject.runAllTests();

    std::cout << "All tests passed successfully!\n";

    return 0;
}
