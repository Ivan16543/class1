#pragma once
#include <string>

class Medicine {
private:
    std::string name;
    std::string manufacturer;
    std::string series;
    std::string expiryDate;   // "ДД.ММ.ГГГГ"
    int         packs;
    std::string category;
    double      temperature;

public:
    // Конструкторы
    Medicine();
    Medicine(const std::string& n, const std::string& m, const std::string& s,
        const std::string& exp, int p, const std::string& cat, double temp);

    // Геттеры
    std::string getName()         const;
    std::string getManufacturer() const;
    std::string getSeries()       const;
    std::string getExpiryDate()   const;
    int         getPacks()        const;
    std::string getCategory()     const;
    double      getTemperature()  const;

    // Сеттеры
    void setName(const std::string& n);
    void setManufacturer(const std::string& m);
    void setSeries(const std::string& s);
    void setCategory(const std::string& c);
    void setPacks(int p);
    void setExpiryDate(const std::string& exp);
    void setTemperature(double t);

    // Операции
    bool isExpired() const;
    bool issue(int count);
    void receive(int count);

    // Вывод
    void printInfo() const;
}; 
