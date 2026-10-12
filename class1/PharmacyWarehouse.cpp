#include "PharmacyWarehouse.h"
#include <iostream>
#include <stdexcept>

using namespace std;

PharmacyWarehouse::PharmacyWarehouse(const string& name)
    : warehouseName(name) {
}

string PharmacyWarehouse::getName() const { return warehouseName; }
int    PharmacyWarehouse::getCount() const { return (int)medicines.size(); }

void PharmacyWarehouse::addMedicine(const Medicine& m) {
    if ((int)medicines.size() >= MAX_CAPACITY)
        throw runtime_error("Склад переполнен! Максимум: " +
            to_string(MAX_CAPACITY));
    medicines.push_back(m);
}

Medicine* PharmacyWarehouse::findByName(const string& n) {
    for (auto& m : medicines)
        if (m.getName() == n) return &m;
    return nullptr;
}

bool PharmacyWarehouse::issueMedicine(const string& n, int count) {
    Medicine* m = findByName(n);
    if (!m) throw runtime_error("Препарат не найден: " + n);
    return m->issue(count);
}

void PharmacyWarehouse::receiveMedicine(const string& n, int count) {
    Medicine* m = findByName(n);
    if (!m) throw runtime_error("Препарат не найден: " + n);
    m->receive(count);
}

int PharmacyWarehouse::removeExpired() {
    int removed = 0;
    for (auto it = medicines.begin(); it != medicines.end(); ) {
        if (it->isExpired()) {
            cout << "  УТИЛИЗАЦИЯ " << it->getName()
                << " (серия " << it->getSeries() << ")\n";
            it = medicines.erase(it);
            ++removed;
        }
        else ++it;
    }
    return removed;
}

void PharmacyWarehouse::printStockReport() const {
    cout << "\n  СКЛАД: " << warehouseName << "\n";
    cout << "  Всего позиций: " << medicines.size()
        << " / " << MAX_CAPACITY << "\n\n";
    if (medicines.empty()) { cout << "  Склад пуст.\n"; return; }
    for (const auto& m : medicines) {
        m.printInfo();
        cout << "\n";
    }
}

void PharmacyWarehouse::printExpired() const {
    bool found = false;
    for (const auto& m : medicines)
        if (m.isExpired()) { m.printInfo(); cout << "\n"; found = true; }
    if (!found) cout << "  Просроченных препаратов нет.\n";
}

void PharmacyWarehouse::printAvailable() const {
    bool found = false;
    for (const auto& m : medicines)
        if (!m.isExpired()) { m.printInfo(); cout << "\n"; found = true; }
    if (!found) cout << "  Доступных к выдаче препаратов нет.\n";
}