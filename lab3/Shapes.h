#pragma once
#include <iostream>

// Лабораторная работа 3, часть 2 (вариант 26): круг -> эллипс.

// Базовый класс "Круг"
class Circle
{
protected:
    double r; // Радиус (для эллипса - первая полуось)

public:
    Circle(double r) : r(r) {}

    // Виртуальный деструктор - чтобы delete через указатель на базовый класс
    // корректно удалял и объекты производного класса
    virtual ~Circle() {}

    // НЕ виртуальная функция -> статическое связывание (по типу указателя)
    void print() const
    {
        std::cout << "r=" << r;
    }

    // Виртуальная функция -> динамическое связывание (по типу объекта)
    virtual void printVirtual() const
    {
        std::cout << "r=" << r;
    }
};

// Производный класс "Эллипс"
class Ellipse : public Circle
{
    double b; // Вторая полуось

public:
    // Явный вызов конструктора базового класса: первая полуось = радиус
    Ellipse(double a, double b) : Circle(a), b(b) {}

    // Переопределение обычной функции (статический полиморфизм)
    void print() const
    {
        Circle::print(); // Сначала функция базового класса
        std::cout << ", b=" << b;
    }

    // Переопределение виртуальной функции (динамический полиморфизм)
    void printVirtual() const override
    {
        Circle::printVirtual(); // Сначала функция базового класса
        std::cout << ", b=" << b;
    }
};
