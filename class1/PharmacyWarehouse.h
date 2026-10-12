#pragma once
#include <string>
#include <vector>
#include "Medicine.h"

class PharmacyWarehouse {
private:
    std::string warehouseName;
    std::vector<Medicine> medicines;
    static const int MAX_CAPACITY = 100;

public:
    explicit PharmacyWarehouse(const std::string& name);

    std::string getName() const;
    int         getCount() const;

    void addMedicine(const Medicine& m);
    Medicine* findByName(const std::string& n);

    bool issueMedicine(const std::string& n, int count);
    void receiveMedicine(const std::string& n, int count);
    int  removeExpired();

    void printStockReport() const;
    void printExpired() const;
    void printAvailable() const;
}; 
