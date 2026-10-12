#include "Medicine.h"
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cstdio>

using namespace std;

namespace {

    string currentDate() {
        time_t t = time(nullptr);
        struct tm now;
#ifdef _MSC_VER
        localtime_s(&now, &t);
#else
        struct tm* ptr = localtime(&t);
        if (ptr) now = *ptr;
#endif
        char buf[11];
        snprintf(buf, sizeof(buf), "%02d.%02d.%04d",
            now.tm_mday, now.tm_mon + 1, now.tm_year + 1900);
        return string(buf);
    }

    long dateToKey(const string& d) {
        if (d.size() != 10 || d[2] != '.' || d[5] != '.')
            throw invalid_argument("Неверный формат даты: " + d);
        int day = stoi(d.substr(0, 2));
        int month = stoi(d.substr(3, 2));
        int year = stoi(d.substr(6, 4));
        return year * 10000L + month * 100L + day;
    }

}

Medicine::Medicine()
    : name("Неизвестно"), manufacturer("Неизвестно"),
    series("0000"), expiryDate("01.01.2000"),
    packs(0), category("обычный"), temperature(20.0) {
}

Medicine::Medicine(const string& n, const string& m, const string& s,
    const string& exp, int p, const string& cat, double temp)
    : name(n), manufacturer(m), series(s), expiryDate(exp),
    packs(p), category(cat), temperature(temp)
{
    if (p < 0)
        throw invalid_argument("Количество упаковок не может быть отрицательным");
    if (temp < -30.0 || temp > 30.0)
        throw invalid_argument("Недопустимая температура хранения");
    dateToKey(exp);   
}


string Medicine::getName()         const { return name; }
string Medicine::getManufacturer() const { return manufacturer; }
string Medicine::getSeries()       const { return series; }
string Medicine::getExpiryDate()   const { return expiryDate; }
int    Medicine::getPacks()        const { return packs; }
string Medicine::getCategory()     const { return category; }
double Medicine::getTemperature()  const { return temperature; }

void Medicine::setName(const string& n) { name = n; }
void Medicine::setManufacturer(const string& m) { manufacturer = m; }
void Medicine::setSeries(const string& s) { series = s; }
void Medicine::setCategory(const string& c) { category = c; }

void Medicine::setPacks(int p) {
    if (p < 0)
        throw invalid_argument("Количество упаковок не может быть отрицательным");
    packs = p;
}

void Medicine::setExpiryDate(const string& exp) {
    dateToKey(exp);
    expiryDate = exp;
}

void Medicine::setTemperature(double t) {
    if (t < -30.0 || t > 30.0)
        throw invalid_argument("Температура должна быть в диапазоне [-30; 30]");
    temperature = t;
}

bool Medicine::isExpired() const {
    return dateToKey(expiryDate) < dateToKey(currentDate());
}

bool Medicine::issue(int count) {
    if (isExpired())
        throw runtime_error("Нельзя выдать просроченный препарат: " + name);
    if (count <= 0)
        throw invalid_argument("Количество выдачи должно быть > 0");
    if (count > packs)
        throw runtime_error("Недостаточно упаковок на складе: " + name);
    packs -= count;
    return true;
}

void Medicine::receive(int count) {
    if (count <= 0)
        throw invalid_argument("Количество прихода должно быть > 0");
    packs += count;
}

void Medicine::printInfo() const {
    cout << "  Название:       " << name << "\n";
    cout << "  Производитель:  " << manufacturer << "\n";
    cout << "  Серия:          " << series << "\n";
    cout << "  Срок годности:  " << expiryDate
        << (isExpired() ? "  ПРОСРОЧЕН" : "  годен") << "\n";
    cout << "  Категория:      " << category << "\n";
    cout << "  Темп. хранения: " << temperature << " C\n";
    cout << "  Упаковок:       " << packs << "\n";
}