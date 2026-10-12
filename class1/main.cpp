#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>

#include "Medicine.h"
#include "PharmacyWarehouse.h"

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) { clearInput(); return value; }
        cout << "   Ошибка: введите целое число.\n";
        clearInput();
    }
}

double readDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) { clearInput(); return value; }
        cout << "   Ошибка: введите число.\n";
        clearInput();
    }
}

string readLine(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

void printMedicineMenu() {
    cout << "\nМЕНЮ: ПРЕПАРАТ\n";
    cout << "  1. Создать новый препарат\n";
    cout << "  2. Показать текущий препарат\n";
    cout << "  3. Изменить название\n";
    cout << "  4. Изменить производителя\n";
    cout << "  5. Изменить серию\n";
    cout << "  6. Изменить категорию\n";
    cout << "  7. Изменить кол-во упаковок\n";
    cout << "  8. Изменить температуру хранения\n";
    cout << "  9. Изменить срок годности\n";
    cout << " 10. Проверить, просрочен ли\n";
    cout << " 11. Отправить препарат на склад\n";
    cout << "  0. Назад\n";
}

void medicineSubMenu(PharmacyWarehouse& warehouse) {
    Medicine med;

    int choice = -1;
    do {
        printMedicineMenu();
        choice = readInt("Ваш выбор: ");

        switch (choice) {
        case 1: {
            cout << "\n--- Создание препарата ---\n";
            string name = readLine("Название: ");
            string manuf = readLine("Производитель: ");
            string serie = readLine("Серия: ");
            string exp = readLine("Срок годности: ");
            int    packs = readInt("Количество упаковок: ");
            string cat = readLine("Категория: ");
            double temp = readDouble("Температура: ");
            try {
                med = Medicine(name, manuf, serie, exp, packs, cat, temp);
                cout << "  Препарат создан.\n";
            }
            catch (const exception& e) {
                cout << "  ОШИБКА: " << e.what() << "\n";
            }
            break;
        }
        case 2:
            cout << "\n--- Текущий препарат ---\n";
            med.printInfo();
            break;
        case 3: med.setName(readLine("Новое название: "));    cout << "  \n"; break;
        case 4: med.setManufacturer(readLine("Новый производитель: ")); cout << "  \n"; break;
        case 5: med.setSeries(readLine("Новая серия: "));      cout << "  \n"; break;
        case 6: med.setCategory(readLine("Новая категория: ")); cout << "  \n"; break;
        case 7: {
            int p = readInt("Новое количество упаковок: ");
            try { med.setPacks(p); cout << "  \n"; }
            catch (const exception& e) { cout << "  ОШИБКА: " << e.what() << "\n"; }
            break;
        }
        case 8: {
            double t = readDouble("Новая температура: ");
            try { med.setTemperature(t); cout << "  \n"; }
            catch (const exception& e) { cout << "  ОШИБКА: " << e.what() << "\n"; }
            break;
        }
        case 9: {
            string exp = readLine("Новый срок годности: ");
            try { med.setExpiryDate(exp); cout << "  \n"; }
            catch (const exception& e) { cout << "  ОШИБКА: " << e.what() << "\n"; }
            break;
        }
        case 10:
            cout << "  Препарат " << (med.isExpired() ? "ПРОСРОЧЕН" : "годен") << "\n";
            break;
        case 11: {
            try {
                warehouse.addMedicine(med);
                cout << "  Препарат отправлен на склад: "
                    << warehouse.getName() << "\n";
            }
            catch (const exception& e) {
                cout << "  ОШИБКА: " << e.what() << "\n";
            }
            break;
        }
        case 0: cout << "  Возврат в меню.\n"; break;
        default: cout << "  Неверный пункт.\n"; break;
        }
    } while (choice != 0);
}

void printWarehouseMenu() {
    cout << "\nМЕНЮ: СКЛАД\n";
    cout << "  1. Показать все препараты\n";
    cout << "  2. Найти препарат по названию\n";
    cout << "  3. Поставка препарата\n";
    cout << "  4. Выдача препарата\n";
    cout << "  5. Утилизировать просроченные партии\n";
    cout << "  6. Показать только просроченные\n";
    cout << "  7. Показать только доступные к выдаче\n";
    cout << "  0. Назад\n";
}

void warehouseSubMenu(PharmacyWarehouse& warehouse) {
    int choice = -1;
    do {
        printWarehouseMenu();
        choice = readInt("Ваш выбор: ");

        switch (choice) {
        case 1:
            warehouse.printStockReport();
            break;
        case 2: {
            cout << "\n--- Поиск ---\n";
            string name = readLine("Название: ");
            Medicine* m = warehouse.findByName(name);
            if (m) m->printInfo();
            else   cout << "  Препарат не найден.\n";
            break;
        }
        case 3: {
            cout << "\n--- Приход ---\n";
            string name = readLine("Название: ");
            int    cnt = readInt("Количество для прихода: ");
            try {
                warehouse.receiveMedicine(name, cnt);
                cout << "  Остаток: "
                    << warehouse.findByName(name)->getPacks() << "\n";
            }
            catch (const exception& e) { cout << "  ОШИБКА: " << e.what() << "\n"; }
            break;
        }
        case 4: {
            cout << "\n--- Выдача ---\n";
            string name = readLine("Название: ");
            int    cnt = readInt("Количество к выдаче: ");
            try {
                warehouse.issueMedicine(name, cnt);
                cout << "  Остаток: "
                    << warehouse.findByName(name)->getPacks() << "\n";
            }
            catch (const exception& e) { cout << "  ОШИБКА: " << e.what() << "\n"; }
            break;
        }
        case 5: {
            cout << "\n--- Утилизация просроченных ---\n";
            int removed = warehouse.removeExpired();
            cout << "  Утилизировано позиций: " << removed << "\n";
            break;
        }
        case 6: warehouse.printExpired();   break;
        case 7: warehouse.printAvailable(); break;
        case 0: cout << "  Возврат в меню.\n"; break;
        default: cout << "  Неверный пункт.\n"; break;
        }
    } while (choice != 0);
}

void printMainMenu() {
    cout << "\nМЕНЮ\n";
    cout << "  1. Препарат\n";
    cout << "  2. Склад\n";
    cout << "  0. Выход\n";
}

int main() {
    setlocale(LC_ALL, "Russian");

    PharmacyWarehouse warehouse("Главный аптечный склад N1");

    int choice = -1;
    do {
        printMainMenu();
        choice = readInt("Ваш выбор: ");

        switch (choice) {
        case 1: medicineSubMenu(warehouse);   break;
        case 2: warehouseSubMenu(warehouse);  break;
        case 0: cout << "\nВыход. До свидания!\n"; break;
        default: cout << "  Неверный пункт.\n"; break;
        }
    } while (choice != 0);

    return 0;
}