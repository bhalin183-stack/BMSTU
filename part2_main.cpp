// Лабораторная работа 3, часть 2 (вариант 26): наследование, полиморфизм.
#include <iostream>
#include <vector>
#include "Shapes.h"

using namespace std;

int main()
{
    Circle c(5);     // Объект базового класса
    Ellipse e(4, 2); // Объект производного класса

    cout << "--- 1. Calls through objects ---" << endl;
    cout << "c.print():        "; c.print();        cout << endl;
    cout << "e.print():        "; e.print();        cout << endl;
    cout << "c.printVirtual(): "; c.printVirtual(); cout << endl;
    cout << "e.printVirtual(): "; e.printVirtual(); cout << endl;

    cout << "\n--- 2. Static polymorphism (print is NOT virtual) ---" << endl;
    Circle* pc = &c;
    cout << "pc -> circle,  pc->print(): "; pc->print(); cout << endl;
    pc = &e; // Указатель на базовый класс ссылается на объект-эллипс
    cout << "pc -> ellipse, pc->print(): "; pc->print(); cout << "   <- Circle::print, b is lost" << endl;

    cout << "\n--- 3. Dynamic polymorphism (printVirtual is virtual) ---" << endl;
    pc = &c;
    cout << "pc -> circle,  pc->printVirtual(): "; pc->printVirtual(); cout << endl;
    pc = &e;
    cout << "pc -> ellipse, pc->printVirtual(): "; pc->printVirtual(); cout << "   <- Ellipse::printVirtual" << endl;

    cout << "\n--- 4. Vector of pointers (base and derived objects) ---" << endl;
    vector<Circle*> shapes;
    shapes.push_back(new Circle(1));
    shapes.push_back(new Ellipse(3, 2));
    shapes.push_back(new Circle(7));
    shapes.push_back(new Ellipse(6, 4));

    cout << "print() (static binding):" << endl;
    for (size_t i = 0; i < shapes.size(); i++)
    {
        cout << "  [" << i << "] "; shapes[i]->print(); cout << endl;
    }

    cout << "printVirtual() (dynamic binding):" << endl;
    for (size_t i = 0; i < shapes.size(); i++)
    {
        cout << "  [" << i << "] "; shapes[i]->printVirtual(); cout << endl;
    }

    for (size_t i = 0; i < shapes.size(); i++) delete shapes[i]; // Освобождаем память
    return 0;
}
