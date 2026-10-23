// Лабораторная работа 3, часть 1 (вариант 2): класс Vector, перегрузка операций.
// Ввод - из input.txt, вывод - в output.txt.
#include <iostream>
#include <fstream>
#include <utility>
#include "Vector.h"

using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    if (!fin.is_open()) { cerr << "Cannot open input.txt" << endl; return 1; }
    if (!fout.is_open()) { cerr << "Cannot open output.txt" << endl; return 1; }

    // Перенаправляем cout в файл: так и результаты, и сообщения
    // конструкторов/деструкторов попадают в output.txt
    streambuf* oldBuf = cout.rdbuf(fout.rdbuf());

    { // Блок нужен, чтобы деструкторы сработали до восстановления cout
        cout << "=== 1. Reading from input.txt (operator>>) ===" << endl;
        Vector A;
        fin >> A;

        int m = 0;
        fin >> m;
        double* arr = new double[m > 0 ? m : 1];
        for (int i = 0; i < m; i++) fin >> arr[i];

        Vector B;
        fin >> B;

        if (!fin)
        {
            cout << "Input error: check input.txt" << endl;
            delete[] arr;
            cout.rdbuf(oldBuf);
            return 1;
        }

        cout << "A = " << A << endl;
        cout << "arr (plain array, m=" << m << "):";
        for (int i = 0; i < m; i++) cout << ' ' << arr[i];
        cout << endl;
        cout << "B = " << B << endl;

        cout << "\n=== 2. Variant 2: Vector + double* ===" << endl;
        if (m != A.size())
        {
            cout << "Error: array length must be equal to vector length" << endl;
        }
        else
        {
            Vector C = A + arr;
            cout << "C = A + arr = " << C << endl;
            cout << "A after operation = " << A << " (unchanged)" << endl;

            cout << "\n=== 3. operator[] ===" << endl;
            cout << "C[0] = " << C[0] << ", C[" << C.size() - 1 << "] = " << C[C.size() - 1] << endl;
            C[0] = 100; // Запись через operator[]
            cout << "After C[0] = 100: " << C << endl;
        }

        cout << "\n=== 4. Copy constructor vs move constructor ===" << endl;
        Vector D(A); // Копирование
        cout << "After copy: A = " << A << endl;
        cout << "            D = " << D << endl;
        Vector E(std::move(D)); // Перемещение
        cout << "After move: D = " << D << "  <- source is empty" << endl;
        cout << "            E = " << E << endl;

        cout << "\n=== 5. Copy assignment vs move assignment ===" << endl;
        Vector F;
        F = B; // Присваивание с копированием
        cout << "After copy assignment: B = " << B << endl;
        cout << "                       F = " << F << endl;
        Vector G;
        G = std::move(B); // Присваивание с перемещением
        cout << "After move assignment: B = " << B << "  <- source is empty" << endl;
        cout << "                       G = " << G << endl;

        delete[] arr;
        cout << "\n=== 6. End of block: destructors ===" << endl;
    }

    cout.rdbuf(oldBuf); // Возвращаем cout на место
    return 0;
}
