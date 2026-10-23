#include "Vector.h"
#include <stdexcept>
#include <utility>

using std::cout;
using std::endl;

Vector::Vector()
{
    cout << "Vector()" << endl;
}

Vector::Vector(int n)
{
    if (n > 0)
    {
        this->n = n;
        p = new double[n](); // () - обнуляем элементы
    }
    cout << "Vector(int n) n=" << this->n << endl;
}

Vector::Vector(const double* arr, int n)
{
    if (n > 0 && arr != nullptr)
    {
        this->n = n;
        p = new double[n];
        for (int i = 0; i < n; i++) p[i] = arr[i];
    }
    cout << "Vector(const double* arr, int n) n=" << this->n << endl;
}

// Конструктор копирования: создаёт НОВЫЙ массив, исходный объект не меняется
Vector::Vector(const Vector& other)
{
    n = other.n;
    if (n > 0)
    {
        p = new double[n];
        for (int i = 0; i < n; i++) p[i] = other.p[i];
    }
    cout << "Vector(const Vector&) [copy] n=" << n << endl;
}

// Конструктор перемещения: забирает чужой массив, исходный объект становится пустым
Vector::Vector(Vector&& other) noexcept : p(other.p), n(other.n)
{
    other.p = nullptr;
    other.n = 0;
    cout << "Vector(Vector&&) [move] n=" << n << endl;
}

Vector::~Vector()
{
    cout << "~Vector() n=" << n << endl;
    delete[] p;
}

double& Vector::operator[](int index)
{
    if (index < 0 || index >= n) throw std::out_of_range("Vector: index out of range");
    return p[index];
}

const double& Vector::operator[](int index) const
{
    if (index < 0 || index >= n) throw std::out_of_range("Vector: index out of range");
    return p[index];
}

Vector& Vector::operator=(const Vector& other)
{
    if (this != &other) // Защита от v = v
    {
        double* tmp = nullptr;
        if (other.n > 0)
        {
            tmp = new double[other.n];
            for (int i = 0; i < other.n; i++) tmp[i] = other.p[i];
        }
        delete[] p; // Освобождаем старую память
        p = tmp;
        n = other.n;
    }
    cout << "operator=(const Vector&) [copy] n=" << n << endl;
    return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept
{
    if (this != &other)
    {
        delete[] p;      // Освобождаем свою старую память
        p = other.p;     // Забираем чужой массив
        n = other.n;
        other.p = nullptr; // Исходный объект становится пустым
        other.n = 0;
    }
    cout << "operator=(Vector&&) [move] n=" << n << endl;
    return *this;
}

Vector Vector::operator+(const double* arr) const
{
    Vector res(n); // Результат той же размерности
    for (int i = 0; i < n; i++) res.p[i] = p[i] + arr[i];
    return res;
}

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    os << "n=" << v.n << ":";
    for (int i = 0; i < v.n; i++) os << ' ' << v.p[i];
    return os;
}

// Формат ввода: сначала число элементов, затем сами элементы
std::istream& operator>>(std::istream& is, Vector& v)
{
    int m;
    if (!(is >> m) || m < 0)
    {
        is.setstate(std::ios::failbit);
        return is;
    }
    double* tmp = (m > 0) ? new double[m] : nullptr;
    for (int i = 0; i < m; i++)
    {
        if (!(is >> tmp[i]))
        {
            delete[] tmp;
            return is; // Ошибка чтения - вектор не меняем
        }
    }
    delete[] v.p;
    v.p = tmp;
    v.n = m;
    return is;
}
