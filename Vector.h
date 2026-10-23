#pragma once
#include <iostream>

// Класс-вектор: динамический массив double + число элементов.
// Вариант 2: перегрузка операции + для (Vector + double*),
// результат - Vector (поэлементная сумма, размерность та же).
class Vector
{
    double* p = nullptr; // Указатель на динамический массив
    int n = 0;           // Размерность вектора

public:
    Vector();                           // Конструктор без параметров - пустой вектор (n = 0)
    explicit Vector(int n);             // Вектор заданной длины, заполненный нулями
    Vector(const double* arr, int n);   // Конструктор на основе обычного массива
    Vector(const Vector& other);        // Конструктор копирования
    Vector(Vector&& other) noexcept;    // Конструктор перемещения
    ~Vector();                          // Деструктор

    int size() const { return n; }

    double& operator[](int index);              // Обращение к элементу (чтение/запись)
    const double& operator[](int index) const;  // Обращение к элементу для const-объектов

    Vector& operator=(const Vector& other);     // Присваивание с копированием
    Vector& operator=(Vector&& other) noexcept; // Присваивание с перемещением

    // Вариант 2: Vector + double*. Первый операнд - объект класса,
    // поэтому оператор-функция является членом класса.
    // Длина массива arr считается равной длине вектора.
    Vector operator+(const double* arr) const;

    // Ввод/вывод: первый операнд - поток, поэтому только внешние (friend) функции
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
    friend std::istream& operator>>(std::istream& is, Vector& v);
};
